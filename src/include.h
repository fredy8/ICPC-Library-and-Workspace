#include <iostream>
#include <fstream>
#include <regex>
#include "common.h"

using namespace std;

bool isInclude(string line) {
    string pattern = "^\\s*#\\s*include\\s*\"(.+)\"\\s*$";
    
    return regex_match(line.c_str(), regex(pattern.c_str()));
}

string getIncludedFile(string includeLine) {
    int initialPos = 0, finalPos = includeLine.length() - 1;
    while(includeLine[initialPos++] != '"');
    while(includeLine[finalPos--] != '"');
    
    return includeLine.substr(initialPos, finalPos - initialPos + 1);
}

bool getline(string &str, string &line) {
    int ind = 0;
    if(str.length() == 0)
        return false;
    while(ind < str.length() && str[ind++] != '\n');

    line = str.substr(0, ind - 1);
    str = str.substr(ind);
    return true;
}

string includeFiles(string source) {
    string result, line;

    while(getline(source, line))
        if(isInclude(line))
            result += ("//" + line) + '\n' + includeFiles(readFile(settings.libDir + getIncludedFile(line)));
        else
            result += line + '\n';
    return result;
}

void include(char *in, char *out) {
    string includedSource = includeFiles(readFile(string(in)));
    cout << out << endl;
    ofstream outputFile(out);
    outputFile << includedSource << endl;
    outputFile.close();
}