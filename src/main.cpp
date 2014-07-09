#include <cstdlib>
#include <iostream>
#include <fstream>
#include "common.h"
#include "run.h"
#include "include.h"
#include "docs.h"

using namespace std;

void loadSettings(string settingFilePath) {
	cout << settingFilePath << endl;
	ifstream file(settingFilePath);
	string line;
	getline(file, line);
	settings.libDir = line;
	file.close();
}

int main(int argc, char *argv[]) {

	loadSettings(string(getenv("HOME")) + "/ICPC/settings.txt");

	if(argc <= 1) {
		cout << "TODO: Description" << endl;
		return 1;
	}

	if(string(argv[1]) == "run") {
		if(argc <= 2) {
			cout << "Error: no input file" << endl;
			return 1;
		}
		run(argv[2]);
	} else if(string(argv[1]) == "include") {
		if(argc <= 2) {
			cout << "Error: no input file" << endl;
			return 1;
		}
		include(argv[2], argv[2 + (argc == 4)]);
	} else if(string(argv[1]) == "docs") {
		if(argc <= 2) {
			cout << "Error: no output file" << endl;
			return 1;
		}
		createDocs(argv[2]);
	} else {
		cout << "Error: command not found." << endl;
	}

	return 0;
}