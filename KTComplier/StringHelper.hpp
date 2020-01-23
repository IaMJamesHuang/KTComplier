//
//  StringHelper.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef StringHelper_hpp
#define StringHelper_hpp

#include <stdio.h>
#include <string>
#include <vector>

std::vector<std::string>split(const std::string &s, const std::string &delim);

bool hasPrefix(const std::string &s, const std::string &prefix);

std::string readFileIntoString(const char *fileName);

std::string getOutPutName(const std::string &sourceStr, const std::string &modelName);

#endif /* StringHelper_hpp */
