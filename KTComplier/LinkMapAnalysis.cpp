//
//  LinkMapAnalysis.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/1/22.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "LinkMapAnalysis.hpp"
#include "StringHelper.hpp"
#include <vector>

static const std::string kOBJECT_FILE = "# Object files:";
static const std::string kSECTIONS = "# Sections:";
static const std::string kSYMBOLS = "# Symbols:";

bool checkLinkMapContent(std::string &linkMapContent) {
    //判断文件里是否有Object files、Sections、Symbols字段
    long objectResult = linkMapContent.find(kOBJECT_FILE, 0);
    long sectionsResult = linkMapContent.find(kSECTIONS, 0);
    long symbolsResult = linkMapContent.find(kSYMBOLS, 0);
    if (objectResult != std::string::npos &&
        sectionsResult != std::string::npos &&
        symbolsResult != std::string::npos) {
        return true;
    }
    return false;
}

std::map<std::string, SymbolModel> symbolMapForLinkMapContent(std::string &linkMapContent) {
    std::map<std::string, SymbolModel> symboMap;
    std::vector<std::string> contentLines = split(linkMapContent, "\n");
    
    bool reachFiles = false;
    bool reachSymbols = false;
    bool reachSections = false;
    
    for (std::string line : contentLines) {
        if (hasPrefix(line, "#")) {
            if (hasPrefix(line, kOBJECT_FILE)) {
                reachFiles = true;
            } else if (hasPrefix(line, kSECTIONS)) {
                reachSections = true;
            } else if (hasPrefix(line, kSYMBOLS)) {
                reachSymbols = true;
            }
        } else {
            if (reachFiles && !reachSections && !reachSymbols) {
                //通过# Object files:拿到输出文件列表
                long pos = line.find("]");
                if (pos != line.npos) {
                    std::string key = line.substr(0, pos + 1);
                    std::string fileName = line.substr(pos + 1, line.size() - pos);
                    SymbolModel model(fileName, 0);
                    symboMap[key] = model;
                }
            } else if (reachFiles && reachSections && !reachSymbols) {
                //sections块的信息都包含在Symbols块里，统计维度不同，可以看到sections和symbols都是按顺序排列的。
                //__TEXT存放的是编译后的代码，权限为只读可执行（r-x）
                //一种可行的优化APP启动时间的方案是：
                //通过GUN C编译指令__attribute__将某些启动时需要执行的block回调函数放到指定的__TEXT段中。
                //避免回调函数分布到各个物理帧中（启动时执行回调函数就会发生大量的缺页中断，增加启动耗时）
            } else if (reachFiles && reachSections && reachSymbols) {
                std::vector<std::string> symbolsVector = split(line, "\t");
                if (symbolsVector.size() == 3) {
                    std::string fileKeyAndName = symbolsVector[2];
                    uint64_t size = strtoul(symbolsVector[1].c_str(), 0, 16);
                    long pos = fileKeyAndName.find("]");
                    if (pos != line.npos) {
                        std::string key = fileKeyAndName.substr(0, pos + 1);
                        SymbolModel &symbol = symboMap[key];
                        uint64_t p_size = symbol.getSize();
                        symbol.setSize(size + p_size);
                    }
                }
            }
        }
    }
    
    return symboMap;
}

void showLinkMap(std::map<std::string, SymbolModel> map) {
    // /会被裁减掉
    showLinkMap(map, "/");
}

void showLinkMap(std::map<std::string, SymbolModel> map, std::string modelName) {
    long pos = modelName.find(".a");
    if (pos == modelName.npos && modelName != "/") {
        modelName = modelName + ".a";
    }
    unsigned long totalSize = 0;
    std::vector<std::pair<std::string, SymbolModel>> symbolModelList(map.begin(), map.end());
    sort(symbolModelList.begin(), symbolModelList.end(), symbolSortFunction);
    for (std::pair<std::string, SymbolModel> sPair : symbolModelList) {
        SymbolModel model = sPair.second;
        if (model.getFileName().find(modelName) != modelName.npos) {
            totalSize += model.getSize();
            std::string outputFileName = getOutPutName(model.getFileName(), modelName);
            std::cout << "fileName: " << outputFileName << "\tsize: " << (float)model.getSize() / 1024 << "KB" << std::endl;
        }
    }
    std::cout << "Total Size: " << (float)totalSize / 1024 << "KB\n";
}

bool symbolSortFunction(const std::pair<std::string, SymbolModel> &sym1, const std::pair<std::string, SymbolModel> &sym2) {
    return sym1.second.getSize() > sym2.second.getSize();
}
