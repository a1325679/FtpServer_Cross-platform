chcp 65001
cd build
del -rf *
cmake .. -G "MinGW Makefiles"
mingw32-make.exe