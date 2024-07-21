/*
  ==============================================================================

    ObjToStlConverter.h
    Created: 21 Jul 2024 9:29:46am
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include "../../VertexDatas/BasicVertexDataStructs.h"
#include "../FileSaverInterface.h"
#include "../../FileFormats/ObjFileFormat/ObjFileFormat.h"

class ObjToStlConverter : public FileSaverInterface<ObjFileFormat> {

public:

    ObjToStlConverter();
    ~ObjToStlConverter() override;

    void manageFileSave(std::ofstream& os, ObjFileFormat* file_format) override;


private:

    //Save the header for the STL file
    void saveHeader(std::ofstream& os);

    //Write the triangles into the ofstream, from the obj file format
    void saveTriangles(std::ofstream& os, ObjFileFormat* file_format);

    void makeTriangleCoordinate(BasicVertexDataStructs::Vec3& triangle_v, BasicVertexDataStructs::Vec3& vertex);


    void saveVec3(std::ofstream& os, const BasicVertexDataStructs::Vec3& vec3);


    BasicVertexDataStructs::Vertex computeNormal(const BasicVertexDataStructs::Vec3& v1, const BasicVertexDataStructs::Vec3& v2, const BasicVertexDataStructs::Vec3& v3);

};