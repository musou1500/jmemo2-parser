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
	
	vector<Note> notes = parser.getNotes();
	Music music = parser.getMusic();

	cout << "Parse result:" << endl;
	cout << notes.size() << " notes." << endl;
	cout << "Level " << music.level << endl;
	cout << "offset " << music.offset << endl;

    return 0;
}
