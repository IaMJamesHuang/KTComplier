//
//  FileWriter.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/3.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef FileWriter_hpp
#define FileWriter_hpp

#include <stdio.h>
#include <string>
#include <fstream>

class FileWriter {
    
private:
    std::string fileName;
    std::fstream *ofile;
    bool isOpen;
    
public:
    
    FileWriter(const std::string &p_fileName);
    
    ~FileWriter();
    
    void start();
    
    std::fstream & getFileStream();
    
    void writeString(const std::string &sourceString);
        
    void end();
    
};

#endif /* FileWriter_hpp */
