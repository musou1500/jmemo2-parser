#include "Jmemo2Parser.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include <wchar.h>
#include <regex>
#include "Lexer.h"
#include "Token.h"

using namespace std;

void Jmemo2Parser::initWithString(string source) {
    // utf8 -> wstringへの変換器
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
    
    // Lexerの初期化
    _lexer.initWithString(cv.from_bytes(source));
    
    // 構文解析
    while(true) {
        if (_state.isPreamble) {
            _state.isPreamble = parsePreamble();
        } else if ( ! parseMusic()){
            break;
        }
    }
};

void Jmemo2Parser::initWithFileName(string filename) {
    ifstream ifs(filename);
    istreambuf_iterator<char> iter(ifs), iter_end;
    initWithString(string(iter, iter_end));
};


bool Jmemo2Parser::parsePreamble() {
    // プリアンブル内ではコマンドか代入のみ許可
    return (parseAssign() || parseCommand());
};

bool Jmemo2Parser::parseMusic() {
    return false;
}

bool Jmemo2Parser::parseAssign() {
    // 変数への代入
    MatchResult matchResult;
    bool assignToVar = _lexer.matchOrBack(
            matchResult,
            TokenType::IDENTIFIER,
            TokenType::EQUAL,
            TokenType::LITERAL);
    
    std::vector<shared_ptr<Token>> matchedTokens = matchResult.tokens;
    if (assignToVar && matchedTokens.size() == 3) {
        wstring name = matchedTokens[0]->getValue();
        shared_ptr<Literal> literal = static_pointer_cast<Literal>(matchedTokens[2]);
        if (name == L"t" && literal->getValueType() == LiteralType::NUMBER) {
            _music.bpmChanges[_state.currentTime] = stoi(literal->getValue());
        } else if (name == L"m" && literal->getValueType() == LiteralType::STRING) {
            _music.musicFilePath = literal->getValue();
        } else if (name == L"o" && literal->getValueType() == LiteralType::NUMBER) {
            auto value = literal->getValue().c_str();
            _music.offset = stoi(literal->getValue());
        } else if (name == L"r" && literal->getValueType() == LiteralType::NUMBER) {
            _music.offset += stoi(literal->getValue());
        }

        return true;
    } else {
        return false;
    }
};

bool Jmemo2Parser::parseCommand() {
    // 代入式付きコマンド
    {
        MatchResult matchResult;
        bool commandWithAssign = _lexer.matchOrBack(
                matchResult,
                TokenType::COMMAND,
                TokenType::EQUAL,
                TokenType::LITERAL);
        vector<shared_ptr<Token>> matchedTokens = matchResult.tokens;
        if (commandWithAssign && matchedTokens.size() == 3) {
            wstring name = matchedTokens[0]->getValue();
            shared_ptr<Literal> literal = static_pointer_cast<Literal>(matchedTokens[2]);
            if (name == L"title") {
                _music.title = literal->getValue();
            } else if (name == L"artist") {
                _music.artist = literal->getValue();
            } else if (name == L"dif" && literal->getValueType() == LiteralType::NUMBER) {
                _music.difficulty = stoi(literal->getValue());
            } else if (name == L"lev" && literal->getValueType() == LiteralType::NUMBER) {
                _music.level = stoi(literal->getValue());
            }

            return true;
        }
    }
    {
        MatchResult matchResult;
        bool command = _lexer.matchOrBack(
                matchResult,
                TokenType::COMMAND);
        if (command) {
            wstring commandName = matchResult.tokens[0]->getValue();
            _music.flags.push_back(commandName);
            return true;
        }
    }
    return false;
};
