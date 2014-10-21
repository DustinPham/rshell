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

    int comment = input.find('#');
    if (comment != string::npos)
    {
        input.at(comment) = '\0';
    }

    char* charin = new char[input.size()+1];
    strcpy(charin, input.c_str());
    //charin now has the user's input in c string, terminated by null

    //while (input != "exit")
    {
        int numbersemi = 0;
        int i = 0;
        //semidone holds each commands separated by ;
        char* parse;
        char** semidone;
        semidone = new char* [input.size()+1];

        parse = strtok(charin, ";");

        while (parse != NULL)
        {
            semidone[i] = parse;

            cout << "This is in semidone[" << i << "]: " << semidone[i] << endl;
            i++;
            numbersemi++;
            parse = strtok(NULL, ";");
        }

        cout << "numbersemi beginning of for: " << numbersemi << endl;

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

            cout << "I DONT THINK SO" << endl;

            int pid = fork();

            cout << "AM I FORKING NOW?" << endl;

            if (pid == -1)
            {
                perror("There was an error with fork().");
                exit(1);
            }
            else if (pid == 0)
            {
                cout << "HEY YING" << endl;

                if (execvp(useme[0], useme) == -1)
                {
                    perror("There was an error in execvp.");
                }

                delete [] useme;

                exit(1);
            }
            else if (pid > 0)
            {
                //int x;
                //if (waitpid(-1, &x, 0) == -1)
                if (wait(0) == -1)
                {
                    perror("There was an error with wait().");
                }
            }
        }
        /*
        cout << "$ ";
        string input;
        getline(cin, input);

        int comment = input.find('#');
        if (comment != string::npos)
        {
            input.at(comment) = '\0';
        }

        strcpy(charin, input.c_str());
        */
    }







    return 0;
}
