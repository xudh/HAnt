#! /bin/sh

cd Function
make
cp -f Library/LibFunction.a ../Library
cd -

cd Config
make
cp -f Library/LibConfig.a ../Library
cd -

cd Page
make
cp -f Library/LibPage.a ../Library
cd -

cd Bussiness
make
cd -

