/*
  ==============================================================================

    ObjFileSaver.h
    Created: 20 Jul 2024 7:07:33pm
    Author:  Padol

  ==============================================================================
*/

#pragma once

#include "../../VertexDatas/BasicVertexDataStructs.h"
#include "../FileSaverInterface.h"
#include "../../FileFormats/ObjFileFormat/ObjFileFormat.h"



class ObjFileSaver : public FileSaverInterface<ObjFileFormat> {

public:

    ObjFileSaver();
    ~ObjFileSaver() override;

    void manageFileSave( std::ofstream& os, ObjFileFormat* file_format) override;

private:


    //Load the vertex datas into ObjFileFormat* obj_format
    void saveVertex(std::ofstream& os, ObjFileFormat* file_format);

    //Load the vertex normal datas into ObjFileFormat* obj_format
    void saveVertexNormal(std::ofstream& os, ObjFileFormat* file_format);

    //Load the vertex texture datas into ObjFileFormat* obj_format
    void saveVertexTexture(std::ofstream& os, ObjFileFormat* file_format);

    //Load the face datas into ObjFileFormat* obj_format
    void saveFaces(std::ofstream& os, ObjFileFormat* file_format);

};