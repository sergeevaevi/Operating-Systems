#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>
#include <sys/stat.h>
/*

struct dirent {
    ino_t          d_ino;       */
/* inode number *//*

    off_t          d_off;       */
/* offset to the next dirent *//*

    unsigned short d_reclen;    */
/* length of this record *//*

    unsigned char  d_type;      */
/* type of file; not supported
                                 by all file system types *//*

    char           d_name[256]; */
/* filename *//*

};
*/

void prStat(char *name, struct stat *sb) {
    printf("dev=%lu ino=%lu mode=%o  uid=%u gid=%u \n"
           "rdev=%lu " "size=%ld blocks=%ld blksize=%ld nlink=%lu \n"
           "atime=%ld mtime=%ld ctime=%ld %s\n \n",

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
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char dir_name[MAXPATHLEN];

    char l[2];
    char c;
    scanf("%s", l);
    c = getchar();
    if(c != '\n' ) {
        scanf("%s", dir_name);
    }else{
        getcwd(dir_name, MAXPATHLEN);
    };

    printf("Directory is %s \n", dir_name);
    dir = opendir(dir_name);

    if (!dir) {
        perror("diropen");
        return (1);
    };

    if (l[1] == 'l') {
        while ((entry = readdir(dir)) != NULL) {
            printf("%lu - %s [%d] %d \n \n",
                   entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
            stat(entry->d_name, &st);
            prStat(entry->d_name, &st);
        };
    } else {
        while ((entry = readdir(dir)) != NULL) {
            printf("%lu - %s [%d] %d\n \n",
                   entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
        };
    }
    closedir(dir);
    return 0;
}
