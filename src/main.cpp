#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    cout << "$ ";
    string input;
    getline(cin, input);

    if (input.find("#") != string::npos)
    {
        input.at(input.find("#")) = '\0';
    }


    int a = 0;
    int o = 0;
    if (input.find("&&") != string::npos)
    {
        a = 1;
    }
    else if (input.find("||") != string::npos)
    {
        o = 1;
    }


    while (input != "exit")
    {
        char* charin = new char[input.size()+1];
        strcpy(charin, input.c_str());

        int numbersemi = 0;
        int i = 0;

        char* parse = 0;
        char** semidone = new char* [input.size()+1];


        if (a == 1)
        {
            parse = strtok(charin, "&");

            while (parse != NULL)
            {
                semidone[i] = parse;

                cout << "This is in semidone[" << i << "]: " << semidone[i] << endl;
                i++;
                numbersemi++;

                parse = strtok(NULL, "&");
            }
        }
        else if (o == 1)
        {
            parse = strtok(charin, "|");

            while (parse != NULL)
            {
                semidone[i] = parse;

                cout << "This is in semidone[" << i << "]: " << semidone[i] << endl;
                i++;
                numbersemi++;

                parse = strtok(NULL, "|");
            }
        }
        else
        {
            parse = strtok(charin, ";");

            while (parse != NULL)
            {
                semidone[i] = parse;

                cout << "This is in semidone[" << i << "]: " << semidone[i] << endl;
                i++;
                numbersemi++;

                parse = strtok(NULL, ";");
            }
        }

        if (a == 1)
        {
            for (int k = 0; k < numbersemi; k++)
            {
                int j = 0;
                char** useme = new char* [input.size()+1];

                parse = strtok(semidone[k], " ");
                while (parse != NULL)
                {
                    useme[j] = parse;

                    cout << "This is in useme[" << j << "]: " << useme[j] << endl;
                    j++;

                    parse = strtok(NULL, " ");
                }

                int pid = fork();

                if (pid == -1)
                {
                    perror("There was an error with fork().");
                    exit(1);
                }
                else if (pid == 0)
                {

                    if (execvp(useme[0], useme) == -1)
                    {
                        perror("There was an error in execvp.");
                    }

                    delete [] useme;

                    exit(1);
                }
                else if (pid > 0)
                {
                    int x;
                    if (waitpid(-1, &x, 0) == -1)
                    {
                        perror("There was an error with wait().");
                    }
                    if (x != 0)
                    {
                        break;
                    }
                }
            }
        }
        else if (o == 1)
        {
            for (int k = 0; k < numbersemi; k++)
            {
                int j = 0;
                char** useme = new char* [input.size()+1];

                parse = strtok(semidone[k], " ");
                while (parse != NULL)
                {
                    useme[j] = parse;

                    cout << "This is in useme[" << j << "]: " << useme[j] << endl;
                    j++;

                    parse = strtok(NULL, " ");
                }

                int pid = fork();

                if (pid == -1)
                {
                    perror("There was an error with fork().");
                    exit(1);
                }
                else if (pid == 0)
                {

                    if (execvp(useme[0], useme) == -1)
                    {
                        perror("There was an error in execvp.");
                    }

                    delete [] useme;

                    exit(1);
                }
                else if (pid > 0)
                {
                    int x;
                    if (waitpid(-1, &x, 0) == -1)
                    {
                        perror("There was an error with wait().");
                    }
                    if (x == 0)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            for (int k = 0; k < numbersemi; k++)
            {
                int j = 0;
                char** useme = new char* [input.size()+1];

                parse = strtok(semidone[k], " ");
                while (parse != NULL)
                {
                    useme[j] = parse;

                    cout << "This is in useme[" << j << "]: " << useme[j] << endl;
                    j++;

                    parse = strtok(NULL, " ");
                }

                int pid = fork();

                if (pid == -1)
                {
                    perror("There was an error with fork().");
                    exit(1);
                }
                else if (pid == 0)
                {

                    if (execvp(useme[0], useme) == -1)
                    {
                        perror("There was an error in execvp.");
                    }

                    delete [] useme;

                    exit(1);
                }
                else if (pid > 0)
                {
                    if (wait(0) == -1)
                    {
                        perror("There was an error with wait().");
                    }
                }
            }
        }

        cout << "$ ";
        getline(cin, input);


        if (input.find("#") !=  string::npos)
        {
            input.at(input.find("#")) = '\0';
        }


        a = 0;
        o = 0;
        if (input.find("&&") != string::npos)
        {
            a = true;
        }
        else if (input.find("||") != string::npos)
        {
            o = true;
        }

        delete [] charin;
        delete [] semidone;
    }
    return 0;
}
