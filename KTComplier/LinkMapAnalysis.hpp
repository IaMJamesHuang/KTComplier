//
//  LinkMapAnalysis.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef LinkMapAnalysis_hpp
#define LinkMapAnalysis_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include "SymbolModel.hpp"
#include "FileWriter.hpp"

bool checkLinkMapContent(std::string &linkMapContent);

std::map<std::string, SymbolModel> symbolMapForLinkMapContent(std::string &linkMapContent);

void showLinkMap(std::map<std::string, SymbolModel> map, FileWriter &fileWirter);

void showLinkMap(std::map<std::string, SymbolModel> map, std::string modelName, FileWriter &fileWirter);

void showComLinkMap(std::map<std::string, SymbolModel> baseLinkMap, std::map<std::string, SymbolModel> comLinkMap, FileWriter &fileWirter);

void showComLinkMap(std::vector<SymbolModel> baseLinkMap, std::vector<SymbolModel> comLinkMap, FileWriter &fileWirter);

void showLinkMapVector(std::vector<SymbolModel> vector, FileWriter &fileWirter);

bool symbolSortFunction(const std::pair<std::string, SymbolModel> &sym1, const std::pair<std::string, SymbolModel> &sym2);

bool symbolVectorSortFunction(const SymbolModel &sym1, const SymbolModel &sym2);

#endif /* LinkMapAnalysis_hpp */
