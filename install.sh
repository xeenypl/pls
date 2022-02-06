#!/bin/sh

set -ex

./build.sh

cp -f pls      /usr/bin
chown root:pls /usr/bin/pls
chmod 4750     /usr/bin/pls
