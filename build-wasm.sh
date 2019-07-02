#!/bin/bash

pwd

set -e

export OPTIMIZE="-O1"
export LDFLAGS="${OPTIMIZE}"
export CFLAGS="${OPTIMIZE}"
export CPPFLAGS="${OPTIMIZE}"

echo "============================================="
echo "Compiling wasm bindings"
echo "============================================="
(
  # Compile C/C++ code
  emcc \
    ${OPTIMIZE} \
    --bind \
    -s STRICT=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s ASSERTIONS=1 \
    -s MALLOC=emmalloc \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s DISABLE_EXCEPTION_CATCHING=0 \
    -o ./wasmcsg.js \
    ./src/*.cpp

  # Create output folder
  mkdir -p dist
  # Move artifacts
  mv wasmcsg.{js,wasm} dist
)
echo "============================================="
echo "Compiling wasm bindings done"
echo "============================================="
