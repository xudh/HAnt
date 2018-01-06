#! /bin/sh

cd Function
make clean; make
cp -f Library/libFunction.a ../Library
cd -

cd Config
make clean; make
cp -f Library/libConfig.a ../Library
cd -

cd Page
make clean; make
cp -f Library/libPage.a ../Library
cd -

cd Bussiness
make clean; make
cd -

