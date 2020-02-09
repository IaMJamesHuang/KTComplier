//
//  Token.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/9.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "Token.hpp"
#include <iostream>

Token::Token(int tag) : tag(tag) {
    
}

Num::Num(int value) : Token(NUM), value(value) {
    
}

Real::Real(float value) : Token(REAL), value(value) {
    
}

Word::Word(int tag, std::string lexeme) : Token(tag), lexeme(lexeme) {
    
}

Word kAnd(AND, "&&"), kOr(OR, "||"), kEq(EQ, "=="), kNe(NE, "!="),
kLe(LE, "<="), kGe(GE, ">="), kMinus(MINUS, "minus"), kTrue(KTRUE, "true"),
kFalse(KFALSE, "false"), kTemp(TEMP, "t");
