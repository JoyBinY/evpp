STEP 1:
git clone https://github.com/google/glog.git
cd glog
cmake -S . -B .build -G "Unix Makefiles"
cmake --build .build
sudo cmake --build .build --target install

STEP 2:
git clone https://github.com/libevent/libevent.git
cd libevent
cmake -S . -B .build -G "Unix Makefiles"
cmake --build .build
sudo cmake --build .build --target install

STEP 3:
git clone https://github.com/Qihoo360/evpp
cd evpp
git submodule update --init --recursive
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j
make test