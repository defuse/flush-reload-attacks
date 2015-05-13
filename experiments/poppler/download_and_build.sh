#!/bin/bash

cd /tmp/
wget http://poppler.freedesktop.org/poppler-0.32.0.tar.xz
rm -rf poppler-0.32.0
tar xvf poppler-0.32.0.tar.xz
rm -rf /tmp/experiment_root/
mkdir /tmp/experiment_root/
cd poppler-0.32.0
./configure --prefix=/tmp/experiment_root
make
make install
