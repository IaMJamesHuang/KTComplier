//
//  STLHelper.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/23.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef STLHelper_hpp
#define STLHelper_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "SymbolModel.hpp"

std::vector<SymbolModel> mapToVector(const std::map<std::string, SymbolModel> &map);

std::vector<std::pair<SymbolModel, SymbolModel>> intersection(const std::vector<SymbolModel> &vector1, const std::vector<SymbolModel> &vector2);

std::vector<SymbolModel> difference(const std::vector<std::pair<SymbolModel, SymbolModel>> &originVector, const std::vector<SymbolModel> &allVector);

bool inPairVector(const std::vector<std::pair<SymbolModel, SymbolModel>> &vector, const SymbolModel &model);

std::vector<SymbolModel> pairVectorToModelVector(const std::vector<std::pair<SymbolModel, SymbolModel>> &pairVector);

std::vector<SymbolModel> filterVector(std::vector<SymbolModel> &vector, std::string &modelName);

std::vector<SymbolModel> filterVector(std::vector<SymbolModel> &vector, std::vector<std::string> modelList);

bool isModelNameInModelList(SymbolModel &model, std::vector<std::string> &modelList);

#endif /* STLHelper_hpp */
