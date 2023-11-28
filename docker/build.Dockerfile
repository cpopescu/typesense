# The good image that builds:
#
# docker build -t typesense-img -f build.Dockerfile .
# docker run --name typesense -v $(pwd):/typesense -ti typesense-img bin/bash
#  -c "cd /typesense && ./build-bazel.sh"
#
# bazel build //:search //:typesense-server //:benchmark //:typesense-test"
#
FROM ubuntu:23.04

COPY install-ubuntu.sh .
RUN ./install-ubuntu.sh

ENV CC gcc
ENV CXX g++
