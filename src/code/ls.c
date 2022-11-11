#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    
    char* path;
    if (argc >= 2) path = argv[1];
    else path = ".";
    mydir = opendir(path);

    while((myfile = readdir(mydir)) != NULL)
    {
        sprintf(buf, "%s/%s", path, myfile->d_name);
        stat(buf, &mystat);
        printf("%zu\t%s\n",mystat.st_size, myfile->d_name);
    }
    closedir(mydir);
}