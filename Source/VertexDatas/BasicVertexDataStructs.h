/*
  ==============================================================================

    BasicVertexDataStructs.h
    Created: 18 Jul 2024 7:39:03pm
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include <vector>


namespace BasicVertexDataStructs {

    struct Vec3 {

        float x, y, z;
    };


    struct Vertex : public Vec3 {
    };

    struct VertexNormal : public Vec3 {

    };

    struct VertexTexture {
        float u, v;
    };

    struct Face {
        std::vector<int> vertexIndices;
        std::vector<int> texCoordIndices;
        std::vector<int> normalIndices;

    };


    struct Triangle {
        Vec3 v1, v2, v3;
        Vec3 normal;
    };

}

/*
* A container, which hold and manage BasicVertexDataStructs, including:
* -An std::vector, which hold the data struct
* -Add function
*/

template <typename T>
class VertexContainer {

public:

    void add(T& new_vertex_data) {

        vertex_datas.push_back(new_vertex_data);
    }
    
    std::vector<T>& getDatas() {

        return vertex_datas;
    }

protected:

    std::vector<T> vertex_datas;

};