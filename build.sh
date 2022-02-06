#!/bin/sh

set -ex
cc -O3 pls.c -o pls -lcrypt
