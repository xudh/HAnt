#! /bin/sh

cd Function
make
cp -f Library/libFunction.a ../Library
cd -

cd Config
make
cp -f Library/libConfig.a ../Library
cd -

cd Page
make
cp -f Library/libPage.a ../Library
cd -

cd Bussiness
make
cd -

