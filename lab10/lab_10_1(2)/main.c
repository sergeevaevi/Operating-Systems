#include <stdio.h>
#include <unistd.h>

int main() {
    if(unlink("/home/llen/CLionProjects/lab10_1/cmake-build-debug/song.txt")){
        printf ("Cannot open file.\n");
        return 1;
    }
    return 0;
}
