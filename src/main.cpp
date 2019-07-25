#include <emscripten/bind.h>
#include <emscripten.h>
#include <iostream>

#include "vector3.h"
#include "face3.h"
#include "triangle.h"
#include "geometry.h"
#include "buffergeometry.h"
#include "bspnode.h"
#include "meshutils.h"
#include "booleans.h"

// using namespace std;
using namespace emscripten;


BufferGeometry* buffGeom = nullptr;
std::vector<BSPNode*> bspNodes;

template <class T>
std::ostream& operator << (std::ostream& os, std::vector<T> v){
    for(auto e: v){
        os << e << " , ";
    }

    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<Vector3*> v){
    for(auto e: v){
        os << *e << " - ";
    }

    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<Face3*> v){
    for(auto e: v){
        os << *e << " - ";
    }

    return os;
}




extern "C" {

EMSCRIPTEN_KEEPALIVE
void addGeometry(float* buffer, int vertices_size, int normals_size, int position_size){
    // try{
        std::cout << "Creating Geometry..." << std::endl;
        std::vector<float> vertices {buffer, buffer + vertices_size};
        std::vector<float> normals {buffer + vertices_size, buffer + vertices_size + normals_size};
        std::vector<float> position {buffer + vertices_size + normals_size, buffer + vertices_size + normals_size + position_size};
        Geometry* g = new Geometry(vertices, normals, position);
        std::cout << "Creating BSPNode " << bspNodes.size() + 1 << std::endl;
        std::vector<Triangle*> triangles = convertGeometryToTriangles(g);
        BSPNode* node = new BSPNode(triangles);
        std::cout << "Done creating BSPNode!" << std::endl;
        bspNodes.push_back(node);
        std::cout <<"Currently there are " << bspNodes.size() << " nodes" << std::endl;
    // }catch (const std::runtime_error& error){
    //    std::cout << error.what() << std::endl;
    // }
}



EMSCRIPTEN_KEEPALIVE
float* getVerticesBuffer(){
    if(buffGeom){
        return buffGeom->vertices->data();
    }

    std::cout << "No buffer Geom computed" << std::endl;
    // throw std::runtime_error{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
float* getNormalsBuffer(){
    if(buffGeom){
        return buffGeom->normals->data();
    }

    std::cout << "No buffer Geom computed" << std::endl;
    // throw std::runtime_error{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getVerticesSize(){
    if(buffGeom){
        return buffGeom->vertices->size();
    }

    std::cout << "No buffer Geom computed" << std::endl;
    // throw std::runtime_error{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
int getNormalsSize(){
    if(buffGeom){
        return int(buffGeom->normals->size());
    }

    std::cout << "No buffer Geom computed" << std::endl;
    // throw std::runtime_error{"No buffer Geom computed"};
}

EMSCRIPTEN_KEEPALIVE
void computeUnion(){
    BSPNode* res = add(bspNodes);
    buffGeom = res->toGeometry()->toBufferGeometry();
}

EMSCRIPTEN_KEEPALIVE
void clean(){
    std::cout << "Deleting " << bspNodes.size() << " nodes" << std::endl;
    for(auto bsp: bspNodes){
        delete bsp; bsp = nullptr;
    }
    bspNodes.clear();

    std::cout << "Donde!" << std::endl;
    std::cout << "Deleting buffGeom " << std::endl;
    delete buffGeom; buffGeom = nullptr;
    std::cout << "Done!" << std::endl;
}

EMSCRIPTEN_KEEPALIVE
void bspToBuffer(int i){
    BSPNode* bsp = bspNodes.at(i);
    Geometry* geom = bsp->toGeometry();
    buffGeom = geom->toBufferGeometry();
}

}

int main()
{
    clean();
    std::cout << "WASM Module Ready" << std::endl;
    return 0;
}

EMSCRIPTEN_BINDINGS(wasmcsg_module) {
    function("bspToBuffer", &bspToBuffer);
    function("computeUnion", &computeUnion);
    function("clean", &clean);
    function("getNormalsBuffer", &getNormalsBuffer, allow_raw_pointers());
    function("getVerticesBuffer", &getVerticesBuffer, allow_raw_pointers());
    function("getNormalsSize", &getNormalsSize);
    function("getVerticesSize", &getVerticesSize);
    function("addGeometry", &addGeometry, allow_raw_pointers());
}
