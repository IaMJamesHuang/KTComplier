//
//  SymbolModel.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "SymbolModel.hpp"

SymbolModel::SymbolModel() {
    fileName = "unfine";
    size = 0;
}

SymbolModel::SymbolModel(std::string p_file_name, int64_t p_size)  {
    fileName = p_file_name;
    size = p_size;
}

SymbolModel::SymbolModel(const SymbolModel &symbol) {
    fileName = symbol.fileName;
    size = symbol.size;
}

SymbolModel::~SymbolModel() {
    
}

SymbolModel & SymbolModel::operator=(const SymbolModel &symbol) {
    if (this != &symbol) {
        fileName = symbol.fileName;
        size = symbol.size;
    }
    return *this;
}

std::string SymbolModel::getFileName() const{
    return fileName;
}

int64_t SymbolModel::getSize() const{
    return size;
}

void SymbolModel::setSize(int64_t p_size) {
    size = p_size;
}

void SymbolModel::setFileName(std::string p_file_name) {
    fileName = p_file_name;
}
