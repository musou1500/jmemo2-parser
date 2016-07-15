#include <string>
#include <iostream>
#include <fstream>
#include "Jmemo2Parser.h"

using namespace std;

int main(int argc, char const* argv[])
{
	string filename;
	cout << "Jmemo2-Parser CLI" << endl;
	cout << "memo file ->" << endl;
	cin >> filename;
    Jmemo2Parser parser;
    parser.initWithFileName(filename);
    for(auto note : parser.getNotes()) {
        cout << note.panelIndex << ",";
        cout << note.justTime << endl;
    }
    return 0;
}
