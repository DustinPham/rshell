#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int pid = fork();

    if (pid == -1)
    {
        perror("There was an error with fork().");
        exit(1);
    }
    else if (pid == 0)
    {
        cout << "$ ";
        char input[1024] = {0};
        cin.getline(input, 1024);

        char* parse;
        char** store;
        store = new char *[1024];

        int i = 0;

        parse = strtok(input, " ;");

        while (parse != NULL)
        {
            store[i] = parse;
            cout << "This is in store[" << i << "]: " << store[i]  <<endl;
            i++;
            parse = strtok(NULL, " ;");
        }

        if (-1 == execvp(store[0], store))
        {
            perror("There was an error in execvp.");
        }

        cout << "THIS IS THE END OF THE CHILD" << endl;

        exit(1);
    }
    else if (pid > 0)
    {
        if (-1 == wait(0))
        {
            perror("There was an error with wait().");
        }
        cout << "THIS IS THE PARENT" << endl;
    }

    return 0;
}
