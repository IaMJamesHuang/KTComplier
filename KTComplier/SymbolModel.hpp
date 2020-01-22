//
//  SymbolModel.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef SymbolModel_hpp
#define SymbolModel_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class SymbolModel {
private:
    std::string fileName;  //.o文件名称
    uint64_t size; //大小
    
public:
    SymbolModel(std::string p_file_name, uint64_t p_size);
    SymbolModel();
    SymbolModel(const SymbolModel &symbol);
    ~ SymbolModel();
    SymbolModel & operator=(const SymbolModel &symbol);
    
    std::string getFileName();
    uint64_t getSize();
    
    void setFileName(std::string p_file_name);
    void setSize(uint64_t p_size);
    
};

#endif /* SymbolModel_hpp */
