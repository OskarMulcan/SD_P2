#include <iostream>
#include <string>
#include "PriorityQueueLinkedList.h"
#include "PriorityQueue.h"
#include "PriorityQueueFibonacciHeap.h"

using namespace std;

int main() {
    PriorityQueue<string>* pq = new PriorityQueueFibonacciHeap<string>();

    pq->enqueue("A", 10);
    cout << pq->getSize() << endl;
    cout << pq->dequeue() << endl;
    cout << pq->getSize() << endl;
    pq->enqueue("A", 10);
    pq->enqueue("B", 12);
    pq->enqueue("C", 1);
    cout << pq->peek() << endl;
    cout << pq->dequeue() << endl;
    cout << pq->peek();
    pq->modifyPriority("B", -1);
    cout << pq->peek() << endl;
    cout << pq->dequeue() << endl;
    cout << pq->peek() << endl;
    pq->enqueue("Z", 100);
    cout << pq->getSize() << endl;
    pq->modifyPriority("Z", -100);
    cout << pq->peek() << endl;
    cout << pq->dequeue() << endl;
    cout << pq->getSize();
    pq->enqueue("Q", -1000000);
    cout << pq->peek() << endl;
    pq->enqueue("R", -5000);
    pq->enqueue("L", -2000000);
    cout << pq->dequeue() << endl;
    pq->modifyPriority("Q", 1000000);
    cout << pq->peek() << endl;
    cout << pq->dequeue() << endl;
    cout << pq->getSize() << endl;
    cout << pq-> dequeue() << endl;
    cout << pq->getSize() << endl;
    cout << pq->peek();






}
