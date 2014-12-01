#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

using namespace std;

void rshell(int a, int o, string input) {
    char* charin = new char[input.size()+1];
    strcpy(charin, input.c_str());

    int numbersemi = 0;
    int i = 0;

    char* parse = 0;
    char** semidone = new char* [input.size()+1];

    if (a == 1) {
        parse = strtok(charin, "&&");

        while (parse != NULL) {
            semidone[i] = parse;
            i++;
            numbersemi++;
            parse = strtok(NULL, "&&");
            if (parse == NULL) {
                semidone[i] = parse;
            }
        }
    }
    else if (o == 1) {
        parse = strtok(charin, "||");

        while (parse != NULL) {
            semidone[i] = parse;
            i++;
            numbersemi++;
            parse = strtok(NULL, "||");
            if (parse == NULL) {
                semidone[i] = parse;
            }
        }
    }
    else {
        parse = strtok(charin, ";");

        while (parse != NULL) {
            semidone[i] = parse;
            i++;
            numbersemi++;
            parse = strtok(NULL, ";");
            if (parse == NULL) {
                semidone[i] = parse;
            }
        }
    }

    if (a == 1) {
        for (int k = 0; k < numbersemi; k++) {
            int j = 0;
            char** useme = new char* [input.size()+1];

            parse = strtok(semidone[k], " ");
            while (parse != NULL) {
                useme[j] = parse;
                j++;
                parse = strtok(NULL, " ");
                if (parse == NULL) {
                    useme[j] = parse;
                }
            }

            int pid = fork();

            if (pid == -1) {
                perror("Error with fork");
                exit(1);
            }
            else if (pid == 0) {
                if (strcmp(useme[0], "exit") == 0) {
                    exit(1);
                }

                char *env = getenv("PATH");
                char *parseenv = strtok(env, ":");
                vector<char *> paths;
                while (parseenv != NULL) {
                    paths.push_back(parseenv);
                    parseenv = strtok(NULL, ":");
                    if (parseenv == NULL) {
                        paths.push_back(parseenv);
                    }
                }

                char *temphold = useme[0];
                strcat(paths.at(0), "/");
                strcat(paths.at(0), useme[0]);
                useme[0] = paths.at(0);
                int h = 1;

                while (access(useme[0], F_OK) != 0) {
                    useme[0] = temphold;
                    strcat(paths.at(h), "/");
                    strcat(paths.at(h), useme[0]);
                    useme[0] = paths.at(h);
                    h++;
                }

                if (execv(useme[0], useme) == -1) {
                    perror("Error in execv");
                }

                //delete [] useme;

                exit(1);
            }
            else if (pid > 0) {
                int x;
                if (waitpid(-1, &x, 0) == -1) {
                    perror("Error with wait");
                }

                if (strcmp(useme[0], "exit") == 0) {
                    exit(0);
                }

                if (x != 0) {
                    break;
                }
            }
            delete [] useme;
        }
    }
    else if (o == 1) {
        for (int k = 0; k < numbersemi; k++) {
            int j = 0;
            char** useme = new char* [input.size()+1];

            parse = strtok(semidone[k], " ");
            while (parse != NULL) {
                useme[j] = parse;
                j++;
                parse = strtok(NULL, " ");

                if (parse == NULL) {
                    useme[j] = parse;
                }
            }

            int pid = fork();

            if (pid == -1) {
                perror("Error with fork");
                exit(1);
            }
            else if (pid == 0) {
                if (strcmp(useme[0], "exit") == 0) {
                    exit(1);
                }

                char *env = getenv("PATH");
                char *parseenv = strtok(env, ":");
                vector<char *> paths;
                while (parseenv != NULL) {
                    paths.push_back(parseenv);
                    parseenv = strtok(NULL, ":");
                    if (parseenv == NULL) {
                        paths.push_back(parseenv);
                    }
                }

                char *temphold = useme[0];
                strcat(paths.at(0), "/");
                strcat(paths.at(0), useme[0]);
                useme[0] = paths.at(0);
                int h = 1;

                while (access(useme[0], F_OK) != 0) {
                    useme[0] = temphold;
                    strcat(paths.at(h), "/");
                    strcat(paths.at(h), useme[0]);
                    useme[0] = paths.at(h);
                    h++;
                }

                if (execv(useme[0], useme) == -1) {
                    perror("Error in execv");
                }

                //delete [] useme;

                exit(1);
            }
            else if (pid > 0) {
                int x;
                if (waitpid(-1, &x, 0) == -1) {
                    perror("Error with wait");
                }

                if (strcmp(useme[0], "exit") == 0) {
                    exit(0);
                }

                if (x == 0) {
                    break;
                }
            }
            delete [] useme;
        }
    }
    else {
        for (int k = 0; k < numbersemi; k++) {
            int j = 0;
            char** useme = new char* [input.size()+1];

            parse = strtok(semidone[k], " ");
            while (parse != NULL) {
                useme[j] = parse;

                //cout << "This is in useme[" << j << "]: " << useme[j] << endl;
                j++;

                parse = strtok(NULL, " ");

                if (parse == NULL) {
                    useme[j] = parse;
                }
            }

            int pid = fork();

            if (pid == -1) {
                perror("Error with fork");
                exit(1);
            }
            else if (pid == 0) {
                if (strcmp(useme[0], "exit") == 0) {
                    exit(1);
                }

                char *env = getenv("PATH");
                char *parseenv = strtok(env, ":");
                vector<char *> paths;
                while (parseenv != NULL) {
                    paths.push_back(parseenv);
                    parseenv = strtok(NULL, ":");
                    if (parseenv == NULL) {
                        paths.push_back(parseenv);
                    }
                }

                char *temphold = useme[0];
                strcat(paths.at(0), "/");
                strcat(paths.at(0), useme[0]);
                useme[0] = paths.at(0);
                int h = 1;

                while (access(useme[0], F_OK) != 0) {
                    useme[0] = temphold;
                    strcat(paths.at(h), "/");
                    strcat(paths.at(h), useme[0]);
                    useme[0] = paths.at(h);
                    h++;
                }

                if (execv(useme[0], useme) == -1) {
                    perror("Error in execv");
                    exit(1);
                }

                //delete [] useme;

                exit(1);
            }
            else if (pid > 0) {
                if (wait(0) == -1) {
                    perror("Error with wait");
                }
                if (strcmp(useme[0], "exit") == 0) {
                    exit(0);
                }
            }
            delete [] useme;
        }
    }

    delete [] charin;
    delete [] semidone;
}


