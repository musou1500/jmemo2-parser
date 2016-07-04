#ifndef JMEMO2PARSER_H_
#define JMEMO2PARSER_H_
#include <string>
#include <vector>
#include <unordered_map>
#include "Lexer.h"

using namespace std;

enum class Difficulty {
    BASIC,
    ADVANCED,
    EXTREAM
};
typedef struct ParserState {
    int currentTime;
    bool isPreamble;
    ParserState():currentTime(0), isPreamble(true) {};
} ParserState;

typedef struct Music {
    wstring title;
    wstring artist;
    wstring musicFilePath;
    wstring jacketFilePath;
    int level;
    int offset;
    int difficulty;
    unordered_map<int, int> bpmChanges;
    Music()
        : title(L""),
        artist(L""),
        musicFilePath(L""),
        jacketFilePath(L""),
        level(1),
        offset(0) {};
} Music;

typedef struct Note {
    int justTime;
    int panelIndex;
    Note() 
        : justTime(0),
        panelIndex(0) {};
} Note;

class Jmemo2Parser {
public:
    Jmemo2Parser() {};
    void initWithString(string source);
    void initWithFileName(string fileName);
    Music getMusic() { return _music; };
    vector<Note> getNotes() { return _notes; };
    bool parsePreamble();
    bool parseCommand();
    bool parseAssign();
    bool parseMusic();
private:
    vector<Note>_notes;
    Music _music;
    Lexer _lexer;
    ParserState _state;
};

#endif
