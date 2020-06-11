#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define _8  0b0010000000100000001000000010000000100000001000000010000000100000
#define _4  0b100000001000000010000000100000
#define _2  0b10000000100000
#define _1  0b100000

void check(char *str, char *old) {
    for (int i = 0; i < strlen(str); i++)
        if ((str[i] ^= _1) != old[i]) {
            printf("BAD!\n");
            return;
        }
}

int main() {
    char str[TMP_MAX];
    char backup[TMP_MAX] = "";
    scanf("%s", str);
    unsigned int len = strlen(str);
    printf("length is %d \n", len);
    unsigned int left = len;
    unsigned int to = 0;
    strcpy(backup, str);
    while ((left / 8 > 0 || left % 8 == 0) && left) {
        *((long long *) (str + to)) ^= _8;
        left -= 8;
        to += 8;
    }
    while ((left / 4 > 0 || left % 4 == 0) && left) {
        *((int *) (str + to)) ^= _4;
        left -= 4;
        to += 4;
    }
    while ((left / 2 > 0 || left % 2 == 0) && left) {
        *((short *) (str + to)) ^= _2;
        left -= 2;
        to += 2;
    }
    while (left > 0) {
        *((char *) (str + to)) ^= _1;
        left -= 1;
        to += 1;
    }

    printf("%s ", str);

    check(str, backup);
    return 0;
    /*SomeTextForSomeSymbols 22
     AnotherOneALittleBitLongerISupposeNotTooMuch 44
    AndShortOne 11
     */
}
