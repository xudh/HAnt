#! /bin/sh

cd Function
make clean; make
cp -f Library/LibFunction.a ../Library
cd -

cd Config
make clean; make
cp -f Library/LibConfig.a ../Library
cd -

cd Page
make clean; make
cp -f Library/LibPage.a ../Library
cd -

cd Bussiness
make clean; make
cd -

