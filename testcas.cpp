#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <atomic>  
#include <math.h>
#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)
#define l 2
struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);
std::atomic<Node*> node0(nullptr);
using namespace std;
int main()
{
 
    Node* node1 = new Node{ 1, node0 };
    Node* node2=node1;
    node2->value=2;
    if(CAS(&node1,node2,node0))
         cout<<"yes"<<endl;
    Node* newNode = new Node{ 0, list_head };
	//for(int i = 0; i < 1000;i++)
	Node* newNode2=newNode;
    newNode2->value=2;
	// next is the same as: list_head = newNode, but in a thread-safe way:
	if(list_head.compare_exchange_weak(newNode->next, newNode)) 
    cout<<"atomic yes"<<endl;


    //验证循环数组长度为2的幂可以优化循环取余
    int size=16;
    int r;
    for(int i=0;i<20;i++)
    {
        r=i & ( size -1 );
        cout<< r<<" ";
    }
    cout<<endl;
    //验证数组的长度可以用define的值的函数初始化，不可以用变量
    int array[(int)pow(2,l)]={0};
    array[0]=5;
    for(int i=0;i<4;i++)
    cout<<array[i]<<endl;

    //验证atomic给普通int赋值
     uint32_t CurrentWriteIndex;
     std::atomic<int> m_CurrentWriteIndex;
     CurrentWriteIndex = m_CurrentWriteIndex;

     //
     std::atomic<int> a;
     a=1;
     int b=1;
     int c=2;
     a.compare_exchange_weak(b,c);
     cout<<a<<endl;
	return 0;
}