/*
  ==============================================================================

    FileSaverInterface.h
    Created: 20 Jul 2024 6:55:25pm
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
class FileSaverInterface {

public:

    virtual ~FileSaverInterface() = default;

    virtual void manageFileSave( std::ofstream& os, FileFormat* file_format) = 0;


    bool saveFile(const std::string& file_path, FileFormat* file_format) {

        std::ofstream out_file = makeOstream(file_path);

        if (!out_file.is_open()) {
            std::cerr << "Failed to open file: " << file_path << std::endl;
            return false;
        }

        manageFileSave(out_file, file_format);

        out_file.close();


        std::cout << "OBJ file saved as " << file_path << std::endl;

        return true;
    }

protected:

    bool is_binary_file = false;


private:

    std::ofstream makeOstream(const std::string& file_path) {

        if (is_binary_file) {

            std::ofstream out_file(file_path, std::ios::binary);
            return out_file;
        }

            std::ofstream out_file(file_path);
            return out_file;
    }

};