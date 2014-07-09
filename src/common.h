#ifndef COMMON_H
#define COMMON_H
 
#include <fstream>

using namespace std;

struct Settings {
	string libDir;
} settings;

string readFile(string filePath) {
    string content;
    ifstream file(filePath);
    string line;
    while (getline(file, line))
        content += line + '\n';
    file.close();
    return content;
}

#endif /* COMMON_H */