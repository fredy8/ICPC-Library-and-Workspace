#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "common.h"

using namespace std;

unsigned char isFile = 0x8;

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

void createDocs(char *out) {
    vector<string> files = vector<string>();
    
    getAllFiles(settings.libDir.substr(0, settings.libDir.length() - 1), files);
    
    ofstream outputFile(out);
    for (int i = 0; i < files.size(); i++) {
        cout << files[i] << endl;
        outputFile << " -------- " << files[i] << " -------- " << "\n" << readFile(files[i]);
    }
    
    outputFile.close();
}