#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>


int countFiles(DIR *dir) {
    int num_f = 0;
    struct dirent *entry;
    while (entry = readdir(dir)) {
        num_f++;
    }
    return num_f - 2;
}

void fileCounter(char *dir_name) {
    DIR *dir;
    if (!(dir = opendir(dir_name))) {
        printf("bad dir! \n");
        return;
    }
    int count = countFiles(dir);
    printf("\n %s contains %d files or folders \n", dir_name, count);
}

void findEmpty(char *dir_name) {
    DIR *dir;
    struct stat st;
    struct dirent *entry;
    int count = 0;
    if (!(dir = opendir(dir_name))) {
        printf("bad dir! \n");
        return;
    }
    while (entry = readdir(dir)) {
        stat(entry->d_name, &st);
        if (st.st_size == 0) {
            printf("%s/%s file size is 0 \n", dir_name, entry->d_name);
            count++;
        }
    }
    printf("%s contains %d empty files \n", dir_name, count);
}

void writeDir(char *dir_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char buff[256];
    strcpy(buff, dir_name);;
    while (1) {
        int curr_f = 0;
        int num_f = 0;
        if (!(dir = opendir(dir_name))) {
            printf("it's a file\n");
            break;
        }
        char new_dir_name[256];
        strcpy(new_dir_name, dir_name);
        while (entry = readdir(dir)) {
            num_f++;
        }
        if (num_f == 2) {
            printf("empty\n");
        }
        rewinddir(dir);
        int c;
        while (entry = readdir(dir)) {

            if (curr_f > 0) {//find current folder/file
                c = curr_f;
                while (c > 0) {
                    entry = readdir(dir);
                    c--;
                }
            }

            char *p = strstr(entry->d_name, ".");//check for . and ..
            if (!(p - entry->d_name)) {
                rewinddir(dir);
                curr_f++;
                if (curr_f == num_f) {
                    break;
                }
                continue;
            }

            printf("%s\n",
                   entry->d_name);
            strcat(new_dir_name, "/");
            strcat(new_dir_name, entry->d_name);
            closedir(dir);
            printf("opening %s ...\n", new_dir_name);
            if (!stat(entry->d_name, &st)) {
                printf("size of it is %ld\n", st.st_size);
            }
            writeDir(new_dir_name);
            printf("close %s...\n\n", new_dir_name);

            curr_f++;
            strcpy(new_dir_name, buff);//new_dir_name = buff;
            strcpy(dir_name, buff);//dir_name = buff;
            if (!(dir = opendir(dir_name))) {
                break;
            }
            if (curr_f == num_f) {
                break;
            }

        }
        if (curr_f == num_f) {
            break;
        }
    }
}

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
           name
    );
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char dir_name[MAXPATHLEN] = "/", buff[MAXPATHLEN];

    char c;
    c = getchar();
    if (c != '\n') {
        scanf("%s", buff);
    } else {
        getcwd(dir_name, MAXPATHLEN);
    }
    if (buff[0] == 'A') {
        getcwd(dir_name, MAXPATHLEN);
        printf("Directory is %s \n\n", dir_name);
        fileCounter(dir_name);
    } else {
        if (buff[0] == 'e') {
            getcwd(dir_name, MAXPATHLEN);
            printf("Directory is %s \n\n", dir_name);
            findEmpty(dir_name);
        } else {
            strcat(dir_name, buff);
            printf("Directory is %s \n\n", dir_name);
            c = getchar();
            if (c != '\n') {
                if (c == ' ') {
                    scanf("%s", buff);
                    if (buff[0] == '-' && buff[1] == 'A') {
                        fileCounter(dir_name);
                    }
                    if (buff[0] == '-' && buff[1] == 'e') {
                        findEmpty(dir_name);
                    }
                }
            } else {
                writeDir(dir_name);
            }
        }
    }


    return 0;
}
