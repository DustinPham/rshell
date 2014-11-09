#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

void sort(vector<string> &o, int n) {
    int condition = 1;
    int j = 0;
    string temp;
    if (n == 0) {
        while (condition == 1) {
            condition = 0;
            for (int i = 0; i < o.size() - 1; i++) {
                //if (strcasecmp(o.at(i).c_str(), o.at(i+1).c_str())) {
                if (o.at(i) > o.at(i+1)) {
                    //swap(o.at(i), o.at(i+1));
                    temp = o.at(i);
                    o.at(i) = o.at(i+1);
                    o.at(i+1) = temp;
                    condition = 1;
                }
            }
        }
    }
    else {
        while (condition == 1) {
            condition = 0;
            for (int i = 0; i < o.size() - 1; i++) {
                //if (strcasecmp(o.at(i).c_str(), o.at(i+1).c_str())) {
                if (o.at(i) < o.at(i+1)) {
                    //swap(o.at(i), o.at(i+1));
                    temp = o.at(i);
                    o.at(i) = o.at(i+1);
                    o.at(i+1) = temp;
                    condition = 1;
                }
            }
        }
    }
}

void print(vector<string> &d, int aflag,int lflag, int Rflag, int args) {
    struct stat s;

    if (stat((d.at(d.size()-1)).c_str(), &s) == -1) {
        perror("Error with stat");
        exit(1);
    }
    if (S_ISREG(s.st_mode)) {
        if (lflag == 1) {
            //print type, directory/symbolic link/regular file
            if (S_ISDIR(s.st_mode)) {
                cout << "d";
            }
            else if (S_ISLNK(s.st_mode)) {
                cout << "l";
            }
            else {
                cout << "-";
            }

            //print user read permission
            if (s.st_mode & S_IRUSR) {
                cout << "r";
            }
            else {
                cout << "-";
            }

            //print user write permission
            if (s.st_mode & S_IWUSR) {
                cout << "w";
            }
            else {
                cout << "-";
            }

            //print user execute permission
            if (s.st_mode & S_IXUSR) {
                cout << "x";
            }
            else {
                cout << "-";

            }

            //print group read permission
            if (s.st_mode & S_IRGRP) {
                cout << "r";
            }
            else {
                cout << "-";
            }

            //print group write permission
            if (s.st_mode & S_IWGRP) {
                cout << "w";
            }
            else {
                cout << "-";
            }

            //print group execute permission
            if (s.st_mode & S_IXGRP) {
                cout << "x";
            }
            else {
                cout << "-";
            }

            //print others read permission
            if (s.st_mode & S_IROTH) {
                cout << "r";
            }
            else {
                cout << "-";
            }

            //print others write permission
            if (s.st_mode & S_IWOTH) {
                cout << "w";
            }
            else {
                cout << "-";
            }

            //print others execute permission
            if (s.st_mode & S_IXOTH) {
                cout << "x";
            }
            else {
                cout << "-";
            }

            cout << " ";
            //print number of hard links
            cout << s.st_nlink << " ";

            struct passwd *userid = getpwuid(s.st_uid);

            //print username
            if (userid == NULL) {
                perror("Error with getpwuid");
                exit(1);
            }
            else {
                cout << userid->pw_name << " ";
            }

            struct group *groupid = getgrgid(s.st_gid);

            //print groupname
            if (groupid == NULL) {
                perror("Error with getgrgid");
                exit(1);
            }
            else {
                cout << groupid->gr_name << " ";
            }

            cout << s.st_size << " ";

            time_t time = s.st_mtime;
            struct tm *ltime = localtime(&time);
            char outtime[100];
            strftime(outtime, 100, "%b %e %H:%M", ltime);
            cout << outtime << " ";

            cout << d.at(d.size()-1) << endl;
        }
        else {
            cout << d.at(d.size()-1) << endl;
        }
    }
    else if (S_ISDIR(s.st_mode)) {
        DIR *dirp = opendir((d.at(d.size()-1)).c_str());
        if (dirp == '\0') {
            perror("Error with opendir");
            exit(1);
        }

        if (args > 1) {
            cout << d.at(d.size()-1) << ":" << endl;
        }

        dirent *direntp;
        while ((direntp = readdir(dirp))) {
            if (direntp == '\0') {
                perror("Error with readdir");
                exit(1);
            }

            //string temp = d.at(d.size()-1);
            //temp = temp + "/" + direntp->d_name;

            char temp[1024];
            strcpy(temp, (d.at(d.size()-1)).c_str());
            strcat(temp, "/");
            strcat(temp, direntp->d_name);

            if (stat(temp, &s) == -1) {
                perror("Error with stat");
            }
            if (aflag == 1) {
                if (lflag == 1) {
                    //print type, directory/symbolic link/regular file
                    if (S_ISDIR(s.st_mode)) {
                        cout << "d";
                    }
                    else if (S_ISLNK(s.st_mode)) {
                        cout << "l";
                    }
                    else {
                        cout << "-";
                    }

                    //print user read permission
                    if (s.st_mode & S_IRUSR) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print user write permission
                    if (s.st_mode & S_IWUSR) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print user execute permission
                    if (s.st_mode & S_IXUSR) {
                        cout << "x";
                    }
                    else {
                        cout << "-";

                    }

                    //print group read permission
                    if (s.st_mode & S_IRGRP) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print group write permission
                    if (s.st_mode & S_IWGRP) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print group execute permission
                    if (s.st_mode & S_IXGRP) {
                        cout << "x";
                    }
                    else {
                        cout << "-";
                    }

                    //print others read permission
                    if (s.st_mode & S_IROTH) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print others write permission
                    if (s.st_mode & S_IWOTH) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print others execute permission
                    if (s.st_mode & S_IXOTH) {
                        cout << "x";
                    }
                    else {
                        cout << "-";
                    }

                    cout << " ";
                    //print number of hard links
                    cout << s.st_nlink << " ";

                    struct passwd *userid = getpwuid(s.st_uid);

                    //print username
                    if (userid == NULL) {
                        perror("Error with getpwuid");
                        exit(1);
                    }
                    else {
                        cout << userid->pw_name << " ";
                    }

                    struct group *groupid = getgrgid(s.st_gid);

                    //print groupname
                    if (groupid == NULL) {
                        perror("Error with getgrgid");
                        exit(1);
                    }
                    else {
                        cout << groupid->gr_name << " ";
                    }

                    //formatting, if size is too small
                    if (s.st_size <= 9) {
                        cout << "   ";
                    }
                    else if (s.st_size <= 99) {
                        cout << "  ";
                    }
                    else if (s.st_size <= 999) {
                        cout << " ";
                    }

                    cout << s.st_size << " ";

                    time_t time = s.st_mtime;
                    struct tm *ltime = localtime(&time);
                    char outtime[100];
                    strftime(outtime, 100, "%b %e %H:%M", ltime);
                    cout << outtime << " ";

                    cout << direntp->d_name << endl;
                }
                else {
                    cout << direntp->d_name << endl;
                }
            }
            else if ((direntp->d_name)[0] != '.') {
                if (lflag == 1) {
                    //print type, directory/symbolic link/regular file
                    if (S_ISDIR(s.st_mode)) {
                        cout << "d";
                    }
                    else if (S_ISLNK(s.st_mode)) {
                        cout << "l";
                    }
                    else {
                        cout << "-";
                    }

                    //print user read permission
                    if (s.st_mode & S_IRUSR) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print user write permission
                    if (s.st_mode & S_IWUSR) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print user execute permission
                    if (s.st_mode & S_IXUSR) {
                        cout << "x";
                    }
                    else {
                        cout << "-";

                    }

                    //print group read permission
                    if (s.st_mode & S_IRGRP) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print group write permission
                    if (s.st_mode & S_IWGRP) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print group execute permission
                    if (s.st_mode & S_IXGRP) {
                        cout << "x";
                    }
                    else {
                        cout << "-";
                    }

                    //print others read permission
                    if (s.st_mode & S_IROTH) {
                        cout << "r";
                    }
                    else {
                        cout << "-";
                    }

                    //print others write permission
                    if (s.st_mode & S_IWOTH) {
                        cout << "w";
                    }
                    else {
                        cout << "-";
                    }

                    //print others execute permission
                    if (s.st_mode & S_IXOTH) {
                        cout << "x";
                    }
                    else {
                        cout << "-";
                    }

                    cout << " ";
                    //print number of hard links
                    cout << s.st_nlink << " ";

                    struct passwd *userid = getpwuid(s.st_uid);

                    //print username
                    if (userid == NULL) {
                        perror("Error with getpwuid");
                        exit(1);
                    }
                    else {
                        cout << userid->pw_name << " ";
                    }

                    struct group *groupid = getgrgid(s.st_gid);

                    //print groupname
                    if (groupid == NULL) {
                        perror("Error with getgrgid");
                        exit(1);
                    }
                    else {
                        cout << groupid->gr_name << " ";
                    }

                    //formatting, if size is too small
                    if (s.st_size <= 9) {
                        cout << "   ";
                    }
                    else if (s.st_size <= 99) {
                        cout << "  ";
                    }
                    else if (s.st_size <= 999) {
                        cout << " ";
                    }
                    cout << s.st_size << " ";

                    time_t time = s.st_mtime;
                    struct tm *ltime = localtime(&time);
                    char outtime[100];
                    strftime(outtime, 100, "%b %e %H:%M", ltime);
                    cout << outtime << " ";

                    cout << direntp->d_name << endl;
                }
                else {
                    cout << direntp->d_name << endl;
                }
            }
        }
        if (closedir(dirp) == -1) {
            perror("Error with closedir");
            exit(1);
        }
    }
}

