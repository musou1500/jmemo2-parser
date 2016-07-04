#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <vector>
#include <iterator>
#include <type_traits>
#include <memory>
#include "Token.h"

using namespace std;

template<typename T>
struct IsTokenType
    : std::conditional<
      std::is_same<T, TokenType>::value,
      std::true_type,
      std::false_type>::type {};

class Lexer {
public:
    Lexer() : _input(L""), _hasError(false) {};
    
    bool initWithString(wstring input);
    bool hasError() { return _hasError; };

    template<typename T, typename ... Types> 
    bool matchOrBack(vector<shared_ptr<Token>> &matchResults, T head, Types ...args) {
        static_assert(Lexer::checkTypes(IsTokenType<T>::value) && Lexer::checkTypes(IsTokenType<Types>::value...), "args should be TokenType");
        return matchOrBack(matchResults, head) && matchOrBack(matchResults, args...);
    };

    bool matchOrBack(vector<shared_ptr<Token>> &matchResults, TokenType a) {
        if ((*_nextTokenIterator)->getType() == a) {
            matchResults.push_back(*_nextTokenIterator);
            _nextTokenIterator++;
            return true;
        } else {
            return false;
        }
    }
    
    shared_ptr<Token> getNextToken() {
        if (_nextTokenIterator == _tokens.end()) {
            return nullptr;
        } else {
            return (*_nextTokenIterator);
        }
    }
private:

    template<typename ... Types>
    constexpr static bool checkTypes(bool b, Types ... rest) {
        return b && checkTypes(rest...);
    }

    constexpr static bool checkTypes(bool b) {
        return b;
    }


    wstring _input;
    vector<shared_ptr<Token>> _tokens;
    bool _hasError;
    vector<shared_ptr<Token>>::iterator _nextTokenIterator;
};
#endif
