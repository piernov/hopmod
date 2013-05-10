#!/bin/sh
./merge.sh latest || exit 1
./compile_ios.sh || exit 1
echo ok
