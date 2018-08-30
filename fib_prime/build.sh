#!/bin/bash

emcc -Os -s WASM=1 number_ops.c -o number_ops.js