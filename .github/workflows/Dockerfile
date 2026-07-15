FROM linuxdeepin/deepin:crimson

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        debhelper \
        fakeroot \
        qt6-base-dev \
        libdtk6widget-dev \
        qt6-multimedia-dev \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY . /build

# Build the Debian package (outputs to parent directory /)
RUN dpkg-buildpackage -us -uc -b && \
    mkdir -p /output && \
    cp ../*.deb /output/

CMD ["/bin/bash"]