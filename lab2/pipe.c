/*//
// Created by llen on 29.03.2020.
//
const int N = 2;
void set_read(int* lpipe)
{
    dup2(lpipe[0], STDIN_FILENO);
    close(lpipe[0]); // we have a copy already, so close it
    close(lpipe[1]); // not using this end
}

void set_write(int* rpipe)
{
    dup2(rpipe[1], STDOUT_FILENO);
    close(rpipe[0]); // not using this end
    close(rpipe[1]); // we have a copy already, so close it
}

void fork_and_chain(int* lpipe, int* rpipe)
{
    if(!fork())
    {
        if(lpipe) // there's a pipe from the previous process
            set_read(lpipe);
        // else you may want to redirect input from somewhere else for the start
        if(rpipe) // there's a pipe to the next process
            set_write(rpipe);
        // else you may want to redirect out to somewhere else for the end

        // blah do your stuff
        // and make sure the child process terminates in here
        // so it won't continue running the chaining code
    }
}

int
main(int argc, char *argv[]) {
// This assumes there are at least two processes to be chained :)

// two pipes: one from the previous in the chain, one to the next in the chain
    int lpipe[2], rpipe[2];

// create the first output pipe
    pipe(rpipe);

// first child takes input from somewhere else
//    fork_and_chain(NULL, rpipe);
    if(!fork())
    {
        dup2(rpipe[1], STDOUT_FILENO);
        close(rpipe[0]); // not using this end
        close(rpipe[1]); // we have a copy already, so close it
    }
// output pipe becomes input for the next process.
    lpipe[0] = rpipe[0];
    lpipe[1] = rpipe[1];
*//*
// chain all but the first and last children
    for (i = 1; i < N - 1; i++) {
        pipe(rpipe); // make the next output pipe
        fork_and_chain(lpipe, rpipe);
        close(lpipe[0]); // both ends are attached, close them on parent
        close(lpipe[1]);
        lpipe[0] = rpipe[0]; // output pipe becomes input pipe
        lpipe[1] = rpipe[1];
    }*//*

    if(!fork())
    {
        dup2(lpipe[0], STDIN_FILENO);
        close(lpipe[0]); // we have a copy already, so close it
        close(lpipe[1]); // not using this end
    }

// fork the last one, its output goes somewhere else
//    fork_and_chain(lpipe, NULL);
    close(lpipe[0]);
    close(lpipe[1]);
}*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    char* msg_1 = "message 1";
    char* msg_2 = "message 2";
    int size = 16;
    char buf[size];
    int p[2];
    /*pipe() создает канал передачи данных для связи процессов. р0 - конец чтения, а р1 - для записи*/
    int r;
    pipe(p);
    if (fork()) {
        write(p[1], msg_1, size);
        write(p[1], msg_2, size);
        close(p[1]);
        wait(NULL);
    }
    else {
        close(p[1]);
        r = read(p[0], buf, size);
        while (r>0){
            printf("%s\n", buf);
            r = read(p[0], buf, size);
        }
        printf("GOODBYE\n");
    }
    return 0;
}

