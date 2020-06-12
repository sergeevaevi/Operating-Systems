#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void myStat(char *name, struct stat *sb) {
    printf("dev=%lu ino=%lu mode=%o  uid=%u gid=%u \n"
           "rdev=%lu " "size=%ld blocks=%ld blksize=%ld nlink=%lu \n"
           "atime=%ld mtime=%ld ctime=%ld %s\n",
           sb->st_dev,    /* device inode resides on */
           sb->st_ino,    /* inode's number */
           sb->st_mode,    /* inode protection mode */
           sb->st_uid,    /* user-id of owner */
           sb->st_gid,    /* group-id of owner */
           sb->st_rdev,    /* device type,	for special file */
           sb->st_size,    /* file size, in bytes */
           sb->st_blocks,    /* blocks allocated for file */
           sb->st_blksize,    /* optimal file sys I/O ops blocksize */
           sb->st_nlink,    /* number or hard links to the file */

           sb->st_atime,    /* time of last access */
           sb->st_mtime,    /* time of last data modification */
           sb->st_ctime,    /* time of last file status change */
            //sb->st_flags,	/* user defined flags for file */
            //sb->st_gen	/* file generation number */
           name
    );
}

void showHardLinks(char *name, struct stat *sb) {
    printf("nlink = %lu  %s\n",
           sb->st_nlink,    /* number or hard links to the file */
           name
    );
}

int
main(int argc, char *argv[]){
    char c;
    int sec = 10;
    FILE *fd = fopen("song.txt", "r");
    if (fd == NULL) {
        printf ("Cannot open file.\n");
        exit(1);
    }

    struct stat sb;
    stat("song.txt", &sb);
    showHardLinks("song.txt", &sb);
    clock_t timer_begin = clock();
    getchar();
    do
    {
        while( fscanf( fd, "%c", &c) != EOF ) {
            printf( "%c",  c);
        }
        fseek(fd, 0, SEEK_SET);
        if((clock() - timer_begin)/CLOCKS_PER_SEC > sec){
            stat("song.txt", &sb);
            myStat("song.txt", &sb);
            break;
        }
    }
    while(1);

    fclose(fd);
    return 0;
}
