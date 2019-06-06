# wasmCSG
Web Assembly Constructive Solid Geometry Module

Tightly based on Three CSG JavaScript Library: https://github.com/chandlerprall/ThreeCSG

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

