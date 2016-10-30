#include <fcntl.h>   
#include <unistd.h>
#include <iostream>
using namespace std;
int main()
{
    char buf[50];
  int fd = open("test.txt", O_RDWR| O_APPEND);
  if(-1 == fd)  
  { 
    cout << "open error" << endl;
  }
/*****************test1***********************/
//查看O_APPEND打开时位置
  off_t CurrentPosition = lseek(fd, 0, SEEK_CUR);  
  if(CurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  cout << "Position at open:  " << CurrentPosition << endl;
  //打开之后马上读取文件
   if(read(fd, &buf, 5) == -1)
  { 
    cout << "read error" << endl;
    close(fd);
    return 0;
  }
  cout<<"read open on append:"<<buf<<endl; 
  //打开之后读取文件之后的位置
  CurrentPosition = lseek(fd, 0, SEEK_CUR);  
  if(CurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  cout << "Position at open after read:  " << CurrentPosition << endl;
/***********************test2****************/
  //定位到文件开始
  if(lseek(fd, 0, SEEK_SET) == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  //查看定位到文件开始之后的位置
  CurrentPosition = lseek(fd, 0, SEEK_CUR);  
  if(CurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
 cout << "Position after lseek to begin:  " << CurrentPosition << endl;
  //读取定位到文件开始之后的数据
  if(read(fd, &buf, 5) == -1)
  { 
    cout << "read error" << endl;
    close(fd);
    return 0;
  }
  cout<<"read after lseek to begin:"<<buf<<endl;
  //查看读取文件数据之后的位置
  off_t NewCurrentPosition = lseek(fd, 0, SEEK_CUR); 
  if(NewCurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  cout << "Position after read :" << NewCurrentPosition << endl;
  /*******************test3********************/
  //定位到文件末尾
  if(lseek(fd, 0, SEEK_END) == -1)//
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  //查看定位到文件末尾之后的位置
  CurrentPosition = lseek(fd, 0, SEEK_CUR);  
  if(CurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
 cout << "Position after lseek to end:  " << CurrentPosition << endl;
  //定位到文件末尾读取文件
  if(read(fd, &buf, 5) == -1)
  { 
    cout << "read error" << endl;
    close(fd);
    return 0;
  }
  cout<<"read after lseek to end:"<<buf<<endl;
  /********************test4***********************/
  //定位到文件开始之后5个字节
  if(lseek(fd, 5, SEEK_SET) == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
  //查看重定位之后的位置
  CurrentPosition = lseek(fd, 0, SEEK_CUR);  
  if(CurrentPosition == -1)
  {
    cout << "lseek error" << endl;
    close(fd);
    return 0;
  }
 cout << "Position after lseek to 5:  " << CurrentPosition << endl;
 //读取重定位之后的文件
  if(read(fd, &buf, 5) == -1)
  { 
    cout << "read error" << endl;
    close(fd);
    return 0;
  }
  cout<<"read after lseek to 5:"<<buf<<endl;

  close(fd);

}
