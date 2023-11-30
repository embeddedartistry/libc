#!/usr/bin/env bash

sudo apt-get install -y git-lfs
sudo apt-get install -y python3 python3-pip ninja-build
pip3 install meson
make
