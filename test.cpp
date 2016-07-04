#include <string>
#include <iostream>
#include <fstream>
#include "Jmemo2Parser.h"

using namespace std;

int main(int argc, char const* argv[])
{
    Jmemo2Parser parser;
    parser.initWithFileName("music/SABM.txt");
    cout << "Music info" << endl;
    Music music = parser.getMusic();
    wcout << "Title:" << music.title << endl;
    wcout << "artist:" << music.artist << endl;
    cout << "Level:" << music.level << endl;
    cout << "Difficulty:" << music.difficulty << endl;
    cout << "Offset:" << music.offset << endl;
    wcout << "Music file:" << music.musicFilePath << endl;
    cout << "Bpm changes(time, bpm) {" << endl;
    for(auto dictPair : music.bpmChanges) {
        cout << "  ";
        cout << dictPair.first << ", " << dictPair.second << endl;
    }
    cout << "}" << endl;
    return 0;
}
