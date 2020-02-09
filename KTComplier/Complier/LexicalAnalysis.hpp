//
//  LexicalAnalysis.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/7.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef LexicalAnalysis_hpp
#define LexicalAnalysis_hpp

#include <stdio.h>
#include "Token.hpp"
#include <map>
#include <string>
#include <fstream>
/*
 * 简单的编译器前端，完成从源代码 -》中间代码（四元表达式）的解析过程
 * 程序的产生式如下：(e表示空产生式，id表示标志符，basic表示基本类型)
 * program -> block
 * block -> { decls stmts}
 * decls -> decls decl | e
 * decl -> type id;
 * type -> type [num] | basic
 * stmts -> stmts stmt | e
 * ... 待补充
 */

class LexicalAnalysis {
private:
    int line;
    char peek;
    std::map<std::string, Word *> *words;
    std::ifstream *fstream;
public:
    LexicalAnalysis(std::string filePath);
    ~LexicalAnalysis();
    void readch();
    bool readch(const char &c);
    Token scan();
};

#endif /* LexicalAnalysis_hpp */
