#/bin/bash

sudo apt-get install libsdl2-2.0 libgl1-mesa-dev x11proto-core-dev libx11-dev
apt-cache search libsdl2
apt-get install libsdl2-dev

git clone git://github.com/bkaradzic/bx.git
git clone git://github.com/bkaradzic/bimg.git
git clone git://github.com/bkaradzic/bgfx.git

cd bgfx

make linux-release64
