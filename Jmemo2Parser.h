#ifndef JMEMO2PARSER_H_
#define JMEMO2PARSER_H_
#include <string>
#include <vector>
#include <array>
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
    vector<pair<int, int>> rhythmBuffer;
    vector<pair<int, int>> placementBuffer;
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
    vector<wstring> flags;
    vector<pair<int, int>> bpmChanges;
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
    int duration;
    Note() 
        : justTime(0),
        panelIndex(0),
        duration(0) {};
} Note;

class Jmemo2Parser {
public:
    Jmemo2Parser() {};
    void initWithString(string source);
    void initWithFileName(string fileName);
    Music getMusic() { return _music; };
    vector<Note> getNotes() { return _notes; };
    bool parseLabel();
    bool parseCommand();
    bool parseAssign();
    bool parseMusic();

    void flushBuffer();
private:
    vector<Note> _notes;
    Music _music;
    Lexer _lexer;
    ParserState _state;
};

#endif
