#include <iostream>
#include "PriorityQueueLinkedList.h"
#include "PriorityQueue.h"

int main() {
    PriorityQueue<int>* pq = new PriorityQueueLinkedList<int>();

    pq->enqueue(1, 0);
    std::cout << pq->getSize() << "\n";
    pq->enqueue(2, 10);
    pq->enqueue(4,-1);
    std::cout << pq->peek() << "\n";
    std::cout << pq->dequeue() << "\n";
    std::cout << pq->peek() << "\n";
    pq->modifyPriority(2, -20);
    pq->enqueue(7, -19);
    std::cout << pq->peek();
    std::cout << pq->getSize() << "\n";


}
