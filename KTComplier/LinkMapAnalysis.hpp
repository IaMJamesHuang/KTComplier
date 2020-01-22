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

#endif /* LinkMapAnalysis_hpp */
