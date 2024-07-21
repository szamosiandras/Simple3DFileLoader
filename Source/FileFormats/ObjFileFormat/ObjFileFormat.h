/*
  ==============================================================================

    ObjFileFormat.h
    Created: 20 Jul 2024 2:32:41pm
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include <vector>
#include <cmath>

#include "../FileFormatInterface.h"
#include "../../VertexDatas/BasicVertexDataStructs.h"

/*Class for manage the obj file, including:
* -(transforms),
* -Add new Vertex(es)
* -Add new VertexNormal(s)
* -Add new VertexTexture(s)
*/




class ObjFileFormat : public FileFormatInterface {

public:

    ObjFileFormat();
    ~ObjFileFormat() override;


    void scale(float x_scale_factor, float y_scale_factor, float z_scale_factor) override;
    void rotate(float angle, char axis) override;
    void translate(float dx, float dy, float dz) override;
    bool isPointInObject(BasicVertexDataStructs::Vec3& point_question) override;
    float calculateSurface() override;
    float calculateVolume() override;


    VertexContainer<BasicVertexDataStructs::Vertex> vertices;
    VertexContainer<BasicVertexDataStructs::VertexNormal> vertex_normals;
    VertexContainer<BasicVertexDataStructs::VertexTexture> vertex_textures;
    VertexContainer<BasicVertexDataStructs::Face> faces;

private:

    void makeTriangles(std::vector<BasicVertexDataStructs::Triangle>& triangles);
    void makeTriangleCoordinate(BasicVertexDataStructs::Vec3& triangle_v, BasicVertexDataStructs::Vec3& vertex);
    bool rayIntersectsTriangle(const BasicVertexDataStructs::Vec3& p, const BasicVertexDataStructs::Vec3& d, const BasicVertexDataStructs::Triangle& tri, BasicVertexDataStructs::Vec3& outIntersectionPoint);

};