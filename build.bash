#!/bin/bash
#Linux platform build project and run this file
cd build
rm -rf *
cmake .. && make
