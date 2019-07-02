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
ThreeBSP* bsp = nullptr;


std::ostream& operator << (std::ostream& os, std::vector<float> v){
    for(auto e: v){
        os << e << " - ";
    }

    return os;
}

int main()
{
    std::cout << "WASM Module Ready" << std::endl;
    geometries.clear();

    return 0;
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
void addGeometry(float* buffer, int vertices_size, int normals_size, int position_size){
    std::vector<float> vertices {buffer, buffer + vertices_size};
    std::vector<float> normals {buffer + vertices_size, buffer + vertices_size + normals_size};
    std::vector<float> position {buffer + vertices_size + normals_size, buffer + vertices_size + normals_size + position_size};

    Geometry* g = new Geometry(vertices, normals, position);
    geometries.push_back(g);
}

EMSCRIPTEN_KEEPALIVE
void computeBSP(int i){
    if(bsp) delete bsp;
    std::cout << "geom to bsp" << std::endl;
    bsp = new ThreeBSP(geometries.at(i));
    std::cout << "Done!" << std::endl;
}

EMSCRIPTEN_KEEPALIVE
void computeBufferGeomFromBSP(){
    if (!bsp){
        std::cout << "bsp not computed" << std::endl;
        throw std::string{"bsp not computed"};
    }

    std::cout << "bsp to geom" << std::endl;
    Geometry* geom = bsp->toGeometry();
    std::cout << "geom computed" << std::endl;
    if(buffGeom) delete buffGeom;
    std::cout << "computing buffer geom" << std::endl;
    buffGeom = geom->toBufferGeometry();
    std::cout << "Done! " << std::endl;
}


EMSCRIPTEN_KEEPALIVE
float* getVerticesBuffer(){
    if(buffGeom){
        return buffGeom->vertices->data();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
float* getNormalsBuffer(){
    if(buffGeom){
        return buffGeom->normals->data();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getVerticesSize(){
    if(buffGeom){
        return buffGeom->vertices->size();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getNormalsSize(){
    if(buffGeom){
        return buffGeom->normals->size();
    }
    throw std::string{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
void computeUnion(){
    if(geometries.size() == 0){
        std::cout << "Cannot perform union with 0 geometries" << std::endl;
        throw std::string{"Cannot perform union with 0 geometries"};
    }

    std::cout << "Computing union of " << geometries.size() << "geometries" << std::endl;

    ThreeBSP * result = new ThreeBSP(geometries.at(0));
    std::cout << "BSP of first geometry done" << std::endl;
    for(unsigned long int i{1}; i < geometries.size() ; i++){
        result->comp_union(new ThreeBSP(geometries.at(i)));
    }

    buffGeom = result->toGeometry()->toBufferGeometry();
}

}



EMSCRIPTEN_BINDINGS(wasmcsg_module) {
    function("computeUnion", &computeUnion);
    function("computeBSP", &computeBSP);
    function("computeBufferGeomFromBSP", &computeBufferGeomFromBSP);
    function("getNormalsBuffer", &getNormalsBuffer, allow_raw_pointers());
    function("getVerticesBuffer", &getVerticesBuffer, allow_raw_pointers());
    function("getNormalsSize", &getNormalsSize);
    function("getVerticesSize", &getVerticesSize);
    function("addGeometry", &addGeometry, allow_raw_pointers());
}
