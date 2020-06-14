#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

#define BLOCK 4096
#define CCITT  0b0001000000100001
#define FIRST 0b1000000000000000
#define FIRST_CHAR 0b10000000
#define START 0b1111111111111111

char pathname[FILENAME_MAX];
char xor_[] = "XOR-checksum:";
char fletcher_[] = "fletcher-checksum:";
char crc_[] = "CRC-checksum:";

double best_time = INT32_MAX;
double xor_time = 0;
double fr_time = 0;
double crc_time = 0;

void print_binary(int b) {
    for (int i = 0; i < 16; i++) {
        printf("%c", (b & 0x8000) ? '1' : '0');
        b <<= 1;
    }
    printf("\n");
}

void print_binary_8(int b) {
    for (int i = 0; i < 8; i++) {
        printf("%c", (b & 0x80) ? '1' : '0');
        b <<= 1;
    }
    printf("\n");
}

double get_time() {
    struct timeval t;
    if (gettimeofday(&t, NULL) == -1) {
        exit(1);
    }
    return (double) t.tv_sec + (double) t.tv_usec / 1000000;
}

unsigned char xor_checksum() {
    int fd;
    if ((fd = open(pathname, O_RDONLY)) == -1) { //Open for reading only
        exit(1);
    }
    double t = get_time();
    unsigned char xor = 0;
    char buff;
    int not_end = 0;
    while ((not_end = read(fd, &buff, 1)) != -1 && not_end) {
        if (buff != '\n') { //Without \n
            xor ^= (unsigned char) (buff - '0'); // char to int
        }
    }
    xor_time = get_time() - t;
    printf("XOR-checksum: %d \t for time %f \n", xor, xor_time);
    if (best_time > xor_time) {
        best_time = xor_time;
    }
    close(fd);
    return xor;
}

uint16_t fletcher_checksum() {
    int fd;
    if ((fd = open(pathname, O_RDONLY)) == -1) {//Open for reading only
        exit(1);
    }
    double t = get_time();
    char buff;
    int fletcher_a = 0;
    int fletcher_b = 0;
    int not_end = 0;

    while ((not_end = read(fd, &buff, 1)) != -1 && not_end) {
        if (buff != '\n') {
            fletcher_a = (buff /*- '0'*/ + fletcher_a) % 255; //8 bit
            fletcher_b = (fletcher_a + fletcher_b) % 255;
        }
    }
    uint16_t res = (fletcher_b << 8) | fletcher_a; // 16 bit
    /*uint8_t c0,c1,f0,f1;
    f0 = res & 0xff;
    f1 = (res >> 8) & 0xff;
    c0 = 0xff - (( f0 + f1) % 0xff);
    c1 = 0xff - (( f0 + c0 ) % 0xff);
    printf("Fletcher checksum %d, %d - %d, %d", f0, f1, c0, c1);
    */
    fr_time = get_time() - t;
    printf("fletcher-checksum: %d \t for time %f\n", res, fr_time);
    if (best_time > fr_time) {
        best_time = fr_time;
    }
    close(fd);
    return res;
}

unsigned short crc() {
    int fd;
    if ((fd = open(pathname, O_RDONLY)) == -1) { //Open for reading only
        exit(1);
    }
    struct stat sb;
    fd = stat(pathname, &sb);
    int size = sb.st_size;
    close(fd);
    if ((fd = open(pathname, O_RDONLY)) == -1) //Open for reading only
        exit(1);
    double t = get_time();
    int not_end = 0;
    unsigned short crc = START;
    unsigned char ch;
    int flag = 0;

    while ((not_end = read(fd, &ch, 1)) != -1 && not_end) {
        size -= sizeof(char);
        if (ch == '\n' && size == 0) {
            continue;
        }
        unsigned char i;
        unsigned short v = FIRST_CHAR;
        for (int j = 0; j < 8; j++) {
            if (crc & FIRST) { //check for first bit
                flag = 1;
            } else {
                flag = 0;
            }
            crc = crc << 1; //shift
            if (ch & v) { // Append next bit of message to end
                crc += 1;
            }
            if (flag) {
                crc = crc ^ CCITT;
            }
            v = v >> 1;// Another bit will be changed
        }
    }
    for (int j = 0; j < 16; j++) { // Last move
        if (crc & FIRST) {
            flag = 1;
        } else {
            flag = 0;
        }
        crc = crc << 1;
        if (flag) {
            crc = crc ^ CCITT;
        }
    }
    crc_time = get_time() - t;
    printf("CRC-checksum: %d 0x%X \t for time  %f\n", crc, crc, crc_time);
    if (best_time > crc_time) {
        best_time = crc_time;
    }
    close(fd);
    return crc;
}

