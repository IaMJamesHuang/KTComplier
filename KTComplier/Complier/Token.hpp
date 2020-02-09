//
//  Token.hpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/9.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <string>

enum Tag {
    AND = 256, BASIC = 257, BREAK = 258, DO = 259, ELSE = 260, EQ = 261, KFALSE = 262, GE = 263,
    ID = 264, IF = 265, INDEX = 266, LE = 267, MINUS = 268, NE = 269, NUM = 270, OR = 271, REAL = 272,
    TEMP = 273, KTRUE = 274, WHILE = 275
};

//词法标记
class Token {
protected:
    int tag;
    
public:
    Token(int tag);
};

// 整数类型
class Num : public Token {
protected:
    int value;
    
public:
    Num(int value);
};

//浮点类型
class Real : public Token {
protected:
    float value;
    
public:
    Real(float value);
};

//标志符号、运算符
class Word : public Token{
protected:
    std::string lexeme;
    
public:
    Word(int tag, std::string lexeme);
};

//定义一些词素
extern Word kAnd, kOr, kEq, kNe, kLe, kGe, kMinus, kTrue, kFalse, kTemp;

#endif /* Token_hpp */
