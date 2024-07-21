/*
  ==============================================================================

    ObjToStlConverter.cpp
    Created: 21 Jul 2024 9:29:46am
    Author:  Padol

  ==============================================================================
*/

#include "ObjToStlConverter.h"

ObjToStlConverter::ObjToStlConverter()
{

    is_binary_file = true;
}

ObjToStlConverter::~ObjToStlConverter()
{
}

void ObjToStlConverter::manageFileSave(std::ofstream& os, ObjFileFormat* file_format)
{
    saveHeader(os);
    saveTriangles(os,file_format);

   // os.

}

void ObjToStlConverter::saveHeader(std::ofstream& os)
{

    char header[80] = "";
    os.write(header, 80);


}

void ObjToStlConverter::saveTriangles(std::ofstream& os, ObjFileFormat* file_format)
{



    std::vector<BasicVertexDataStructs::Vertex> vertices = file_format->vertices.getDatas();
    std::vector<BasicVertexDataStructs::Triangle> triangles;

    for (size_t i = 0; i < file_format->faces.getDatas().size(); ++i) {

        const BasicVertexDataStructs::Face face = file_format->faces.getDatas()[i];

        for (size_t j = 1; j + 1 < face.vertexIndices.size(); ++j) {

            BasicVertexDataStructs::Triangle triangle;

            makeTriangleCoordinate(triangle.v1, vertices[face.vertexIndices[0] - 1]);
            makeTriangleCoordinate(triangle.v2, vertices[face.vertexIndices[j] - 1]);
            makeTriangleCoordinate(triangle.v3, vertices[face.vertexIndices[j + 1] - 1]);
            triangle.normal = computeNormal(triangle.v1, triangle.v2, triangle.v3);

            triangles.push_back(triangle);
        }
    }

    uint32_t numTriangles = triangles.size();
    os.write(reinterpret_cast<const char*>(&numTriangles), sizeof(numTriangles));

    for (const auto& tri : triangles) {

        saveVec3(os,tri.normal);
        saveVec3(os, tri.v1);
        saveVec3(os, tri.v2);
        saveVec3(os, tri.v3);

        uint16_t attributeByteCount = 0;
        os.write(reinterpret_cast<const char*>(&attributeByteCount), sizeof(attributeByteCount));
    }
}

void ObjToStlConverter::makeTriangleCoordinate(BasicVertexDataStructs::Vec3& triangle_v, BasicVertexDataStructs::Vec3& vertex)
{
    triangle_v = vertex;

    std::swap(triangle_v.y, triangle_v.z);
}

void ObjToStlConverter::saveVec3(std::ofstream& os,const BasicVertexDataStructs::Vec3& vec3)
{
    os.write(reinterpret_cast<const char*>(&vec3), sizeof(vec3));
}

BasicVertexDataStructs::Vertex ObjToStlConverter::computeNormal(const BasicVertexDataStructs::Vec3& v1, const BasicVertexDataStructs::Vec3& v2, const BasicVertexDataStructs::Vec3& v3)
{
    BasicVertexDataStructs::Vertex normal;
    float ux = v2.x - v1.x;
    float uy = v2.y - v1.y;
    float uz = v2.z - v1.z;

    float vx = v3.x - v1.x;
    float vy = v3.y - v1.y;
    float vz = v3.z - v1.z;

    normal.x = uy * vz - uz * vy;
    normal.y = uz * vx - ux * vz;
    normal.z = ux * vy - uy * vx;

    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    return normal;
}
 