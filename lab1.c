#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <string.h>
#include <fcntl.h>

/*
    - U1610131 - Madiyor Abdukhashimov
        Lab Assignment Number 4
*/

void fibonacci_writer(int *array){
    int f1 = 0;
    int f2 = 1;
    int next = 0;
    array[0] = 0;
    array[1] = 1;
    for(size_t i = 0; i < 18; i++)
    {
        next = f1 + f2;
        f1 = f2;
        f2 = next;
        array[i + 2] = next;
    }
}

void forWard(char *path, const char *folder){
    sprintf(path, "./%s", folder);
}

int main(int argc, char const *argv[])
{
    int array[20];
    fibonacci_writer(array);
    const char *homedir;
    char nextDir[250];
    int hd;
    char temp[250];
    memset(temp, '\0', 250);
    const char ID[8] = "U1610131";
    const char *name = "Madiyor";
    const char *lastName = "Abdukhashimov";
    const char *fileName = "this_is_Awesome.txt";
    int fd = 0;
    memset(nextDir, '\0', 250);

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    hd = chdir(homedir);

    if (hd < 0) {
        printf("%s", "Could not change the directory!\n");
        exit(1);
    }

    mkdir(ID, 0777);
    // make a directory called ID
    forWard(nextDir, ID);
    // create the pathName for ID
    chdir(nextDir);
    // get inside the directory
    mkdir(name, 0777);
    // Make directory with name
    memset(nextDir, '\0', 250);
    // clear our buffer nexDir
    forWard(nextDir, name);
    // create the pathName
    chdir(nextDir);
    // get inside the directory
    mkdir(lastName, 0777);
    // make lastName Directory
    memset(nextDir, '\0', 250);
    // clear our buffer nexDir
    forWard(nextDir, lastName);
    // create the path
    chdir(nextDir);
    // get inside the directory
    fd = open(fileName, O_RDWR|O_CREAT, 0667);
    // open filewith permissions 
    for(size_t i = 0; i < 20; i++)
    {
        sprintf(temp,"%d", array[i]);
        write(fd, temp ,strlen(temp));
        write(fd, " " ,1);
    }
    
    memset(nextDir, '\0', 250);

    sprintf(nextDir, "%s/%s/%s/%s/%s", homedir, ID, name, lastName, fileName);
    
    if (symlink(nextDir, "../this_is_Awesome.symlink") < 0){
        printf("error");
        exit(0);
    }
    chdir("../");
    system("pwd");
    if (symlink(nextDir, "../this_is_Awesome.symlink") < 0){
        printf("error");
        exit(0);
    }
    return 0;
}