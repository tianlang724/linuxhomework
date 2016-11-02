#include <stdio.h>
#include <errno.h>  //errno
#include <unistd.h> //memset
#include <stdlib.h> //free
#include <fcntl.h>
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    int fd=open("test.txt",O_RDWR);
    off_t offset=lseek(fd,0,SEEK_CUR);
    cout<<offset<<endl;
    close(fd);
    fd=open("test.txt",O_RDWR|O_APPEND);
    offset=lseek(fd,0,SEEK_CUR);
    cout<<offset<<endl;
    char buf[20];
    read(fd,buf,20);
    cout<<buf<<endl;
    memset(buf,0,sizeof(buf));
    //offset=lseek(fd,5,SEEK_CUR);
    lseek(fd,3,SEEK_SET);
    read(fd,buf,20);
    cout<<"lseek 3"<<buf<<endl;
    lseek(fd,0,SEEK_SET);
    read(fd,buf,20);
    cout<<"lseek 0"<<buf<<endl;
    //cout<<strlen(buf)<<offset<<endl;
    close(fd);
    return 0;
}