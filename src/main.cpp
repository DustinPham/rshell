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

    int comment = input.find("#");
    if (comment >= 0)
    {
        input.at(comment) = '\0';
    }

    int andd = input.find("&&");
    bool a = false;
    int orr = input.find("||");
    bool o = false;
    if (andd >= 0)
    {
        a = true;
    }
    else if (orr >= 0)
    {
        o = true;
    }

    //char* charin = new char[input.size()+1];
    //strcpy(charin, input.c_str());
    //charin now has the user's input in c string, terminated by null

    while (input != "exit")
    {
        char* charin = new char[input.size()+1];
        strcpy(charin, input.c_str());

        int numbersemi = 0;
        int i = 0;

        char* parse;
        char** semidone;
        semidone = new char* [input.size()+1];

        if (a == true)
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
        else if (o == true)
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

        if (a == true)
        {
            int j = 0;

            for (int k = 0; k < numbersemi; k++)
            {
                j = 0;
                char** useme;
                useme = new char* [input.size()+1];

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
        else if (o == true)
        {
            int j = 0;

            for (int k = 0; k < numbersemi; k++)
            {
                j = 0;
                char** useme;
                useme = new char* [input.size()+1];

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
            int j = 0;

            for (int k = 0; k < numbersemi; k++)
            {
                j = 0;
                char** useme;
                useme = new char* [input.size()+1];

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
        delete [] charin;

        cout << "$ ";
        getline(cin, input);

        int comment = input.find("#");
        if (comment >= 0)
        {
            input.at(comment) = '\0';
        }

        andd = input.find("&&");
        a = false;
        orr = input.find("||");
        o = false;
        if (andd >= 0)
        {
            a = true;
        }
        else if (orr >= 0)
        {
            o = true;
        }

        delete [] semidone;
    }
    return 0;
}
