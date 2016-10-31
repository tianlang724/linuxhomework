#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <unistd.h>
#include <thread>
template <typename T,int size=0>
class Foo
{
    int a;
};

template <typename T,int size>
void func(Foo<T,size> &tt,int a) 
{
}

int main()
{
    Foo<int> foo;
    int a=9;
    func<int>(foo,a);
    std::thread t2(func<int>,foo,a);//thread 不支持模板函数
    return 0;
}