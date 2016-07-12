#include <string>
#include <iostream>
#include <fstream>
#include "Jmemo2Parser.h"

using namespace std;

int main(int argc, char const* argv[])
{
    Jmemo2Parser parser;
    parser.initWithFileName("music/SABM.txt");
    for(auto note : parser.getNotes()) {
        cout << note.panelIndex << ",";
        cout << note.justTime << endl;
    }
    return 0;
}