void remove(string &input) {
    string temp;
    int size = input.size();
    for (int i = 0; i < size; i++) {
        if (input.at(i) != ' ') {
            temp = temp + input.at(i);
        }
    }
    input = temp;
}

void removeq(string &input) {
    string temp;
    int size = input.size();
    for (int i = 0; i < size; i++) {
        if (input.at(i) != '"') {
            temp = temp + input.at(i);
        }
    }
    input = temp;
}

void errredirect(string input) {
    string left(input, 0, input.find(">"));
    string right(input, input.find(">") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstderr = dup(2);
    if (oldstderr == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
        if (close(2) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstderr) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void outredirect(string input) {
    string left(input, 0, input.find(">"));
    string right(input, input.find(">") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstdout = dup(1);
    if (oldstdout == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
        if (close(1) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdout) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void outoutredirect(string input) {
    string left(input, 0, input.find(">>"));
    string right(input, input.find(">>") + 2, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstdout = dup(1);
    if (oldstdout == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
        if (close(1) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdout) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void innredirect(string input) {
    string left(input, 0, input.find(">"));
    string right(input, input.find(">") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();


    int fd = open(right.c_str(), O_RDONLY | O_TRUNC);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstdin = dup(0);
    if (oldstdin == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(1);
        }
        if (close(0) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdin) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void inredirect(string input) {
    string left(input, 0, input.find("<"));
    string right(input, input.find("<") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();


    int fd = open(right.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstdin = dup(0);
    if (oldstdin == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(1);
        }
        if (close(0) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdin) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void outinredirect(string input) {
    string left(input, 0, input.find(">"));
    string temp2(input, input.find(">") + 1, string::npos);
    string right(temp2, 0, temp2.find("<"));
    string wayright(temp2, temp2.find("<") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
        remove(wayright);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }

    int fd2 = open(wayright.c_str(), O_RDONLY);
    if (fd2 == -1) {
        perror("Error with open");
        exit(1);
    }

    int oldstdout = dup(1);
    if (oldstdout == -1) {
        perror("Error with dup");
        exit(1);
    }

    int oldstdin = dup(0);
    if (oldstdin == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(1);
        }

        if (close(1) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }
        if (close(0) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd2) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdout) == -1) {
            perror("Error with dup");
            exit(1);
        }
        if (close(fd2) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdin) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void inoutredirect(string input) {
    string left(input, 0, input.find("<"));
    string temp2(input, input.find("<") + 1, string::npos);
    string right(temp2, 0, temp2.find(">"));
    string wayright(temp2, temp2.find(">") + 1, string::npos);

    if (input.size() != 0) {
        remove(right);
        remove(wayright);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(wayright.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }

    int fd2 = open(right.c_str(), O_RDONLY);
    if (fd2 == -1) {
        perror("Error with open");
        exit(1);
    }

    int oldstdout = dup(1);
    if (oldstdout == -1) {
        perror("Error with dup");
        exit(1);
    }

    int oldstdin = dup(0);
    if (oldstdin == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(1);
        }

        if (close(1) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }
        if (close(0) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd2) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdout) == -1) {
            perror("Error with dup");
            exit(1);
        }
        if (close(fd2) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdin) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void piping(string &input, int &count, int fd[2]) {
    string left(input, 0, input.find("|"));
    string right(input, input.find("|") + 1, string::npos);

    count++;
    if (input.find("|") == string::npos) {
        char *temp2 = new char [1024];
        strcpy(temp2, left.c_str());

        char *parse2 = strtok(temp2, " ");
        char **useme2 = new char* [1024];
        int j = 0;
        while (parse2 != NULL) {
            useme2[j] = parse2;
            j++;
            parse2 = strtok(NULL, " ");

            if (parse2 == NULL) {
                useme2[j] = parse2;
            }
        }

        int pid2 = fork();

        if (pid2 == -1) {
            perror("Error with fork");
            exit(1);
        }
        else if (pid2 == 0) {
            if (strcmp(useme2[0], "exit") == 0) {
                exit(1);
            }
/*
            if (close(fd[1]) == -1) {
                perror("Error with pipe close1");
                exit(1);
            }
            */
            if (dup2(fd[0], 0) == -1) {
                perror("Error with dup2");
                exit(1);
            }

            char *env = getenv("PATH");
            char *parseenv = strtok(env, ":");
            vector<char *> paths;
            while (parseenv != NULL) {
                paths.push_back(parseenv);
                parseenv = strtok(NULL, ":");
                if (parseenv == NULL) {
                    paths.push_back(parseenv);
                }
            }

            char *temphold = useme2[0];
            strcat(paths.at(0), "/");
            strcat(paths.at(0), useme2[0]);
            useme2[0] = paths.at(0);
            int h = 1;

            while (access(useme2[0], F_OK) != 0) {
                useme2[0] = temphold;
                strcat(paths.at(h), "/");
                strcat(paths.at(h), useme2[0]);
                useme2[0] = paths.at(h);
                h++;
            }

            if (execv(useme2[0], useme2) == -1) {
                perror("Error with execv");
                exit(1);
            }

            exit(1);
        }
        else if (pid2 > 0) {
            if (wait(0) == -1) {
                perror("Error with wait");
                exit(1);
            }
            if (close(fd[0]) == -1) {
                perror("Error with pipe close");
                exit(1);
            }
            if (strcmp(useme2[0], "exit") == 0) {
                exit(0);
            }
        }
        delete [] temp2;
        delete [] useme2;
    }
    else {
        input = right;

        char *temp = new char [1024];
        strcpy(temp, left.c_str());

        char *parse = strtok(temp, " ");
        char **useme = new char* [1024];
        int i = 0;
        while (parse != NULL) {
            useme[i] = parse;
            i++;
            parse = strtok(NULL, " ");

            if (parse == NULL) {
                useme[i] = parse;
            }
        }

        int pid = fork();

        if (pid == -1) {
            perror("Error with fork");
            exit(1);
        }
        else if (pid == 0) {
            if (strcmp(useme[0], "exit") == 0) {
                exit(1);
            }

            if (count != 1) {
                if (dup2(fd[0], 0) == -1) {
                    perror("Error with dup2");
                    exit(1);
                }
            }
            if (close(fd[0]) == -1) {
                perror("Error with pipe close0");
                exit(1);
            }

            if (dup2(fd[1], 1) == -1) {
                perror("Error with dup2");
                exit(1);
            }

            char *env = getenv("PATH");
            char *parseenv = strtok(env, ":");
            vector<char *> paths;
            while (parseenv != NULL) {
                paths.push_back(parseenv);
                parseenv = strtok(NULL, ":");
                if (parseenv == NULL) {
                    paths.push_back(parseenv);
                }
            }

            char *temphold = useme[0];
            strcat(paths.at(0), "/");
            strcat(paths.at(0), useme[0]);
            useme[0] = paths.at(0);
            int h = 1;

            while (access(useme[0], F_OK) != 0) {
                useme[0] = temphold;
                strcat(paths.at(h), "/");
                strcat(paths.at(h), useme[0]);
                useme[0] = paths.at(h);
                h++;
            }

            if (execv(useme[0], useme) == -1) {
                perror("Error with execv");
                exit(1);
            }

            exit(1);
        }
        else if (pid > 0) {
            if (close(fd[1]) == -1) {
                perror("Error with pipe close1");
                exit(1);
            }
            if (wait(0) == -1) {
                perror("Error with wait");
                exit(1);
            }

            if (strcmp(useme[0], "exit") == 0) {
                exit(0);
            }
        }
        delete [] temp;
        delete [] useme;
    }
}

void outzeroredirect(string input) {
    string left(input, 0, input.find(">>"));
    string right(input, input.find(">>") + 2, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstdin = dup(0);
    if (oldstdin == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
        if (close(0) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstdin) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void remsp(string &input) {
    if (input.at(0) == ' ') {
        unsigned int q = input.find('"');
        if (q == string::npos) {
            int j = 0;
            while (input.at(j) == ' ') {
                input[j] = '\0';
                j++;
            }
        }
        else {
            for (unsigned int i = 0; i < q; i++) {
                input.erase(i, i+1);
            }
        }
    }
}

void triinredirect(string input) {
    string left(input, 0, input.find("<<<"));
    string right(input, input.find("<<<") + 3, string::npos);

    if (input.size() != 0) {
        //remsp(right);
        removeq(right);
    }

    int pid = fork();

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        cout << right << endl;

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }
    }
}

void outtworedirect(string input) {
    string left(input, 0, input.find(">>"));
    string right(input, input.find(">>") + 2, string::npos);

    if (input.size() != 0) {
        remove(right);
    }

    char *temp = new char [1024];
    strcpy(temp, left.c_str());

    char *parse = strtok(temp, " ");
    char **useme = new char* [1024];
    int i = 0;
    while (parse != NULL) {
        useme[i] = parse;
        i++;
        parse = strtok(NULL, " ");

        if (parse == NULL) {
            useme[i] = parse;
        }
    }

    int pid = fork();

    int fd = open(right.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }
    int oldstderr = dup(2);
    if (oldstderr == -1) {
        perror("Error with dup");
        exit(1);
    }

    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }
    else if (pid == 0) {
        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
        if (close(2) == -1) {
            perror("Error with close");
            exit(1);
        }
        if (dup(fd) == -1) {
            perror("Error with dup");
            exit(1);
        }

        char *env = getenv("PATH");
        char *parseenv = strtok(env, ":");
        vector<char *> paths;
        while (parseenv != NULL) {
            paths.push_back(parseenv);
            parseenv = strtok(NULL, ":");
            if (parseenv == NULL) {
                paths.push_back(parseenv);
            }
        }

        char *temphold = useme[0];
        strcat(paths.at(0), "/");
        strcat(paths.at(0), useme[0]);
        useme[0] = paths.at(0);
        int h = 1;

        while (access(useme[0], F_OK) != 0) {
            useme[0] = temphold;
            strcat(paths.at(h), "/");
            strcat(paths.at(h), useme[0]);
            useme[0] = paths.at(h);
            h++;
        }

        if (execv(useme[0], useme) == -1) {
            perror("Error with execv");
            exit(1);
        }

        exit(1);
    }
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Error with wait");
            exit(1);
        }

        if (close(fd) == -1) {
            perror("Error with close");
            exit(1);
        }
        if(dup(oldstderr) == -1) {
            perror("Error with dup");
            exit(1);
        }

        if (strcmp(useme[0], "exit") == 0) {
            exit(0);
        }
    }

    delete [] temp;
    delete [] useme;
}

void sighandler(int signum) {
    if (signum == SIGINT) {
        cout << endl;
    }
}

int main() {
    if (signal(SIGINT, sighandler) == SIG_ERR) {
        perror("Error with signal");
        exit(1);
    }

    char cwd[BUFSIZ];
    if (getcwd(cwd, BUFSIZ) == NULL) {
        perror("Error with getcwd");
        exit(1);
    }
    cout << cwd;
    cout << " $ ";
    string input;
    getline(cin, input);

    if (input.find("#") != string::npos) {
        input.at(input.find("#")) = '\0';
    }

    int a = 0;
    int o = 0;
    int outred = 0;
    int outoutred = 0;
    int inred = 0;
    int triinred = 0;
    int pipered = 0;
    int error = 0;

    if (input.find("&&") != string::npos) {
        a = 1;
    }
    else if (input.find("||") != string::npos) {
        o = 1;
    }

    int findg = input.find(">");
    int findl = input.find("<");

    if (input.find(">") != string::npos) {
        outred = 1;
    }
    if (input.find(">>") != string::npos) {
        outoutred = 1;
    }
    if (input.find("<<<") != string::npos) {
        triinred = 1;
    }
    if (input.find("<") != string::npos) {
        inred = 1;
    }
    if (input.find("|") != string::npos) {
        if (input.find("||") == string::npos) {
            pipered = 1;
        }
    }


    if (input.rfind(">") != input.find(">") && input.rfind(">") != input.find(">")+1) {
        error = 1;
    }
    else if (input.rfind("<") != input.find("<") && triinred != 1) {
        error = 1;
    }
    else if (input.rfind(">>") != input.find(">>")) {
        error = 1;
    }

    while (input != "exit") {
        if (error == 1) {
            cout << "Error: cannot do multiple of the same redirection or piping" << endl;
            error = 0;
        }
        else if (outred == 0 && inred == 0 && pipered == 0) {
            rshell(a, o, input);
        }
        else if (outred == 1 && inred == 1 && findl > findg) {
            outinredirect(input);
        }
        else if (outred == 1 && inred == 1 && findl < findg) {
            inoutredirect(input);
        }
        else if (outoutred == 1 && input.at(input.find(">>") - 1) == '1') {
            input.at(input.find(">") - 1) = ' ';
            outoutredirect(input);
        }
        else if (outoutred == 1 && input.at(input.find(">>") - 1) == '0') {
            input.at(input.find(">") - 1) = ' ';
            outzeroredirect(input);
        }
        else if (outoutred == 1 && input.at(input.find(">>") - 1) == '2') {
            input.at(input.find(">") - 1) = ' ';
            outtworedirect(input);
        }
        else if (outred == 1 && input.at(input.find(">") - 1) == '1') {
            input.at(input.find(">") - 1) = ' ';
            outredirect(input);
        }
        else if (outred == 1 && input.at(input.find(">") - 1) == '0') {
            input.at(input.find(">") - 1) = ' ';
            innredirect(input);
        }
        else if (outred == 1 && input.at(input.find(">") - 1) == '2') {
            input.at(input.find(">") - 1) = ' ';
            errredirect(input);
        }
        else if (triinred == 1) {
            triinredirect(input);
        }
        else if (outoutred == 1) {
            outoutredirect(input);
        }
        else if (outred == 1) {
            outredirect(input);
        }
        else if (inred == 1) {
            inredirect(input);
        }
        else if (pipered == 1) {
            int count = 0;

            while (input.find("|") != string::npos) {
                int fd[2];
                if (pipe(fd) == -1) {
                    perror("Error with pipe");
                    exit(1);
                }
                piping(input, count, fd);

                if (input.find("|") == string::npos) {
                    piping(input, count, fd);
                }
            }
        }

        if (getcwd(cwd, BUFSIZ) == NULL) {
            perror("Error with getcwd");
            exit(1);
        }
        cout << cwd;
        cout << " $ ";
        getline(cin, input);

        if (input.find("#") != string::npos) {
            input.at(input.find("#")) = '\0';
        }

        a = 0;
        o = 0;
        outred = 0;
        outoutred = 0;
        triinred = 0;
        inred = 0;
        pipered = 0;

        if (input.find("&&") != string::npos) {
            a = 1;
        }
        else if (input.find("||") != string::npos) {
            o = 1;
        }

        findg = input.find(">");
        findl = input.find("<");

        if (input.find(">") != string::npos) {
            outred = 1;
        }
        if (input.find(">>") != string::npos) {
            outoutred = 1;
        }
        if (input.find("<<<") != string::npos) {
            triinred = 1;
        }
        if (input.find("<") != string::npos) {
            inred = 1;
        }
        if (input.find("|") != string::npos) {
            pipered = 1;
        }


        if (input.rfind(">") != input.find(">") && input.rfind(">") != input.find(">")+1) {
            error = 1;
        }
        else if (input.rfind("<") != input.find("<") && triinred != 1) {
            error = 1;
        }
        else if (input.rfind(">>") != input.find(">>")) {
            error = 1;
        }
    }

    return 0;
}
