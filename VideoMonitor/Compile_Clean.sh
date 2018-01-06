#! /bin/sh

rm -f Library/libFunction.a
cd Function
make clean
cd -

rm -f Library/libConfig.a
cd Config
make clean
cd -

rm -f Library/libPage.a
cd Page
make clean
cp -f Library/libPage.a ../Library
cd -

cd Bussiness
make clean
cd -

