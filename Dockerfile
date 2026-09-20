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
    autoconf \
    autoconf-archive \
    automake \
    libtool \
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

# Limit vcpkg build concurrency to reduce memory usage
ENV VCPKG_MAX_CONCURRENCY=1

# Create a release-only triplet based on the official Linux triplet
RUN printf '%s\n' \
    'include(/opt/vcpkg/triplets/x64-linux.cmake)' \
    'set(VCPKG_BUILD_TYPE release)' \
    > /opt/vcpkg/triplets/x64-linux-release.cmake

# Copy project
COPY . .

# Install dependencies using release-only triplet
RUN vcpkg install \
    --triplet x64-linux-release

# Configure project
RUN cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_TARGET_TRIPLET=x64-linux-release \
    -DCMAKE_BUILD_TYPE=Release

# Build with one job
RUN cmake --build build \
    --config Release \
    --parallel 1

ENV PORT=10000

EXPOSE 10000

CMD ["./build/LogeshwariMart"]