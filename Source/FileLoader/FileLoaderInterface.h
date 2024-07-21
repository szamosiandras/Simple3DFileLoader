/*
  ==============================================================================

    FileLoaderInterface.h
    Created: 16 Jul 2024 1:56:23pm
    Author:  Padol

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../FileFormats/FileFormatInterface.h"

template <typename FileFormat>
class FileLoaderInterface{
    
public:
    
    virtual ~FileLoaderInterface() = default;

    virtual bool manageFileLoad(const std::string& identifier, FileFormat* file_format) = 0;


    bool loadFile(const std::string& file_path, FileFormat* file_format){
        
        std::ifstream file(file_path);
        
        if(!file.is_open()){
            
            std::cerr << "unable to open file: " << file_path << std::endl;
            return false;
        }
        
        std::string line;
        while(std::getline(file, line)){
            
            if(!manageFileLoad(line, file_format)) {

                return false;
           }
        }
        
        file.close();
        return true;
    }


protected:

    //Chack if the file format is valid for the given line after it set to the proper data structure
    bool checkLineValidity(std::istringstream& iss)
    {

        if (iss.fail()) {

            std::cerr << "Invalid vertex data:" << std::endl;
            return false;
        }

        return true;
    }



};
