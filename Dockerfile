FROM ubuntu:20.04
LABEL maintainer="ryangraham@gmail.com"

ENV DEBIAN_FRONTEND noninteractive

ENV BUILD_TOOLS \
    build-essential \
    autoconf \
    g++ \
    gcc \
    make \
    cmake

ENV TOOLS \
    ca-certificates \
    curl \
    git \
    sudo \
    unzip

ENV DEPS \
    libglib2.0-dev \
    libsecret-1-dev

RUN apt-get update \
    && apt-get install -y \
    $BUILD_TOOLS \
    $TOOLS \
    $DEPS \
    --no-install-recommends
