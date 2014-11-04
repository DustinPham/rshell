#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv) {
    string temp = ".";
    DIR *dirp = opendir(temp.c_str());
    if (dirp == '\0') {
        perror("Error with opendir");
    }
    dirent *direntp;
    while ((direntp = readdir(dirp))) {
        if (direntp == '\0') {
            perror("Error with readdir");
        }
        cout << direntp->d_name << endl;
    }
    if (closedir(dirp) == -1) {
        perror("Error with closedir");
    }


    return 0;
}
