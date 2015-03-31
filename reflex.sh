cd build
./autogen
cd ..
./configure --prefix=$PWD
make -j8
make install
