#include "CLFileHandle.h"
#include "CLStatus.h"
#include <iostream>
using namespace std;
int main()
{
    CLFileHandle fh;
    CLStatus s=fh.OpenFile("makefile.txt",O_RDWR);
    if(!s.IsSuccess())
    {
        cout<<"open error"<<endl;
        s.PrintfErrorcode();
        return -1;
    }
    char buf[100];
    memset(buf,0,sizeof(buf));
    //测试连续读以及读缓存不够的情况'
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"read 10: "<<buf<<endl;
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"read 10 "<<buf<<endl;
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"read 10 "<<buf<<endl;
    //测试改变位置读的内容是否正确
    fh.SetFileOffset(10,SEEK_SET);
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"lseek 10 read: "<<buf<<endl;
    //测试读完之后写是否正确
    char ss[11]="0000000000";
    cout<<"offset"<<fh.GetFileOffset()<<"write"<<endl;
    fh.WriteFile(ss);
    //测试连续写
    cout<<"offset"<<fh.GetFileOffset()<<"write"<<endl;
    fh.WriteFile(ss);
    cout<<"offset"<<fh.GetFileOffset()<<"write"<<endl;
    fh.WriteFile(ss);
    //测试写完之后读
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"read after write 1: "<<buf<<endl;
    cout<<"offset"<<fh.GetFileOffset()<<"write"<<endl;
    fh.WriteFile(ss);
    fh.ReadFile(buf,10);
    cout<<"offset"<<fh.GetFileOffset()<<"read after write 2 "<<buf<<endl;
}