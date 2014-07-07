#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

unsigned char isFile = 0x8;

string readFile(string path) {
    string output;
    ifstream file(path);
    while(file.good()) {
        string line;
        getline(file, line);
        output += line + "\n";
    }
    file.close();
    return output;
}

int getAllFiles(string dir, vector<string> &files) {
    DIR *dp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        string dirName(entry->d_name);
        if(dirName[0] != '.') {
            if(entry->d_type != isFile)
                getAllFiles(dir + "/" + dirName, files);
            else
                files.push_back(dir + "/" + dirName);
        }
    }
    closedir(dp);
    return 0;
}

int main() {
    string dir = string("../../src");
    vector<string> files = vector<string>();
    
    getAllFiles(dir, files);
    
    ofstream out("../Test.txt");
    for (int i = 0; i < files.size(); i++)
        out << readFile(files[i]);
    
    out.close();
}