int main(int argc, char* argv[]) {
    vector<string> dandf;
    vector<string> output;

    string temp = ".";
    string a = "-a", la = "-la", al = "-al";
    string l = "-l", lR = "-lR", Rl = "-Rl";
    string R = "-R", Ra = "-Ra", aR = "-aR";
    string alR = "-alR", aRl = "-aRl";
    string Rla = "-Rla", Ral = "-Ral";
    string lRa = "-lRa", laR = "-laR";

    int aflag = 0;
    int lflag = 0;
    int Rflag = 0;

    for (int i = 0; i < argc; i++) {
        if (argv[i] == a) {
            aflag = 1;
        }
        else if (argv[i] == l) {
            lflag = 1;
        }
        else if (argv[i] == R) {
            Rflag = 1;
        }
        else if (argv[i] == la || argv[i] == al) {
            aflag = 1;
            lflag = 1;
        }
        else if (argv[i] == lR || argv[i] == Rl) {
            lflag = 1;
            Rflag = 1;
        }
        else if (argv[i] == Ra || argv[i] == aR) {
            Rflag = 1;
            aflag = 1;
        }
        else if (argv[i] == alR || argv[i] == aRl ||
                 argv[i] == Rla || argv[i] == Ral ||
                 argv[i] == lRa || argv[i] == laR) {
            aflag = 1;
            lflag = 1;
            Rflag = 1;
        }
        else if (argv[i][0] != '.') {
            dandf.push_back(argv[i]);
        }
    }

    if (dandf.empty()) {
        dandf.push_back(".");
    }

    sort(dandf, 1);
    int size = dandf.size();

    while (!dandf.empty()) {
        print(dandf, aflag, lflag, Rflag, size);
        cout << endl;
        dandf.pop_back();
    }

    return 0;
}
