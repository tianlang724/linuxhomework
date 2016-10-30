#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <unistd.h>
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
    func<int>(&foo,a);
    return 0;
}