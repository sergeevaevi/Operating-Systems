#include <stdio.h>
#include <stdlib.h>

int global;

void just_func(int n, int *local, void *pointer) {
    void *q = malloc(128);
    double y;
    printf("%p: Address of just_func is \n", just_func);
    printf("%p: Address of y is \n", &y);
    printf("%p: Address of local is \n", local);
    printf("%p: Address of q is \n", q);
    if (&y < local) {
        printf("Stack address is decreasing\n");
    } else {
        printf("Wow! Stack address is increasing\n");
    }
    if (q < pointer) {
        printf("Wow! Heap address is decreasing\n");
    } else {
        printf("Heap address is increasing\n");
    }
}

int main() {
    int local = 5;
    void *p = malloc(64);
    printf("%p : address of main is \t\n", main);
    printf("%p: Address of global is \n", &global);
    printf("%p: Address of local is \n", &local);
    just_func(0, &local, p);
    printf("%p: Address of p is   \n", p);
    printf("%p: Address of &p is \n", &p);

    char name[20];
    puts("Enter name: ");
    scanf("%19s", name);
    printf("Hello,  %s.\n\n\tNice to see you.\n", name);

    puts("Enter name: ");
    scanf("%19s", name);
    printf("Hello,  %s.\n\n\tNice to see you.\n", name);


    char *name1=name;
    char a_letter=name1[0];
    name1[0]=name1[3];
    name1[3]=a_letter;
    puts(name1);

    return 0;
}