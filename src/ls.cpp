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
#include <algorithm>
#include <iomanip>

#include <iostream>

using namespace std;

/*
void makeo(vector<string> &d, vector<string> &o, int aflag,int lflag, int Rflag, int args, int &width) {
    struct stat s;

    if (lstat((d.at(0)).c_str(), &s) == -1) {
        perror("Error with stat");
        exit(1);
    }
    if (S_ISREG(s.st_mode)) {
        o.push_back(d.at(0));
    }
    else if (S_ISDIR(s.st_mode)) {
        DIR *dirp = opendir((d.at(0)).c_str());
        if (dirp == '\0') {
            perror("Error with opendir");
            exit(1);
        }

        dirent *direntp;
        while ((direntp = readdir(dirp))) {
            if (direntp == '\0') {
                perror("Error with readdir");
                exit(1);
            }

            char temp[512];
            strcpy(temp, (d.at(0)).c_str());
            strcat(temp, "/");
            strcat(temp, direntp->d_name);

            if (lstat(temp, &s) == -1) {
                perror("Error with stat");
                exit(1);
            }

            if (aflag == 1) {
                o.push_back(direntp->d_name);
            }
            else if (direntp->d_name[0] != '.') {
                o.push_back(direntp->d_name);
            }
        }
        if (closedir(dirp) == -1) {
            perror("Error with closedir");
            exit(1);
        }
    }
}
*/

