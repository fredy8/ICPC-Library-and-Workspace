#include <iostream>
#include <fstream>
#include <regex>

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

int main() {
    ifstream source("../src/problem.cpp");
    ofstream temp("../src/temp.cpp");
    
    string line;
    while(getline(source, line))
    {
        if(isInclude(line)) {
            temp << ("//" + line) << endl;
            ifstream includeFile("../../lib/src/" + getIncludedFile(line));
            while(getline(includeFile, line)) {
                temp << line << endl;
            }
            includeFile.close();
        } else {
            temp << line << endl;
        }
    }
    
    source.close();
    temp.close();
    
    system("mv ../src/temp.cpp ../src/problem.cpp");
}