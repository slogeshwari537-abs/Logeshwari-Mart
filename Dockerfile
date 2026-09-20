FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
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

# Copy project
COPY . .

# Install C++ dependencies from vcpkg.json
RUN vcpkg install --triplet x64-linux

# Configure project
RUN cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Release

# Build project
RUN cmake --build build --config Release -j2

# Render provides PORT automatically
ENV PORT=10000

EXPOSE 10000

CMD ["./build/LogeshwariMart"]