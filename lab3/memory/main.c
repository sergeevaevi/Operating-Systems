#include <stdio.h>
#include "malloc.h"
#include <time.h>

int main() {
    int mb_count = 0;
    scanf("%d", &mb_count);
    int *p = (int*)malloc(mb_count*1024*1024);
    int n = mb_count*(1024*1024/sizeof(int));
    if(!p) {
        printf("Memory request failed.\n");
        return 1;
    }
    int sec;
    scanf("%d", &sec);
    int i = 0;
    clock_t timer_begin = clock();
    while(1){
        if(i == n){
            i = 0;
        }
        p[i] = 0;
      //1  printf("%d\t", p[i]);
        i++;
        if((clock() - timer_begin)/CLOCKS_PER_SEC > sec){
            printf ("\n Too Long!");
            break;
        }
    }
    printf ("\n The End!");
    free(p);

}
