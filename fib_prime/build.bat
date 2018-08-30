cmd /c emcc -Os -s WASM=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -std=c++11 number_ops_pthread.cpp -o number_ops_pthread.js
cmd /c emcc -Os -s WASM=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -std=c++11 number_ops_stdthread.cpp -o number_ops_stdthread.js
cmd /c emcc -Os -s WASM=1 number_ops.c -o number_ops.js