# Host
FROM ubuntu:20.04

# Install required packages
RUN apt-get update && \
    apt-get install -y cmake clang ninja-build vim

# docker dir
WORKDIR /app

# Copy files
COPY sandbox /app/sandbox
COPY src /app/src
COPY cmake /app/cmake
COPY CMakeLists.txt /app/
COPY scripts/internal/docker.sh /app/

RUN chmod +x /app/docker.sh

ENTRYPOINT ["/app/docker.sh"]