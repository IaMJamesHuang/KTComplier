//
//  StringHelper.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include "StringHelper.hpp"

std::vector<std::string>split(const std::string& s, const std::string& delim) {
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len)
    {
        long find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

bool hasPrefix(const std::string &s, const std::string &prefix) {
    long pos = s.find(prefix);
    return pos == 0;
}

std::string readFileIntoString(const char *fileName) {
    std::ifstream ifile(fileName);
    std::ostringstream buf;
    char ch;
    while( buf && ifile.get(ch) ) {
        buf.put(ch);
    }
    return buf.str();
}

std::string getOutPutName(const std::string &sourceStr, const std::string &modelName) {
    std::vector<std::string> stringVector = split(sourceStr, "/");
    long modelNamePos = stringVector.size() - 2;
    if (modelNamePos > 0 && stringVector[modelNamePos] == modelName) {
        std::string outPutStr = stringVector[modelNamePos] + "/" + stringVector[stringVector.size() - 1];
        return outPutStr;
    }
    return sourceStr;
}

std::string getPureName(const std::string &sourceStr) {
    std::vector<std::string> stringVector = split(sourceStr, "/");
    std::string temp = stringVector[stringVector.size() - 1];
    std::vector<std::string> tempvector = split(temp, "(");
    std::string result = tempvector[tempvector.size() - 1];
    result = result.substr(0, result.size() - 1);
    return result;
}
