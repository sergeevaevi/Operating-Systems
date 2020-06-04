#include <sys/stat.h>
#include <stdio.h>
#include <time.h>


void prStat(char *name, struct stat *sb) {
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

int main() {
    struct stat sb;
    char name[256];
    int fd;
    int i;
    scanf("%s", name);

    fd = stat(name, &sb);
    if (fd == -1) {
        perror(name);
        return 1;
    }
    prStat(name, &sb);
    return 0;
}
