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

typedef struct MatchResult {
    int backTrackTo;
    vector<shared_ptr<Token>> tokens;
    MatchResult() : backTrackTo(-1) {};
} MatchResult;

class Lexer {
public:
    Lexer() : _input(L""), _hasError(false), _curTokenIndex(0){};
    
    bool initWithString(wstring input);
    bool hasError() { return _hasError; };

    template<typename T, typename ... Types> 
    bool matchOrBack(MatchResult &matchResult, T head, Types ...args) {
        static_assert(Lexer::checkTypes(IsTokenType<T>::value) && Lexer::checkTypes(IsTokenType<Types>::value...), "args should be TokenType");
        if (matchResult.backTrackTo < 0) {
            matchResult.backTrackTo = _curTokenIndex;
        }
        bool res = matchOrBack(matchResult, head) && matchOrBack(matchResult, args...);
        return res;
    };

    bool matchOrBack(MatchResult &matchResult, TokenType a) {
        shared_ptr<Token> token = nextToken();
        if (token->getType() == a) {
            matchResult.tokens.push_back(token);
            return true;
        } else {
            backTrack(matchResult.backTrackTo);
            return false;
        }
    }
    
    shared_ptr<Token> nextToken() {
        if (_curTokenIndex > static_cast<int>(_tokens.size()) - 1) {
            return nullptr;
        } else {
            return _tokens[_curTokenIndex++];
        }
    }

    shared_ptr<Token> curToken() {
        return _tokens[_curTokenIndex];
    }
    void backTrack(int i) {
        if (i >= 0 && i <= static_cast<int>(_tokens.size()) - 1) {
            _curTokenIndex = i;
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
    int _curTokenIndex;
};
#endif