int find_key_word_and_compare(char *key, FILE *infile, int i_key) {
    int st = 0;
    char word[30];
    while (!feof(infile)) {
        if (fscanf(infile, "%s", word) != 1) {
            perror("empty");
            exit(1);
        }
        if (!strcmp(word, key)) {
            int cks = 0;
            fscanf(infile, "%d", &cks);
            // printf("%d\n", cks);
            if (i_key != cks) {
                puts("Test failed! \n");
                return 1;
            }
            st++;
            break;
        }
    }
    if (!st) {
        puts("not found");
        return 1;
    }
    return 0;
}

void test(int i_xor, int i_fletcher, int i_crc) {
    int fdt;
    if ((fdt = open("test.txt", O_WRONLY | O_APPEND)) == -1) {
        exit(1);
    }
    if (write(fdt, &pathname, sizeof(pathname)) == -1){
        exit(1);
    }
    FILE *infile;
    int st = 0;
    char word[30];
    infile = fopen("test_ans.txt", "r+");
    if (infile == NULL) {
        perror("Error opening file \n");
        exit(1);
    }

    while (!feof(infile)) {
        if (fscanf(infile, "%s", word) != 1) {
            perror("empty \n");
            exit(1);
        }
        if (!strcmp(word, pathname)) {
            //printf("Find! %s\n", word);
            st++;
            break;
        }
    }
    if (!st) {
        puts("not found");
    }
    int i = find_key_word_and_compare(xor_, infile, i_xor);
    i += find_key_word_and_compare(fletcher_, infile, i_fletcher);
    i += find_key_word_and_compare(crc_, infile, i_crc);
    if (!i) {
        if (write(fdt, "\nTest passed \n", 15) == -1){
            exit(1);
        }
        puts("Test passed");
    } else{
        puts("Test failed!");

    }
    close(fdt);
}

void create_csum() {
    unsigned char xor = 0;
    unsigned char blocks[BLOCK];
    int fdr;
    int fdw;
    int not_end = 0;
    if ((fdr = open(pathname, O_RDONLY)) == -1) {
        exit(1);
    }
    if ((fdw = open("csum.txt", O_WRONLY | O_CREAT)) == -1) {
        exit(1);
    }
    while ((not_end = read(fdr, blocks, BLOCK)) != -1 && not_end) {
        for (int i = 0; i < not_end; i++) { //the number of bytes read is returned
            xor ^= blocks[i];
        }
        if (write(fdw, &xor, 1) == -1) {
            exit(1);
        }
    }
    close(fdr);
    close(fdw);
}

void check_csum() {
    int fdt;
    if ((fdt = open("test.txt", O_WRONLY | O_APPEND)) == -1) {
        exit(1);
    }
    unsigned char xor = 0;
    unsigned char blocks[BLOCK];
    unsigned char old_xor = 0;
    int fda;
    int fdo;
    int not_end = 0;

    if ((fda = open(pathname, O_RDONLY)) == -1) {
        exit(1);
    }
    if ((fdo = open("csum.txt", O_RDONLY)) == -1) {
        exit(1);
    }
    while ((not_end = read(fda, blocks, BLOCK)) != -1 && not_end) {
        for (size_t i = 0; i < not_end; i++) {
            xor ^= blocks[i];
        }

        if ((not_end = read(fdo, &old_xor, 1)) == -1) {
            exit(1);
        }
        if (old_xor != xor) {
            printf("Check-sum FAILED!\n");
            write(fdt, "Check-sum FAILED!\n", 25);
            exit(EXIT_FAILURE);
        }
    }
    printf("PASS check-sum\n");
    if (write(fdt, "PASS check-sum\n", 20) == -1){
        exit(1);
    }
    close(fda);
    close(fdo);
    close(fdt);
}

void time_check() {
    int fdt;
    if ((fdt = open("test.txt", O_WRONLY | O_APPEND)) == -1) {
        exit(1);
    }
    if (best_time == xor_time) {
        printf("Best time is XOR-time: %f \n", best_time);
        if (write(fdt, xor_, sizeof(xor_)) == -1){
            exit(1);
        }
    } else {
        if (best_time == fr_time) {
            printf("Best time is fletcher-time: %f \n", best_time);
            if (write(fdt, fletcher_, sizeof(fletcher_)) == -1){
                exit(1);
            }
        } else {
            printf("Best time is CRC-time: %f \n", best_time);
            if (write(fdt, crc_, sizeof(crc_)) == -1) {
                exit(1);
            }
        }
    }
    if (write(fdt, "\n", 1) == -1){
        exit(1);
    }
    close(fdt);
}

int main(int argc, char *argv[]) {
    printf("Path to file: \n");
    scanf("%s", pathname);

    int i_xor = xor_checksum();
    int i_fletcher = fletcher_checksum();
    int i_crc = crc();

    test(i_xor, i_fletcher, i_crc);

    create_csum();
    check_csum();

    time_check();

    return 0;
}
//    song.txt              //    crc
//    another_song.txt      //    xor
//    and_other.txt         //    crc
//    two.txt               //    xor
//    three.txt             //    fletcher
//    wiki1.txt             //    fletcher
//    wiki2.txt             //    fletcher
//    wiki3.txt             //    fletcher