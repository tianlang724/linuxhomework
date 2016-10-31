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
    CLStatus s1=fh.ReadFile(buf,10);
    if(!s1.IsSuccess())
    {
        cout<<"open error"<<endl;
        return -1;
    }
    cout<<"1"<<buf<<endl;
    fh.ReadFile(buf,10);
    cout<<"2"<<buf<<endl;
    fh.LseekFile(10,SEEK_SET);
    fh.ReadFile(buf,10);
    cout<<"3"<<buf<<endl;
    fh.LseekFile(10,SEEK_SET);
    char ss[6]="00000";
    fh.WriteFile(ss);

}