/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <iostream>
#include <string>
#include "FileLoader/ObjFileLoader/ObjFileLoader.h"
#include "FileFormats/ObjFileFormat/ObjFileFormat.h"
#include "FileSaver/ObjFileSaver/ObjFileSaver.h"
#include "FileSaver/StlFileSaver/ObjToStlConverter.h"

ObjFileLoader fl;
ObjFileSaver fs;
ObjToStlConverter otsc;
std::unique_ptr<ObjFileFormat> obj_file;


void load() {

    //"F:\\Bedando\\cilinder.obj"

    std::string input;
    std::cout << "Give the full path of the file like: F:\\box.obj" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);

    bool is_loaded = fl.loadFile(input, obj_file.get());

    if (is_loaded) {

        std::cout << "The file is loaded" << std::endl;

    }
    else {

        std::cout << "LOAD ERROR" << std::endl;

    }
}


void save() {

    std::string input;
    std::cout << "Give the full path of the file where you want to save the obj like:  F:\\saved_box.obj" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);

    fs.saveFile(input, obj_file.get());


}


void objToStl() {

    std::string input;
    std::cout << "Give the full path of the file where you want to save the stl like:  F:\\saved_box.stl" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);

    otsc.saveFile(input, obj_file.get());
}


void scale() {

    std::string input;
    std::cout << "Scale the object with x_scale, y_scale, z_scale (write 1 for no change) like:  1 2 3" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    BasicVertexDataStructs::Vec3 point_question;

    iss >> point_question.x >> point_question.y >> point_question.z;

    if (iss.fail()) {

        std::cout << "BAD scale format!" << std::endl;
    }
    else {

        obj_file->scale(point_question.x, point_question.y, point_question.z);
        std::cout << "x scaled with: " << point_question.x << " y scaled with: " << point_question.y << " z scaled with: " << point_question.z << std::endl;

    }


}


void rotate() {


    std::string input;
    std::cout << "Rotate the object with angle with the give axis, like:  180 z" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);
    std::istringstream iss(input);

    float angle;
    char axis;

    iss >> angle >> axis;

    if (iss.fail()) {

        std::cout << "BAD scale format!" << std::endl;
    }
    else {

        obj_file->rotate(angle, axis);
        std::cout << "The object rotated with: " << angle << " trought: " << axis << " axis" << std::endl;
    }



}


void translate() {


    std::string input;
    std::cout << "Translate the object with x_translate, y_translate, z_translate like:  1 2 3" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    BasicVertexDataStructs::Vec3 point_question;

    iss >> point_question.x >> point_question.y >> point_question.z;

    if (iss.fail()) {

        std::cout << "BAD translate format!" << std::endl;
    }
    else {

        obj_file->translate(point_question.x, point_question.y, point_question.z);

        std::cout << "x translated with: " << point_question.x << " y translated with: " << point_question.y << " z translated with: " << point_question.z << std::endl;

    }

}


void findPointInObject() {

    std::string input;
    std::cout << "Find, if the given point by you is inside the object. Give the point like:  1 2 3" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);

    std::istringstream iss(input);

    BasicVertexDataStructs::Vec3 point_question;

    iss >> point_question.x >> point_question.y >> point_question.z;

    if (iss.fail()) {

        std::cout << "BAD point format!" << std::endl;
    }
    else {

        if (obj_file->isPointInObject(point_question)) {

            std::cout << "P(" << point_question.x << ";" << point_question.y << ";" << point_question.z << ") point is INSIDE the object" << std::endl;
        }
        else {

            std::cout << "P(" << point_question.x << ";" << point_question.y << ";" << point_question.z << ") point is OUTSIDE the object" << std::endl;
        }
    }
}


void surface() {

    std::cout << "The surface of the object is: " << obj_file->calculateSurface() << std::endl;

}
void volume() {

    std::cout << "The volume of the object is: " << obj_file->calculateVolume() << std::endl;

}

bool loadCheck() {

    if (obj_file) {

        return true;
    }

    return false;
}

void badCommand(std::string& input) {

    if (loadCheck()) {

        std::cout << "INVALID command." << std::endl;

    }
    else {

        std::cout << "INVALID command, because the file hasnt loaded yet!" << std::endl;

    }
}



void commandList() {

    std::cout << "You have the following commands (you have to write the command and enter first, then write the needed data (if the command needs any)):" << std::endl;
    std::cout << "> exit" << std::endl;
    std::cout << "> load" << std::endl;
    std::cout << "> save" << std::endl;
    std::cout << "> obj to stl" << std::endl;
    std::cout << "> scale" << std::endl;
    std::cout << "> rotate" << std::endl;
    std::cout << "> translate" << std::endl;
    std::cout << "> find point in object" << std::endl;
    std::cout << "> surface" << std::endl;
    std::cout << "> volume" << std::endl;
    std::cout << std::endl << std::endl << std::endl;

}

//==============================================================================
int main(int argc, char* argv[])
{

    obj_file = std::make_unique<ObjFileFormat>();

    commandList();

    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        bool is_bad_command = true;

        if (input == "exit") {

            break;
        }
        else if (input == "load") {

            is_bad_command = false;
            load();
        }
        else {

            if (loadCheck()) {


                if (input == "save") {

                    is_bad_command = false;
                    save();
                }
                else if (input == "obj to stl") {

                    is_bad_command = false;
                    objToStl();
                }
                else if (input == "scale") {

                    is_bad_command = false;
                    scale();
                }
                else if (input == "rotate") {

                    is_bad_command = false;
                    rotate();
                }
                else if (input == "translate") {

                    is_bad_command = false;
                    translate();
                }
                else if (input == "find point in object") {

                    is_bad_command = false;
                    findPointInObject();
                }
                else if (input == "surface") {

                    is_bad_command = false;
                    surface();
                }
                else if (input == "volume") {

                    is_bad_command = false;
                    volume();
                }
            }
            else {

                std::cout << "File hasnt loaded yet!" << std::endl;
            }


        }
       


        if (is_bad_command ) {

            badCommand(input);

        }
    }

    return 0;
}


