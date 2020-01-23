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

bool checkLinkMapContent(std::string &linkMapContent);

std::map<std::string, SymbolModel> symbolMapForLinkMapContent(std::string &linkMapContent);

void showLinkMap(std::map<std::string, SymbolModel> map);

void showLinkMap(std::map<std::string, SymbolModel> map, std::string modelName);

bool symbolSortFunction(const std::pair<std::string, SymbolModel> &sym1, const std::pair<std::string, SymbolModel> &sym2);

#endif /* LinkMapAnalysis_hpp */
