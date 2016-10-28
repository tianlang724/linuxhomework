#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <unistd.h>

template<typename T>
struct Node
{
    T* data;
    Node<T>* next;
};

template<typename T>
struct Queue
{
    Node<T>* head;
    Node<T>* tail;
    std::atomic<int> nodeCounts = 0;
};
template<typename T>
class FreeLockQueue
{
    
}