#include <string>
#include <iostream>
#include "lexer.h"

Glass::Token::Token(TokenType type, std::string value){
    this->type = type;
    this->value = value;
}

Glass::Token::Token(TokenType type){
    this->type = type;
}

Glass::Token::~Token(){

}

Glass::Lexer::Lexer(std::string code){
    this->code = code;
}

Glass::Lexer::~Lexer(){
}

/*
De un codi doncs torna tokens!
*/
std::vector<Glass::Token>* Glass::Lexer::GetTokens(){
    return &tokenList;
}

std::string Glass::Lexer::nextWord(int pos, int* nextPos){
    std::string nWord = "";
    while(!isEnd(pos)){
        nWord += code[pos];
        pos++;
        if(isEmpty(code[pos]) || isSymbol(code[pos])) break;
    }
    *nextPos = pos;
    return nWord;
}

int Glass::Lexer::isNumber(char c){
    if(c >= 48 && c <= 57) return true;
    return false;
}

int Glass::Lexer::isEmpty(char c){
    return c == typeSymbol[Symbols::SPACE] || c == typeSymbol[Symbols::NEWLINE];
}

void Glass::Lexer::flush(int *next){
    int pos = *next;
    while(isEmpty(code[pos])) pos++;
    *next = pos;
}

int Glass::Lexer::isSemicolon(char c){
    return c == typeSymbol[Symbols::SEMICOLON];
}

int Glass::Lexer::isSeparator(char c){
    return 0;
}

int Glass::Lexer::isComment(char c){
    return c == typeSymbol[Symbols::COMMENT];
}

int Glass::Lexer::isEnd(int pos){
    return pos >= code.size();
}

int Glass::Lexer::isPoint(char c){
    return c == typeSymbol[Symbols::POINT];
}

int Glass::Lexer::isQuot(char c){
    return c == typeSymbol[Symbols::QUOT];
}

int Glass::Lexer::isDoubleQuot(char c){
    return c == typeSymbol[Symbols::DOUBLE_QUOT];
}

int Glass::Lexer::isSymbol(char c){
    return isComment(c) || isPoint(c);
}

void Glass::Lexer::addError(){
    tokenList.push_back(Token(Token::ERROR, ""));
}

void Glass::Lexer::getNumber(int *next){
    int pos = *next;

    std::string num(1, code[pos]);

    int isRational = 0;

    for(pos++; isNumber(code[pos]); pos++){
        num += code[pos];
    }
    
    if(code[pos] == typeSymbol[Symbols::POINT]){
        num += ".";
        isRational = 1;
        for(pos += 1; isNumber(code[pos]); pos++){
            num += code[pos];
        }
    }

    *next = pos;
    
    if(isEmpty(code[pos]) || isSemicolon(code[pos]) || isSeparator(code[pos]) || isEnd(pos)){
        if(isRational) tokenList.push_back(Token(Token::L_REAL, num));
        else tokenList.push_back(Token(Token::L_INT, num));
    } else {
        // Error
        addError();
    }
}

void Glass::Lexer::getString(int *next){
    int pos = *next;
    std::string s = "";

    char check = code[pos];
    pos++;
    while(code[pos] != check){
        if(code[pos] == '\\'){
            if(!isEnd(pos + 1)){
                if(code[pos + 1] == check){
                    s += check;
                    pos += 2;
                    continue;
                }
            } else {
                // Error
                addError();
                return;
            }
        }
        s += code[pos];
        pos++;
    }

    *next = pos;
    tokenList.push_back(Token(Token::L_STRING, s));
    // Sin error

}

void Glass::Lexer::skipComment(int *next){
    if(isComment(code[*next])){
        int pos = *next;
        while(code[pos] != typeSymbol[Symbols::NEWLINE] && !isEnd(pos)){
            pos++;
        }
        *next = pos + 1;
    }
}

void Glass::Lexer::checkLiterals(int *next){
    if(isEnd(*next)) return;

    char c = code[*next];
    if(isNumber(c) || isPoint(c)){
        getNumber(next);
    }
    else if(isQuot(c) || isDoubleQuot(c)){
        getString(next);
    }

    flush(next);
}


void Glass::Lexer::checkKeywords(int *next){
    if(isEnd(*next)) return;
    if(isSymbol(code[*next])) return;
    int pos = *next;
    std::string word;

    int nextPos = pos;
    word = nextWord(pos, &nextPos);
    if(typeKeyword.count(word)){
        switch (typeKeyword[word]){
            case FUNC:
                /* code */
                tokenList.push_back(Token(Token::FUNCTION_DECLARATION));
                break;
            case REAL:
                tokenList.push_back(Token(Token::T_REAL));
                break;
            case INT:
                tokenList.push_back(Token(Token::T_INT));
                break;
            case STRING:
                tokenList.push_back(Token(Token::T_STRING));
                break;
            case BOOLEAN:
                tokenList.push_back(Token(Token::T_BOOLEAN));
                break;
            case TRUE:
                tokenList.push_back(Token(Token::L_TRUE));
                break;
            case FALSE:
                tokenList.push_back(Token(Token::L_FALSE));
                break;
            case _NULL:
                tokenList.push_back(Token(Token::L_NULL));
                break;
            default:
                /* Ha de ser una reference */

                break;
        }
    } else {
        tokenList.push_back(Token(Token::IDENTIFIER, word));    
    }
    *next = nextPos;

    flush(next);
    
}

int Glass::Lexer::GenerateTokens(){
    for(int i = 0; i < code.size(); ){
        skipComment(&i);

        checkLiterals(&i);
        checkKeywords(&i);
    }

    return 0;
}