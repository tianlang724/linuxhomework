#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <atomic>  
#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)
struct Node { int value; Node* next; };
std::atomic<Node*> node0(nullptr);
using namespace std;
int main()
{
 
    Node* node1 = new Node{ 1, node0 };
    Node* node2=node1;
    node2->value=2;
    if(CAS(&node1,node2,node0))
         cout<<"yes"<<endl;
    if(node0.compare_exchange_weak(node1, node0))
        cout<<"atomic yes"<<endl;
	return 0;
}