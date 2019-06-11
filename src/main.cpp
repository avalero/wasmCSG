#include <emscripten/bind.h>
#include <emscripten.h>
#include <iostream>

#include "polygon.h"
#include "vertex.h"
#include "node.h"
#include "threebsp.h"

// using namespace std;
using namespace emscripten;

std::vector<Geometry*> geometries;

int main()
{
    geometries.clear();
    return 0;
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void buildCSG(float* buffer, int buffersize){
        std::cout << "Hello from buildCSG" << std::endl;
        std::cout << "Received a buffer of size " << buffersize << std::endl;
        std::vector<float> my_vector {buffer, buffer + buffersize};

        for(auto a:my_vector){
            std::cout << a << ", " ;
        }
        std::cout << std::endl;
    }

    // EMSCRIPTEN_KEEPALIVE
    //void addGeometry(float* verticesBuffer, int vertices_size,
    //                 float* normalsBuffer, int normals_size,
    //                 float* positionBuffer, int position_size){
    //    std::cout << "vertices size: " << vertices_size << std::endl;
    //    std::cout << "normals size: " << normals_size << std::endl;
    //    std::cout << "position size: " << position_size << std::endl;
    //}

    EMSCRIPTEN_KEEPALIVE
    void addGeometry(float* verticesBuffer, int vertices_size){
        std::cout << "vertices size: " << vertices_size << std::endl;
    }
}

EMSCRIPTEN_BINDINGS(wasmcsg_module) {
    function("buildCSG", &buildCSG, allow_raw_pointers());
    function("addGeometry", &addGeometry, allow_raw_pointers());
}
