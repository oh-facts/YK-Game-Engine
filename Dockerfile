# Host
FROM ubuntu:20.04

# Install required packages
RUN apt-get update && \
    apt-get install -y --fix-missing cmake libgl-dev libglfw3 clang \
    ninja-build libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev xvfb \
    libgl1-mesa-dev

# Set the DISPLAY variable
ENV DISPLAY=:0

# docker dir
WORKDIR /app

# Copy files
COPY res /app/res
COPY sandbox /app/sandbox
COPY src /app/src
COPY vendor /app/vendor
COPY cmake /app/cmake
COPY CMakeLists.txt /app/
COPY scripts/docker.sh /app/

RUN chmod +x /app/docker.sh

ENTRYPOINT ["/app/docker.sh"]
