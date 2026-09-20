FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app

# System dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    python3 \
    bison \
    flex \
    libssl-dev \
    libpq-dev \
    uuid-dev \
    zlib1g-dev \
    libjsoncpp-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg \
    && /opt/vcpkg/bootstrap-vcpkg.sh -disableMetrics

ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="/opt/vcpkg:${PATH}"

# Release-only custom triplet
RUN printf '%s\n' \
    'set(VCPKG_TARGET_ARCHITECTURE x64)' \
    'set(VCPKG_CMAKE_SYSTEM_NAME Linux)' \
    'set(VCPKG_BUILD_TYPE release)' \
    'set(VCPKG_LIBRARY_LINKAGE dynamic)' \
    > /opt/vcpkg/triplets/x64-linux-release.cmake

# Copy project
COPY . .

# Install dependencies using Release-only triplet
RUN VCPKG_BUILD_TYPE=release \
    vcpkg install \
    --triplet x64-linux-release

# Configure project
RUN cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_TARGET_TRIPLET=x64-linux-release \
    -DCMAKE_BUILD_TYPE=Release

# Build with one job to reduce memory usage
RUN cmake --build build \
    --config Release \
    --parallel 1

ENV PORT=10000

EXPOSE 10000

CMD ["./build/LogeshwariMart"]