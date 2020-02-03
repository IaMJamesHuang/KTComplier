//
//  FileWriter.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/3.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "FileWriter.hpp"

FileWriter::FileWriter(const std::string &p_fileName) {
    fileName = p_fileName;
    ofile = nullptr;
    isOpen = false;
}

FileWriter::~FileWriter() {
    if (isOpen) {
        ofile -> close();
    }
    delete ofile;
}

void FileWriter::start() {
    if (!isOpen) {
        ofile = new std::fstream(fileName, std::ios::out | std::ios::trunc);
        isOpen = true;
    } else {
        throw "can't open same stream twice";
    }
}

void FileWriter::writeString(const std::string &sourceString) {
    *ofile << sourceString << std::endl;
}

std::fstream & FileWriter::getFileStream() {
    return *ofile;
}

void FileWriter::end() {
    if (isOpen) {
        ofile -> close();
        isOpen = false;
    } else {
        throw "can't close an unopen stream";
    }
}
