/*
  ==============================================================================

    ObjFileFormat.cpp
    Created: 20 Jul 2024 2:32:41pm
    Author:  Padol

  ==============================================================================
*/

#include "ObjFileFormat.h"

ObjFileFormat::ObjFileFormat()
{
}

ObjFileFormat::~ObjFileFormat()
{
}

void ObjFileFormat::scale(float x_scale_factor, float y_scale_factor, float z_scale_factor)
{

    for (auto& vertex : vertices.getDatas()) {
        scaleVec3(vertex,x_scale_factor,y_scale_factor,z_scale_factor);
    }
}

void ObjFileFormat::rotate(float angle, char axis)
{
    float radians = angle * M_PI / 180.0f;
    float cosA = cos(radians);
    float sinA = sin(radians);

    for (auto& vertex : vertices.getDatas()) {
        
        rotateVec3(vertex, cosA, sinA, axis);
    }

}

void ObjFileFormat::translate(float dx, float dy, float dz)
{
    
    for (auto& vertex : vertices.getDatas()) {
        translateVec3(vertex, dx, dy, dz);

    }
}

bool ObjFileFormat::isPointInObject(BasicVertexDataStructs::Vec3& point_question)
{

    std::vector<BasicVertexDataStructs::Triangle> triangles;
    makeTriangles(triangles);
    

    BasicVertexDataStructs::Vec3 rayDir = { 1.0f, 0.0f, 0.0f }; // Arbitrary direction
    int intersectionCount = 0;
    BasicVertexDataStructs::Vec3 intersectionPoint;

    for (const auto & tri : triangles) {
        if (rayIntersectsTriangle(point_question, rayDir, tri, intersectionPoint)) {
            intersectionCount++;
        }
    }


    return (intersectionCount % 2) == 1;
}

float ObjFileFormat::calculateSurface()
{
    std::vector<BasicVertexDataStructs::Triangle> triangles;
    makeTriangles(triangles);

    float total_surface_area = 0.0f;
    for (const auto& triangle : triangles) {

        total_surface_area += triangleArea(triangle.v1, triangle.v2, triangle.v3);
    }


    return total_surface_area;
}

float ObjFileFormat::calculateVolume()
{

    std::vector<BasicVertexDataStructs::Triangle> triangles;
    makeTriangles(triangles);

    float total_volume = 0.0f;
    for (const auto& triangle : triangles) {

        total_volume += tetrahedronVolume(triangle.v1, triangle.v2, triangle.v3);
    }

    return total_volume;
}

void ObjFileFormat::makeTriangles(std::vector<BasicVertexDataStructs::Triangle>& triangles)
{

    for (size_t i = 0; i < faces.getDatas().size(); ++i) {

        const BasicVertexDataStructs::Face face = faces.getDatas()[i];

        for (size_t j = 1; j + 1 < face.vertexIndices.size(); ++j) {

            BasicVertexDataStructs::Triangle triangle;

            makeTriangleCoordinate(triangle.v1, vertices.getDatas()[face.vertexIndices[0] - 1]);
            makeTriangleCoordinate(triangle.v2, vertices.getDatas()[face.vertexIndices[j] - 1]);
            makeTriangleCoordinate(triangle.v3, vertices.getDatas()[face.vertexIndices[j + 1] - 1]);

            triangles.push_back(triangle);
        }
    }
}

void ObjFileFormat::makeTriangleCoordinate(BasicVertexDataStructs::Vec3& triangle_v, BasicVertexDataStructs::Vec3& vertex)
{

    triangle_v = vertex;

    std::swap(triangle_v.y, triangle_v.z);
}


bool ObjFileFormat::rayIntersectsTriangle(const BasicVertexDataStructs::Vec3& p, const BasicVertexDataStructs::Vec3& d, const BasicVertexDataStructs::Triangle& tri, BasicVertexDataStructs::Vec3& outIntersectionPoint) {
    const float EPSILON = 0.0000001;
    BasicVertexDataStructs::Vec3 v0v1 = { tri.v2.x - tri.v1.x, tri.v2.y - tri.v1.y, tri.v2.z - tri.v1.z };
    BasicVertexDataStructs::Vec3 v0v2 = { tri.v3.x - tri.v1.x, tri.v3.y - tri.v1.y, tri.v2.z - tri.v1.z };
    BasicVertexDataStructs::Vec3 pvec = { d.y * v0v2.z - d.z * v0v2.y, d.z * v0v2.x - d.x * v0v2.z, d.x * v0v2.y - d.y * v0v2.x };
    float det = v0v1.x * pvec.x + v0v1.y * pvec.y + v0v1.z * pvec.z;

    if (det > -EPSILON && det < EPSILON) return false;
    float invDet = 1 / det;

    BasicVertexDataStructs::Vec3 tvec = { p.x - tri.v1.x, p.y - tri.v1.y, p.z - tri.v1.z };
    float u = (tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z) * invDet;
    if (u < 0 || u > 1) return false;

    BasicVertexDataStructs::Vec3 qvec = { tvec.y * v0v1.z - tvec.z * v0v1.y, tvec.z * v0v1.x - tvec.x * v0v1.z, tvec.x * v0v1.y - tvec.y * v0v1.x };
    float v = (d.x * qvec.x + d.y * qvec.y + d.z * qvec.z) * invDet;
    if (v < 0 || u + v > 1) return false;

    float t = (v0v2.x * qvec.x + v0v2.y * qvec.y + v0v2.z * qvec.z) * invDet;
    if (t > EPSILON) {
        outIntersectionPoint = { p.x + d.x * t, p.y + d.y * t, p.z + d.z * t };
        return true;
    }

    return false;
}

