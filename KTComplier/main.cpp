//
//  main.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include <iostream>
#include <string>
#include "StringHelper.hpp"
#include "LinkMapAnalysis.hpp"

int main(int argc, const char * argv[]) {
    std::string fileName = "/Users/huangjiahao/Desktop/NewsLiteInHouse-LinkMap-arm64.txt";
    std::string content = readFileIntoString(fileName.c_str());
    if (checkLinkMapContent(content)) {
        std::map<std::string, SymbolModel> map = symbolMapForLinkMapContent(content);
        showLinkMap(map);
    }
}
