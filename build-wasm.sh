#!/bin/bash

pwd

set -e

export OPTIMIZE="-O3"
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
    -s ASSERTIONS=0 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s DISABLE_EXCEPTION_CATCHING=1 \
    -s SAFE_HEAP=1 \
    -s RUNTIME_LOGGING=0 \
    -s INVOKE_RUN=0 \
    -s SAFE_HEAP_LOG=0 \
    -s INLINING_LIMIT=1 \
    -s FILESYSTEM=0 \
    -fno-exceptions \
    -o ./wasmcsg.js \
    ./src/*.cpp

# -s MALLOC=emmalloc \

# Create output folder
  mkdir -p dist
  # Move artifacts
  mv wasmcsg.{js,wasm} dist
)
echo "============================================="
echo "Compiling wasm bindings done"
echo "============================================="
