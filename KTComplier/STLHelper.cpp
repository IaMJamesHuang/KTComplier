//
//  STLHelper.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/23.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "STLHelper.hpp"
#include "StringHelper.hpp"
#include <cmath>

std::vector<SymbolModel> mapToVector(const std::map<std::string, SymbolModel> &map) {
    std::vector<SymbolModel> result;
    for (auto item : map) {
        result.push_back(item.second);
    }
    return result;
}

//求交集
std::vector<std::pair<SymbolModel, SymbolModel>> intersection(const std::vector<SymbolModel> &vector1, const std::vector<SymbolModel> &vector2) {
    std::vector<std::pair<SymbolModel, SymbolModel>> result;
    //不存在同名文件
    for (auto item1 : vector1) {
        for (auto item2 : vector2) {
            if (item1.getFileName() == item2.getFileName()) {
                result.push_back(std::pair<SymbolModel, SymbolModel>(item1, item2));
            }
        }
    }
    return result;
}

//求差集
std::vector<SymbolModel> difference(const std::vector<std::pair<SymbolModel, SymbolModel>> &originVector, const std::vector<SymbolModel> &allVector) {
    std::vector<SymbolModel> result;
    for (auto item : allVector) {
        if (!inPairVector(originVector, item)) {
            result.push_back(item);
        }
    }
    return result;
}

bool inPairVector(const std::vector<std::pair<SymbolModel, SymbolModel>> &vector, const SymbolModel &model) {
    for (auto item : vector) {
        if (item.first.getFileName() == model.getFileName()) {
            return true;
        }
    }
    return false;
}

std::vector<SymbolModel> pairVectorToModelVector(const std::vector<std::pair<SymbolModel, SymbolModel>> &pairVector) {
    std::vector<SymbolModel> result;
    for (auto item : pairVector) {
        SymbolModel item1 = item.first;
        SymbolModel item2 = item.second;
        if (fabs(item1.getSize() - item2.getSize()) > 0.05) {
            SymbolModel model;
            model.setFileName(item1.getFileName());
            model.setSize(item2.getSize() - item1.getSize());
            result.push_back(model);
        }
    }
    return result;
}

std::vector<SymbolModel> filterVector(std::vector<SymbolModel> &vector, std::string &modelName) {
    std::vector<SymbolModel> result;
    for (auto item : vector) {
        if (item.getFileName().find(modelName) != modelName.npos) {
            SymbolModel symbol;
            symbol.setFileName(getPureName(item.getFileName()));
            symbol.setSize(item.getSize());
            result.push_back(symbol);
        }
    }
    return result;
}


