/*
  ==============================================================================

    FileFormatInterface.h
    Created: 20 Jul 2024 2:33:43pm
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include <vector>
#include "../VertexDatas/BasicVertexDataStructs.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//An interfeace for file formats, for destructor, ...
class FileFormatInterface {


public:

    virtual ~FileFormatInterface() = default;


    virtual void scale(float x_scale_factor, float y_scale_factor, float z_scale_factor) = 0;
    virtual void rotate(float angle, char axis) = 0;
    virtual void translate(float dx, float dy, float dz) = 0;
    virtual bool isPointInObject(BasicVertexDataStructs::Vec3& point_question) = 0;
    virtual float calculateSurface() = 0;
    virtual float calculateVolume() = 0;
 //   virtual void manageFileLoad(const std::string& identifier) = 0;

protected:

    void rotateVec3(BasicVertexDataStructs::Vec3& vec3,float& cos_a, float& sin_a, char& axis) {

            float x = vec3.x;
            float y = vec3.y;
            float z = vec3.z;
            if (axis == 'x') {
                vec3.y = y * cos_a - z * sin_a;
                vec3.z = y * sin_a + z * cos_a;
            }
            else if (axis == 'y') {
                vec3.x = x * cos_a + z * sin_a;
                vec3.z = -x * sin_a + z * cos_a;
            }
            else if (axis == 'z') {
                vec3.x = x * cos_a - y * sin_a;
                vec3.y = x * sin_a + y * cos_a;
            }
    }

    void scaleVec3(BasicVertexDataStructs::Vec3& vec3, float x_scale_factor, float y_scale_factor, float z_scale_factor) {

            vec3.x *= x_scale_factor;
            vec3.y *= y_scale_factor;
            vec3.z *= z_scale_factor;
    }

    void translateVec3(BasicVertexDataStructs::Vec3& vec3, float dx, float dy, float dz) {

            vec3.x += dx;
            vec3.y += dy;
            vec3.z += dz;
    }


    // Compute the area of a triangle given its vertices
    float triangleArea(const BasicVertexDataStructs::Vec3& v1, const BasicVertexDataStructs::Vec3& v2, const BasicVertexDataStructs::Vec3& v3) {
        BasicVertexDataStructs::Vec3 a = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
        BasicVertexDataStructs::Vec3 b = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
        BasicVertexDataStructs::Vec3 cross = crossProduct(a, b);
        return 0.5f * magnitude(cross);
    }

    // Compute the magnitude of a vector
    float magnitude(const BasicVertexDataStructs::Vec3& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }


    // Compute the cross product of two vectors
    BasicVertexDataStructs::Vec3 crossProduct(const BasicVertexDataStructs::Vec3& a, const BasicVertexDataStructs::Vec3& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    // Compute the dot product of two vectors
    float dotProduct(const BasicVertexDataStructs::Vec3& a, const BasicVertexDataStructs::Vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }


    // Compute the volume of a tetrahedron formed by the origin and a triangular face
    float tetrahedronVolume(const BasicVertexDataStructs::Vec3& v1, const BasicVertexDataStructs::Vec3& v2, const BasicVertexDataStructs::Vec3& v3) {
        BasicVertexDataStructs::Vec3 cross = crossProduct(v2, v3);
        return std::abs(dotProduct(v1, cross)) / 6.0f;
    }
};