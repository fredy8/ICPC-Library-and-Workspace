#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "common.h"

using namespace std;

void run(char *src) {
    
    string sourceDir, sourceFile(src);
    sourceDir = sourceFile.substr(0, sourceDir.find_last_of('/') + 1);
    
    string inputFile = sourceDir + "input.txt";
    
	ifstream source(sourceFile.c_str());
	int i = 0;
	string line;
	getline(source, line);
	bool created = false;
	if(!line.find("/*")) {
		ofstream input(inputFile.c_str());
		created = true;
		while(getline(source, line) && line.find("*/"))
			input << line << endl;
		input.close();
	}
	
	source.close();

	bool syntaxError = system(("g++ -iquote \"" + settings.libDir + "\" -DDEBUG -o problem \"" + sourceFile + "\"").c_str());
	if(!syntaxError) {
        ifstream input(inputFile.c_str());
		if(input.good()) 
			system(("./problem < " + inputFile).c_str());
		else
			system("./problem");

		system("rm problem");
		input.close();
		
		if (created)
			system(("rm " + inputFile).c_str());
	}
}