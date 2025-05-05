#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>
#include "PriorityQueueLinkedList.h"
#include "PriorityQueueFibonacciHeap.h"

using namespace std;

int main() {
    srand(time(nullptr));

    // Instantiate both priority queue types
    PriorityQueue<string>* pq;
    PriorityQueue<string>* linkedList = new PriorityQueueLinkedList<string>();
    PriorityQueue<string>* fibonacciHeap = new PriorityQueueFibonacciHeap<string>();

    int structures[] = {0, 2};
    map<int, string> structuresMap = {
            {0, "Linked List"},
            {2, "Fibonacci Heap"}
    };

    // Number of operations to test
    int operationsNumber[] = {1000, 5000, 10000, 50000, 100000};

    for (int structure : structures) {
        switch (structure) {
            case 0:
                pq = linkedList;
                break;
            case 2:
                pq = fibonacciHeap;
                break;
        }

        cout << "Structure: " << structuresMap[structure] << "\n";

        for (int num : operationsNumber) {
            while (!pq->isEmpty()) pq->dequeue();

            // Enqueue & Peak
            double enqueueTime = 0;
            double peekTime = 0;
            for (int i = 0; i < num; ++i) {
                auto start = chrono::high_resolution_clock::now();
                pq->enqueue("A", rand() % 1000);
                auto end = chrono::high_resolution_clock::now();
                enqueueTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                pq->peek();
                end = chrono::high_resolution_clock::now();
                peekTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            // Dequeue
            double dequeueTime = 0;
            for (int i = 0; i < num; ++i) {
                auto start = chrono::high_resolution_clock::now();
                pq->dequeue();
                auto end = chrono::high_resolution_clock::now();
                dequeueTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            //Results
            cout << "n: " << num << "; "
                 << "Enqueue: " << enqueueTime << " us; "
                 << "Peek: " << peekTime << " us; "
                 << "Dequeue: " << dequeueTime << " us\n";
        }

        cout << endl;
    }
    delete linkedList;
    delete fibonacciHeap;
    return 0;
}
