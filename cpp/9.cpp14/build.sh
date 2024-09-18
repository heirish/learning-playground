build_dir=./build
rm -rf ${build_dir} 2>&1 > /dev/null
mkdir ${build_dir}
cd ${build_dir}
cmake ../
make clean && make
cd -
