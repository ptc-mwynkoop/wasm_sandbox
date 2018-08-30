cmd /c emcc -Os -s WASM=1 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 number_ops_pthread.c -o number_ops_pthread.js
cmd /c emcc -Os -s WASM=1 number_ops.c -o number_ops.js