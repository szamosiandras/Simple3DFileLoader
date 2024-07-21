/*
  ==============================================================================

    ObjFileLoader.h
    Created: 20 Jul 2024 2:17:13pm
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include "../../VertexDatas/BasicVertexDataStructs.h"
#include "../FileLoaderInterface.h"
#include "../../FileFormats/ObjFileFormat/ObjFileFormat.h"



class ObjFileLoader : public FileLoaderInterface<ObjFileFormat> {

public:

    ObjFileLoader();
    ~ObjFileLoader() override;

    bool manageFileLoad(const std::string& line, ObjFileFormat* file_format) override;


private:

    //Load the vertex datas into ObjFileFormat* obj_format
    bool loadVertex(std::istringstream& iss, ObjFileFormat* file_format);

    //Load the vertex normal datas into ObjFileFormat* obj_format
    bool loadVertexNormal(std::istringstream& iss, ObjFileFormat* file_format);

    //Load the vertex texture datas into ObjFileFormat* obj_format
    bool loadVertexTexture(std::istringstream& iss, ObjFileFormat* file_format);

    //Load the face datas into ObjFileFormat* obj_format
    bool loadFaces(std::istringstream& iss, ObjFileFormat* file_format);

};