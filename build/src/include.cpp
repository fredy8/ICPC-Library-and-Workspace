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

string readFile(string filePath) {
    string content;
    ifstream file(filePath);
    string line;
    while (getline(file, line))
        content += line + '\n';
    file.close();
    return content;
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
    string result;
    
    string line;
    while(getline(source, line))
    {
        if(isInclude(line)) {
            result += ("//" + line) + '\n';
            result += includeFiles(readFile("../../lib/src/" + getIncludedFile(line)));
        } else {
            result += line + '\n';
        }
    }
    
    return result;
}

int main() {
    string fixedSource = includeFiles(readFile("../src/problem.cpp"));
    ofstream sourceFile("../src/problem.cpp");
    sourceFile << fixedSource << endl;
    sourceFile.close();
}