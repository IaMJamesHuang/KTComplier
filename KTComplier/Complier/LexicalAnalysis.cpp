//
//  LexicalAnalysis.cpp
//  KTComplier
//
//  Created by 黄嘉豪 on 2020/2/7.
//  Copyright © 2020 黄嘉豪. All rights reserved.
//

#include "LexicalAnalysis.hpp"

using namespace std;

LexicalAnalysis::LexicalAnalysis(std::string filePath) :line(1), peek(' ') {
    words = new map<std::string, Word *>();
    fstream = new ifstream(filePath);
}

LexicalAnalysis::~LexicalAnalysis() {
    if (fstream && fstream -> is_open()) {
        fstream -> close();
    }
    delete fstream;
    delete words;
}

void LexicalAnalysis::readch() {
    if (fstream -> is_open()) {
        fstream -> get(peek);
        if (!peek) {
            fstream -> close();
        }
    }
}

bool LexicalAnalysis::readch(const char &c) {
    readch();
    if (peek !=c ) {
        return false;
    } else {
        peek = ' ';
        return true;
    }
}

Token LexicalAnalysis::scan() {
    while (true) {
        readch();
        if (peek == ' ' || peek == '\t') {
            continue;
        } else if (peek == '\n') {
            line = line + 1;
        } else {
            break;
        }
    }
    
    switch (peek) {
        case '&':
            if (readch('&')) {
                return kAnd;
            } else {
                return Token('&');
            }
        case '|':
            if (readch('|')) {
                return kOr;
            } else {
                return Token('|');
            }
        case '=':
            if (readch('=')) {
                return kEq;
            } else {
                return Token('=');
            }
        case '!':
            if (readch('=')) {
                return kNe;
            } else {
                return Token('!');
            }
        case '<':
            if (readch('=')) {
                return kLe;
            } else {
                return Token('<');
            }
        case '>':
            if (readch('=')) {
                return kGe;
            } else {
                return Token('>');
            }
        default:
            break;
    }
    if (isdigit(peek)) {
        int v = 0;
        do {
            v = 10 * v + peek;
            readch();
        } while (isdigit(peek));
        //错误处理：8ab
        if (peek != '.') {
            return Num(v);
        }
        float x = v;
        float d = 10;
        while (true) {
            readch();
            //错误处理8.ab
            if (!isdigit(peek)) {
                break;
            }
            x = x + peek / d;
            d = d * 10;
        }
        return Real(x);
    }
    if (isalpha(peek)) {
        string b;
        do {
            b = b + peek;
            readch();
        } while (isalpha(peek) || isdigit(peek));
        if ((*words).count(b)) {
            return *((*words)[b]);
        } else {
            Word *w = new Word(ID, b) ;
            (*words)[b] = w;
            return *w;
        }
    }
    Token token(peek);
    peek = ' ';
    return token;
}

