#include <stdlib.h>
#include <stdio.h>

int main() {
    int *data = malloc(100);
    free(data);
    printf("%d", data[1]);
}