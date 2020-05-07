#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


/*int
main(int argc, char *argv[])
{
    int rc = fork();
    int status;
      if (rc < 0) {
           // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1)
      }else
          if(!rc){
              printf("HELLO\n");
          }else{
              while(waitpid(rc, &status, WNOHANG)){
                  sleep(1);
              }
                  printf("GOODBYE\n");

          }
    return 0 ;
}*/

void sig_rec(int signal) {
    printf("GOODBYE\n");
}

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int parent_pid = getpid();
    signal(SIGCONT, sig_rec);//Системный вызов signal позволяет
    pause();//Системный вызов pause приостанавливает

    int rc = fork();

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("HELLO\n");
        kill(parent_pid, SIGCONT); //Системный вызов kill
        // посылает сигнал процессу или группе процессов, которые заданы идентификатором pid.
    } else {
        signal(SIGCONT, sig_rec);//Системный вызов signal позволяет
        // вызывающему процессу выбрать один из трех возможных способов
        // реакции на получение определенного сигнала.
        pause();//Системный вызов pause приостанавливает
        // вызывающий процесс до получения им сигнала.
        // Сигнал должен отличаться от тех сигналов, которые игнорируются вызывающим процессом.
    }
    return 0;
}
