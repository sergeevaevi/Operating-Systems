//
// Created by llen on 29.03.2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    char* msg_1 = "message 1\n";
    char* msg_2 = "message 2\n";
    int size = 8;
    char buf[size];
    int p[2];
    /*pipe() создает канал передачи данных для связи процессов. р0 -  чтения, а р1 - для записи*/
    int r;
    pipe(p);
    if (fork()) {  /* Child writes msg to pipe */
        write(p[1], msg_1, size);
        write(p[1], msg_2, size);
        close(p[1]);
        wait(NULL); /* Wait for child */
    }
    else {  /* Parent reads from pipe */
        close(p[1]); /* Close unused write end */
        r = read(p[0], buf, size);
        while (r>0){
            printf("%s\n", buf);
            r = read(p[0], buf, size);
        }
        printf("GOODBYE\n");
    }
    return 0;
}

