#include <emscripten/bind.h>
#include <emscripten.h>
#include <iostream>

#include "polygon.h"
#include "vertex.h"
#include "node.h"
#include "threebsp.h"
#include "geometry.h"
#include "buffergeometry.h"

// using namespace std;
using namespace emscripten;

std::vector<Geometry*> geometries;
BufferGeometry* buffGeom = nullptr;

int main()
{
    geometries.clear();
    return 0;
}

extern "C" {
EMSCRIPTEN_KEEPALIVE
void buildCSG(float* buffer, int buffersize){
    std::vector<float> my_vector {buffer, buffer + buffersize};
}


EMSCRIPTEN_KEEPALIVE
void addGeometry(float* buffer, int vertices_size, int normals_size, int position_size){
    std::vector<float> vertices {buffer, buffer + vertices_size};
    std::vector<float> normals {buffer + vertices_size, buffer + vertices_size + normals_size};
    std::vector<float> position {buffer + vertices_size + normals_size, buffer + vertices_size + normals_size + position_size};

    Geometry* g = new Geometry(vertices, normals, position);
    geometries.push_back(g);
}

void computeBufferGeometry(int i){
    if(buffGeom) delete buffGeom;

    if(i >= geometries.size()) throw std::string{"Out of bounds"};


    Geometry* geom = geometries.at(i);
    buffGeom = geom->toBufferGeometry();
}

EMSCRIPTEN_KEEPALIVE
float* getVerticesBuffer(int i){
    computeBufferGeometry(i);
    if(buffGeom){
        return buffGeom->vertices->data();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
float* getNormalsBuffer(int i){
    computeBufferGeometry(i);
    if(buffGeom){
        return buffGeom->normals->data();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getVerticesSize(int i){
    computeBufferGeometry(i);
    if(buffGeom){
        return buffGeom->vertices->size();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getNormalsSize(int i){
    computeBufferGeometry(i);
    if(buffGeom){

        return buffGeom->normals->size();
    }
    throw std::string{"No buffer Geom computed"};
}
}

EMSCRIPTEN_BINDINGS(wasmcsg_module) {
    function("getNormalsBuffer", &getNormalsBuffer, allow_raw_pointers());
    function("getVerticesBuffer", &getVerticesBuffer, allow_raw_pointers());
    function("getNormalsSize", &getNormalsSize);
    function("getVerticesSize", &getVerticesSize);
    function("buildCSG", &buildCSG, allow_raw_pointers());
    function("addGeometry", &addGeometry, allow_raw_pointers());
}
