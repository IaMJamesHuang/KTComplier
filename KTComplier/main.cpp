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
#include "STLHelper.hpp"

void analysisSingleLinkMap();

void compareLinkMaps();

int main(int argc, const char * argv[]) {
//    analysisSingleLinkMap();
    compareLinkMaps();
    return 0;
}

void analysisSingleLinkMap() {
    std::string fileName = "/Users/huangjiahao/Desktop/NewsLiteInHouse-LinkMap-arm64.txt";
    std::string modelName = "TTShortVideoLiteBusiness";
    std::cout << "start analysis linkmap. \npath: " << fileName << std::endl;
    //todo 改成流式读取
    std::string content = readFileIntoString(fileName.c_str());
    if (checkLinkMapContent(content)) {
        std::map<std::string, SymbolModel> map = symbolMapForLinkMapContent(content);
        showLinkMap(map, modelName);
        std::cout << "done\n";
    } else {
        std::cout << "linkmap file has wrong format\n";
    }
}

void compareLinkMaps() {
    std::string baseLinkMapfileName = "/Users/huangjiahao/Desktop/NewsLiteInHouse-LinkMap-arm64.txt";
    std::string comLinkMapFileName = "/Users/huangjiahao/Downloads/NewsLiteInHouse-LinkMap-arm64.txt";
    std::string baseModelName = "TTShortVideoLiteBusiness";
    std::string comModelName = "TTShortVideoBusinessLite";
    std::cout << "start compare linkmaps. \npath1: " << baseLinkMapfileName << "\npath2: " << comLinkMapFileName << "\n";
    std::string baseContent = readFileIntoString(baseLinkMapfileName.c_str());
    std::string comContent = readFileIntoString(comLinkMapFileName.c_str());
    if (checkLinkMapContent(baseContent) && checkLinkMapContent(comContent)) {
        std::map<std::string, SymbolModel> baseMap = symbolMapForLinkMapContent(baseContent);
        std::map<std::string, SymbolModel> comMap = symbolMapForLinkMapContent(comContent);
        std::vector<SymbolModel> tempBaseVector = mapToVector(baseMap);
        std::vector<SymbolModel> tempComVector = mapToVector(comMap);
        std::vector<SymbolModel> baseVector = filterVector(tempBaseVector, baseModelName);
        std::vector<SymbolModel> comVector = filterVector(tempComVector, comModelName);
        showComLinkMap(baseVector, comVector);
    } else {
        std::cout << "linkmap file has wrong format\n";
    }
}
