/*
  ==============================================================================

    ObjFileLoader.cpp
    Created: 20 Jul 2024 2:17:13pm
    Author:  Padol

  ==============================================================================
*/

#include "ObjFileLoader.h"


ObjFileLoader::ObjFileLoader()
{
}

ObjFileLoader::~ObjFileLoader()
{
}

bool ObjFileLoader::manageFileLoad(const std::string& line, ObjFileFormat* file_format)
{

    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v") {

        if (!loadVertex(iss, file_format)) {
            return false;
        }
    }
    else if (prefix == "vn") {

        if (!loadVertexNormal(iss, file_format)) {
            return false;
        }
    }
    else if (prefix == "vt") {

        if (!loadVertexTexture(iss, file_format)) {
            return false;
        }
    }
    else if (prefix == "f") {

        if (!loadFaces(iss, file_format)) {
            return false;
        }
    }

    return true;
}


bool ObjFileLoader::loadVertex(std::istringstream& iss, ObjFileFormat* file_format)
{
    BasicVertexDataStructs::Vertex vertex;
    iss >> vertex.x >> vertex.y >> vertex.z;
    file_format->vertices.add(vertex);
    
    return checkLineValidity(iss);
}


bool ObjFileLoader::loadVertexNormal(std::istringstream& iss, ObjFileFormat* file_format)
{

    BasicVertexDataStructs::VertexNormal vertex_normal;
    iss >> vertex_normal.x >> vertex_normal.y >> vertex_normal.z;
    file_format->vertex_normals.add(vertex_normal);

    return checkLineValidity(iss);
}


bool ObjFileLoader::loadVertexTexture(std::istringstream& iss, ObjFileFormat* file_format)
{

    BasicVertexDataStructs::VertexTexture vertex_texture;
    iss >> vertex_texture.u >> vertex_texture.v;
    file_format->vertex_textures.add(vertex_texture);

    return checkLineValidity(iss);
}

bool ObjFileLoader::loadFaces(std::istringstream& iss, ObjFileFormat* file_format)
{

    BasicVertexDataStructs::Face face;
    std::string vertexInfo;

    while (iss >> vertexInfo) {
        std::istringstream viss(vertexInfo);
        std::string index;
        int i = 0;
        while (std::getline(viss, index, '/')) {
            if (!index.empty()) {
                int idx = std::stoi(index);
                if (i == 0) face.vertexIndices.push_back(idx);
                else if (i == 1) face.texCoordIndices.push_back(idx);
                else if (i == 2) face.normalIndices.push_back(idx);
            }
            ++i;
        }
    }
    file_format->faces.add(face);


    return true;
}

