#!/bin/bash

emcc -Os -s WASM=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -std=c++11 number_ops_pthread.cpp -o number_ops_pthread.js
emcc -Os -s WASM=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -std=c++11 number_ops_stdthread.cpp -o number_ops_stdthread.js
emcc -Os -s WASM=1 number_ops.c -o number_ops.js