void print(vector<string> &d, int aflag,int lflag, int Rflag, int args, int &width) {
    struct stat s;

    if (lstat((d.at(0)).c_str(), &s) == -1) {
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

            cout << setw(5) << s.st_size << " ";

            time_t time = s.st_mtime;
            struct tm *ltime = localtime(&time);
            char outtime[100];
            strftime(outtime, 100, "%b %e %H:%M", ltime);
            cout << outtime << " ";

            if ((d.at(0).at(0) == '.') && (S_ISLNK(s.st_mode))) {
                cout << "\033[1;100;36m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IFDIR)) {
                cout << "\033[1;100;34m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IXUSR)) {
                cout << "\033[1;100;32m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if (d.at(0).at(0) == '.') {
                cout << "\033[1;100;37m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if (S_ISLNK(s.st_mode)) {
                cout << "\033[1;36m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if (s.st_mode & S_IFDIR) {
                cout << "\033[1;34m" << d.at(0) << "\033[0;00m" << endl;
            }
            else if (s.st_mode & S_IXUSR) {
                cout << "\033[1;32m" << d.at(0) << "\033[0;00m" << endl;
            }
            else {
                cout << d.at(0) << endl;
            }
        }
        else {
            if (width < 60) {
                if ((d.at(0).at(0) == '.') && (S_ISLNK(s.st_mode))) {
                    cout << "\033[1;100;36m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IFDIR)) {
                    cout << "\033[1;100;34m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IXUSR)) {
                    cout << "\033[1;100;32m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if (d.at(0).at(0) == '.') {
                    cout << "\033[1;100;37m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if (S_ISLNK(s.st_mode)) {
                    cout << "\033[1;36m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if (s.st_mode & S_IFDIR) {
                    cout << "\033[1;34m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else if (s.st_mode & S_IXUSR) {
                    cout << "\033[1;32m" << setw(20) << left << d.at(0) << "\033[0;00m" << " ";
                    width = width + 20;
                }
                else {
                    cout << setw(20) << left << d.at(0)  << " ";
                    width = width + 20;
                }
            }
            else {
                if ((d.at(0).at(0) == '.') && (S_ISLNK(s.st_mode))) {
                    cout << "\033[1;100;36m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IFDIR)) {
                    cout << "\033[1;100;34m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if ((d.at(0).at(0) == '.') && (s.st_mode & S_IXUSR)) {
                    cout << "\033[1;100;32m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if (d.at(0).at(0) == '.') {
                    cout << "\033[1;100;37m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if (S_ISLNK(s.st_mode)) {
                    cout << "\033[1;36m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if (s.st_mode & S_IFDIR) {
                    cout << "\033[1;34m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else if (s.st_mode & S_IXUSR) {
                    cout << "\033[1;32m" << setw(20) << left << d.at(0) << "\033[0;00m" << endl;
                    width = 0;
                }
                else {
                    cout << setw(20) << left << d.at(0) << endl;
                    width = 0;
                }
            }
        }
    }
    else if (S_ISDIR(s.st_mode)) {
        DIR *dirp = opendir((d.at(0)).c_str());
        if (dirp == '\0') {
            perror("Error with opendir");
            exit(1);
        }

        if (args > 1) {
            cout << d.at(0) << ":" << endl;
        }

        int ptotal = 0;

        dirent *direntp;
        while ((direntp = readdir(dirp))) {
            if (direntp == '\0') {
                perror("Error with readdir");
                exit(1);
            }

            char temp[512];
            strcpy(temp, (d.at(0)).c_str());
            strcat(temp, "/");
            strcat(temp, direntp->d_name);

            if (lstat(temp, &s) == -1) {
                perror("Error with stat");
                exit(1);
            }

            if (aflag == 1) {
                if (lflag == 1) {
                    if (ptotal == 0) {
                        cout << "total " << s.st_blocks << endl;
                        ptotal = 1;
                    }
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

                    cout << setw(5) << s.st_size << " ";

                    time_t time = s.st_mtime;
                    struct tm *ltime = localtime(&time);
                    char outtime[100];
                    strftime(outtime, 100, "%b %e %H:%M", ltime);
                    cout << outtime << " ";

                    if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                        cout << "\033[1;100;36m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                        cout << "\033[1;100;34m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                        cout << "\033[1;100;32m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (direntp->d_name[0]  == '.') {
                        cout << "\033[1;100;37m" << direntp-> d_name << "\033[0;00m" << endl;
                    }
                    else if (S_ISLNK(s.st_mode)) {
                        cout << "\033[1;36m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (s.st_mode & S_IFDIR) {
                        cout << "\033[1;34m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (s.st_mode & S_IXUSR) {
                        cout << "\033[1;32m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else {
                        cout << direntp->d_name << endl;
                    }
                }
                else {
                    if (width < 60) {
                        if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                            cout << "\033[1;100;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                            cout << "\033[1;100;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                            cout << "\033[1;100;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (direntp->d_name[0]  == '.') {
                            cout << "\033[1;100;37m" << setw(20) << left << direntp-> d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (S_ISLNK(s.st_mode)) {
                            cout << "\033[1;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (s.st_mode & S_IFDIR) {
                            cout << "\033[1;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (s.st_mode & S_IXUSR) {
                            cout << "\033[1;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else {
                            cout << setw(20) << left << direntp->d_name << " ";
                            width = width + 20;
                        }
                    }
                    else {
                        if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                            cout << "\033[1;100;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                            cout << "\033[1;100;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                            cout << "\033[1;100;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (direntp->d_name[0]  == '.') {
                            cout << "\033[1;100;37m" << setw(20) << left << direntp-> d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (S_ISLNK(s.st_mode)) {
                            cout << "\033[1;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (s.st_mode & S_IFDIR) {
                            cout << "\033[1;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (s.st_mode & S_IXUSR) {
                            cout << "\033[1;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else {
                            cout << setw(20) << left << direntp->d_name << endl;
                            width = 0;
                        }
                    }
                }
            }
            else if (direntp->d_name[0] != '.') {
                if (lflag == 1) {
                    if (ptotal == 0) {
                        cout << "total " << s.st_blocks << endl;
                        ptotal = 1;
                    }
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

                    cout << setw(5) << s.st_size << " ";

                    time_t time = s.st_mtime;
                    struct tm *ltime = localtime(&time);
                    char outtime[100];
                    strftime(outtime, 100, "%b %e %H:%M", ltime);
                    cout << outtime << " ";

                    if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                        cout << "\033[1;100;36m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                        cout << "\033[1;100;34m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                        cout << "\033[1;100;32m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (direntp->d_name[0]  == '.') {
                        cout << "\033[1;100;37m" << direntp-> d_name << "\033[0;00m" << endl;
                    }
                    else if (S_ISLNK(s.st_mode)) {
                        cout << "\033[1;36m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (s.st_mode & S_IFDIR) {
                        cout << "\033[1;34m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else if (s.st_mode & S_IXUSR) {
                        cout << "\033[1;32m" << direntp->d_name << "\033[0;00m" << endl;
                    }
                    else {
                        cout << direntp->d_name << endl;
                    }
                }
                else {
                    if (width < 60) {
                        if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                            cout << "\033[1;100;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                            cout << "\033[1;100;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                            cout << "\033[1;100;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (direntp->d_name[0]  == '.') {
                            cout << "\033[1;100;37m" << setw(20) << left << direntp-> d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (S_ISLNK(s.st_mode)) {
                            cout << "\033[1;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (s.st_mode & S_IFDIR) {
                            cout << "\033[1;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else if (s.st_mode & S_IXUSR) {
                            cout << "\033[1;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << " ";
                            width = width + 20;
                        }
                        else {
                            cout << setw(20) << left << direntp->d_name << " ";
                            width = width + 20;
                        }
                    }
                    else {
                        if ((direntp->d_name[0] == '.') && (S_ISLNK(s.st_mode))) {
                            cout << "\033[1;100;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IFDIR)) {
                            cout << "\033[1;100;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if ((direntp->d_name[0] == '.') && (s.st_mode & S_IXUSR)) {
                            cout << "\033[1;100;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (direntp->d_name[0]  == '.') {
                            cout << "\033[1;100;37m" << setw(20) << left << direntp-> d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (S_ISLNK(s.st_mode)) {
                            cout << "\033[1;36m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (s.st_mode & S_IFDIR) {
                            cout << "\033[1;34m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else if (s.st_mode & S_IXUSR) {
                            cout << "\033[1;32m" << setw(20) << left << direntp->d_name << "\033[0;00m" << endl;
                            width = 0;
                        }
                        else {
                            cout << setw(20) << left << direntp->d_name << endl;
                            width = 0;
                        }
                    }
                }
            }
        }
        if (closedir(dirp) == -1) {
            perror("Error with closedir");
            exit(1);
        }
    }
}

bool find(vector<string> a, string p) {
    bool found = false;
    int size = a.size();
    for (int i = 0; i < size; i++) {
        if (a.at(i) == p) {
            found = true;
        }
    }
    return found;
}

void recursion(vector<string> &directories, int aflag, int lflag, int Rflag, int args, int width) {
    if (directories.empty()) {
        return;
    }
    struct stat s;
    string temp;

    if (lstat(directories.at(0).c_str(), &s) == -1) {
        perror("Error with stat");
        exit(1);
    }

    if (S_ISREG(s.st_mode)) {
        cout << directories.at(0) << endl;
        return;
    }

    DIR *dirp = opendir((directories.at(0)).c_str());
    if (dirp == '\0') {
        perror("Error with opendir");
        exit(1);
    }

    dirent *direntp;
    while ((direntp = readdir(dirp))) {
        if (direntp == '\0') {
            perror("Error with readdir");
            exit(1);
        }
        if ((direntp->d_name)[0] == '.' && (direntp->d_name)[1] == '.') {
            continue;
        }

        temp = directories.at(0);
        temp = temp + "/" + direntp->d_name;

        if (temp == "./.") {
            temp = ".";
        }

        if (direntp->d_name[0] == '.' && aflag == 0) {
            continue;
        }

        if (lstat(temp.c_str(), &s) == -1) {
            perror("Error with stat");
            exit(1);
        }
        if (S_ISREG(s.st_mode)) {
            continue;
        }
        else if (S_ISDIR(s.st_mode)) {
            string t = direntp->d_name;
            if (find(directories, temp) || t == "." || t == "..") {
                continue;
            }
            directories.push_back(temp);
        }
    }

    if (closedir(dirp) == -1) {
        perror("Error with closedir");
        exit(1);
    }

    sort(directories.begin(), directories.end(), locale("en_US.UTF-8"));

    print(directories, aflag, lflag, Rflag, args, width);
    cout << endl;

    directories.erase(directories.begin());
    recursion(directories, aflag, lflag, Rflag, args, width);
}

int main(int argc, char* argv[]) {
    vector<string> dandf;

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
        else if (argv[i][0] == '-') {
            cout << "Error: Wrong flag(s)" << endl;
            cout << "Try: -a, -l, -R, or any combinations" << endl;
            exit(1);
        }
        else if (i != 0) {
            dandf.push_back(argv[i]);
        }
    }

    if (dandf.empty()) {
        dandf.push_back(".");
    }

    int width = 0;
    sort(dandf.begin(), dandf.end(), locale("en_US.UTF-8"));
    int size = dandf.size();

    /*
    vector<string> output;
    makeo(dandf, output, aflag, lflag, Rflag, size, width);
    sort(output.begin(), output.end(), locale("en_US.UTF-8"));
    */

    if (Rflag == 1) {
        vector<string> alld(dandf);
        size = 2;
        sort(alld.begin(), alld.end(), locale("en_US.UTF-8"));
        recursion(alld, aflag, lflag, Rflag, size, width);
    }
    else {
        while (!dandf.empty()) {
            print(dandf, aflag, lflag, Rflag, size, width);
            dandf.erase(dandf.begin());
        }
        /*
        while (!output.empty()) {
            print(output, aflag, lflag, Rflag, size, width);
            output.erase(output.begin());
        }
        */
        cout << endl;
    }

    return 0;
}
