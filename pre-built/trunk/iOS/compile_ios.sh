#!/bin/sh
export REVISION=`svn info --xml | grep -m 1 -E 'revision *\= *"[0-9]+" *>' | grep -oE '[0-9]+'`
rm -rf .ios_build
mkdir .ios_build && cd .ios_build && cmake .. -DIOS=1 -DWITH_OPENSSL=No -DWITH_LUASQL=No && make -j8 && make install && rm -rf .ios_build && exit 0
exit 1
