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
#include "STLHelper.hpp"

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

void showLinkMap(std::map<std::string, SymbolModel> map, FileWriter &fileWirter) {
    // /会被裁减掉
    showLinkMap(map, "/", fileWirter);
}

void showLinkMap(std::map<std::string, SymbolModel> map, std::string modelName, FileWriter &fileWirter) {
    unsigned long totalSize = 0;
    std::vector<std::pair<std::string, SymbolModel>> symbolModelList(map.begin(), map.end());
    sort(symbolModelList.begin(), symbolModelList.end(), symbolSortFunction);
    for (std::pair<std::string, SymbolModel> sPair : symbolModelList) {
        SymbolModel model = sPair.second;
        if (model.getFileName().find(modelName) != modelName.npos) {
            totalSize += model.getSize();
            std::string outputFileName = getOutPutName(model.getFileName(), modelName);
            std::cout << "fileName: " << outputFileName << "\tsize: " << (float)model.getSize() / 1024 << "KB" << std::endl;
            fileWirter.getFileStream() << "fileName: " << outputFileName << "\tsize: " << (float)model.getSize() / 1024 << "KB" << std::endl;
        }
    }
    std::cout << "Total Size: " << (float)totalSize / 1024 << "KB\n";
    fileWirter.getFileStream() << "Total Size: " << (float)totalSize / 1024 << "KB\n";
}

void showComLinkMap(std::map<std::string, SymbolModel> baseLinkMap,
                    std::map<std::string, SymbolModel> comLinkMap,
                    FileWriter &fileWriter) {
    std::vector<SymbolModel> baseLinkMapVector = mapToVector(baseLinkMap);
    std::vector<SymbolModel> comLinkMapVector = mapToVector(comLinkMap);
    showComLinkMap(baseLinkMapVector, comLinkMapVector, fileWriter);
}

void showComLinkMap(std::vector<SymbolModel> baseLinkMap, std::vector<SymbolModel> comLinkMap, FileWriter &fileWriter) {
    std::vector<std::pair<SymbolModel, SymbolModel>> intersectionVector = intersection(baseLinkMap, comLinkMap);
    //base没有的，就是减少了
    std::vector<SymbolModel> deleteVector = difference(intersectionVector, baseLinkMap);
    sort(deleteVector.begin(), deleteVector.end(), symbolVectorSortFunction);
    
    //com没有的，就是新增了
    std::vector<SymbolModel> newVector = difference(intersectionVector, comLinkMap);
    sort(newVector.begin(), newVector.end(), symbolVectorSortFunction);

    //转成vector便于排序
    std::vector<SymbolModel> interVector = pairVectorToModelVector(intersectionVector);
    sort(interVector.begin(), interVector.end(), symbolVectorSortFunction);

    std::cout << "原有文件增量：\n";
    fileWriter.getFileStream() << "原有文件增量：\n";
    showLinkMapVector(interVector, fileWriter);
    
    std::cout << "新增文件增量：\n";
    fileWriter.getFileStream() << "新增文件增量：\n";
    showLinkMapVector(newVector, fileWriter);

    std::cout << "删除文件减量:\n";
    fileWriter.getFileStream() << "删除文件减量:\n";
    showLinkMapVector(deleteVector, fileWriter);
}

void showLinkMapVector(std::vector<SymbolModel> vector, FileWriter &fileWriter) {
    unsigned long totalSize = 0;
    for (auto item : vector) {
        totalSize += item.getSize();
        std::string outputFileName = getOutPutName(item.getFileName(), "/");
        std::cout << "fileName: " << outputFileName << "\tsize: " << (float)item.getSize() / 1024 << "KB" << std::endl;
        fileWriter.getFileStream() << "fileName: " << outputFileName << "\tsize: " << (float)item.getSize() / 1024 << "KB" << std::endl;
    }
    std::cout << "total size: " << totalSize << std::endl;
    fileWriter.getFileStream() << "total size: " << (float)totalSize / 1024 << "KB" << std::endl;
}

bool symbolSortFunction(const std::pair<std::string, SymbolModel> &sym1, const std::pair<std::string, SymbolModel> &sym2) {
    return sym1.second.getSize() > sym2.second.getSize();
}

bool symbolVectorSortFunction(const SymbolModel &sym1, const SymbolModel &sym2) {
    return sym1.getSize() > sym2.getSize();
}
