#!/bin/bash

VERSION="0.32.0"
EXT="tar.xz"
#VERSION="0.18.4"
#EXT="tar.gz"

cd /tmp/
wget http://poppler.freedesktop.org/poppler-$VERSION.$EXT
rm -rf poppler-$VERSION
tar xvf poppler-$VERSION.$EXT
rm -rf /tmp/experiment_root/
mkdir /tmp/experiment_root/
cd poppler-$VERSION
./configure --prefix=/tmp/experiment_root
make
make install
