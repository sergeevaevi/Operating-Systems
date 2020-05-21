//
// Created by llen on 29.03.2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();
    if (rc == 0) // child process
    {
        close(STDOUT_FILENO);
        printf("Unvisible\n");
    }
    else if (rc > 0)
    {
        wait(NULL);
        printf("I am parent process\n");
    }
    else
    {
        printf("Error\n");
    }
    return 0;
}