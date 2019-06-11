# wasmCSG
Web Assembly Constructive Solid Geometry Module

ThreeCSG JavaScript Library (https://github.com/chandlerprall/ThreeCSG) ported to C++ to be compiled to WASM. The goal is to reduce computation time (when we get results we will post here a comparative)

## Build Instructions
### Prerequisites

- Install emscripten compiler: https://emscripten.org/
- Add emcc to your PATH
- Create a dist directory into project root directory

### Build

``
npm install && npm run build
`` 

js and wasm files will be located in dist folder

### Check
``
npm run serve
``

