/*
  ==============================================================================

    ObjFileSaver.cpp
    Created: 20 Jul 2024 7:07:33pm
    Author:  Padol

  ==============================================================================
*/

#include "ObjFileSaver.h"

ObjFileSaver::ObjFileSaver()
{
}

ObjFileSaver::~ObjFileSaver()
{
}

void ObjFileSaver::manageFileSave( std::ofstream& os, ObjFileFormat* file_format)
{

    saveVertex(os,file_format);
    saveVertexNormal(os, file_format);
    saveVertexTexture(os, file_format);
    saveFaces(os, file_format);
}

void ObjFileSaver::saveVertex(std::ofstream& os, ObjFileFormat* file_format)
{

    for (const auto& vertex : file_format->vertices.getDatas()) {
        os << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }
}

void ObjFileSaver::saveVertexNormal(std::ofstream& os, ObjFileFormat* file_format)
{

    for (const auto& vertex_normal : file_format->vertex_normals.getDatas()) {
        os << "vn " << vertex_normal.x << " " << vertex_normal.y << " " << vertex_normal.z << "\n";
    }
}

void ObjFileSaver::saveVertexTexture(std::ofstream& os, ObjFileFormat* file_format)
{

    for (const auto& vertex_texture : file_format->vertex_textures.getDatas()) {
        os << "vt " << vertex_texture.u << " " << vertex_texture.v << "\n";
    }
}

void ObjFileSaver::saveFaces(std::ofstream& os, ObjFileFormat* file_format)
{

    for (const auto& face : file_format->faces.getDatas()) {
        os << "f";
        for (size_t i = 0; i < face.vertexIndices.size(); ++i) {

            os << " " << face.vertexIndices[i];

            if (!face.texCoordIndices.empty()) {
                os << "/" << face.texCoordIndices[i];
            }

            if (!face.normalIndices.empty()) {
                if (face.texCoordIndices.empty()) {
                    os << "/";
                }
                os << "/" << face.normalIndices[i] ;
            }
        }
        os << "\n";
    }
}


