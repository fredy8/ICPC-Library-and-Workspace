#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    
    string currentDir(argv[0]);
    currentDir = currentDir.substr(0, currentDir.find_last_of('/') + 1);
    
    string srcFile = currentDir + "../src/problem.cpp";
    string inputFile = currentDir + "../src/input.txt";
    
	ifstream source(srcFile.c_str());
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

	bool syntaxError = system(("g++ -iquote ../../lib/src/ -DDEBUG -o problem " + srcFile).c_str());
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