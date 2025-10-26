#!/bin/bash -x
WORKDIR=work

LIB_DIR="usr/lib/games/ninix-kagari/kagari"
DOC_DIR="usr/share/doc/kagari"

VERSION="1.0.0"

make -j

mkdir ${WORKDIR}

pushd ${WORKDIR}

mkdir -p ${LIB_DIR}
mkdir -p ${DOC_DIR}

cp ../libkagari.so ${LIB_DIR}/libkagari.so

cp -r ../debian DEBIAN

cp ../LICENSE ${DOC_DIR}/copyright

find usr -type f -exec md5sum {} \+ > DEBIAN/md5sums
INSTALLED_SIZE=$(du -sk usr | cut -f 1)
sed -i -e "s/@installed_size/${INSTALLED_SIZE}/g" -e "s/@version/${VERSION}/g" DEBIAN/control
popd
fakeroot dpkg-deb --build ${WORKDIR} .

rm -r work
