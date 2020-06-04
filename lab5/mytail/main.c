#include <stdio.h>
#include <sys/stat.h>

int main() {
    char name[20];
    scanf("%s", name);
    printf("%s\n", name);
    int l_count = 0;
    scanf("%d", &l_count);
    FILE *fp;
    // getc(f);
    fp = fopen(name, "r");
    if (!fp) {
        printf("Cannot open file.\n");
        return (1);
    }
    fseek(fp, -1, SEEK_END);
    struct stat buff;
    stat(name, &buff);
    printf("Size of the file is: %ld\n", buff.st_size);

    long i;
    if ((i = ftell(fp)) == -1L)
        printf("A file error has occurred.\n");

    i = ftell(fp);
    int pos = 1;
    char c;
    for (int l = 0; l < l_count; ++l) {
        while (c != '\n' && pos < buff.st_size) {
            pos++;
            if (fread(&c, sizeof(c), 1, fp)) {
                fseek(fp, -(pos), SEEK_END);
                i = ftell(fp);
            }
        }
        c = ' ';
    }
    if(pos < buff.st_size){
        i+=2;
        pos-=2;
    }
    fseek(fp, i, SEEK_SET);
    for (int l = 0; l < l_count; ++l) {
        while (c != '\n' && pos > 0) {
            pos--;
            i++;
            if (fread(&c, sizeof(c), 1, fp)) {
                printf("%c", c);
                fseek(fp, i, SEEK_SET);
                i = ftell(fp);
            }
        }
        c = ' ';
    }
    fclose(fp);

    return 0;
}
