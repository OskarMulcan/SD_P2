#include <iostream>
#include <chrono>
#include <string>
#include <map>
#include <random>
#include <cassert>
#include "PriorityQueueLinkedList.h"
#include "PriorityQueueFibonacciHeap.h"
#include "PriorityQueueMinHeap.h"
#include "MinHeap.h"

using namespace std;

string getRandomCapitalLetter() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist('A', 'Z');

    char randomChar = static_cast<char>(dist(gen));
    return string(1, randomChar);
}

int generateRandomPriority() {
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> dist(1, 1000000);
	return dist(gen);
}

int main() {

    PriorityQueueFibonacciHeap<int> heap1;
    heap1.enqueue(10, 5);
    heap1.enqueue(20, 3);
    heap1.enqueue(30, 7);

    assert(heap1.peek() == 20);
    assert(heap1.getSize() == 3);
    int testsNum = 50;

    PriorityQueue<string>* pq;
    PriorityQueue<string>* linkedList = new PriorityQueueLinkedList<string>();
    PriorityQueue<string>* heap = new PriorityQueueMinHeap<string>();
    PriorityQueue<string>* fibonacciHeap = new PriorityQueueFibonacciHeap<string>();

    int structures[] = {0, 1, 2};
    map<int, string> structuresMap = {
            {0, "Linked List"},
            {1, "Heap"},
            {2, "Fibonacci Heap"}
    };

    int queueSize[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    for (int structure : structures) {
        switch (structure) {
            case 0:
                pq = linkedList;
                break;
            case 1:
                pq = heap;
                break;
            case 2:
                pq = fibonacciHeap;
                break;

        }
        cout << structuresMap[structure] << "\n";
        for (int size: queueSize) {
            double enqueueTime = 0;
            double dequeueTime = 0;
            double peekTime = 0;
            double modifyPriorityTime = 0;
            double getSizeTime = 0;

            for (int i = 0; i < testsNum; i++) {
                for (int j = 0; j < size; j++) {
                    string element = "";
                    element += getRandomCapitalLetter();
                    element += getRandomCapitalLetter();
                    pq->enqueue(element, rand() % 1000000);
                }
                //Enqueue
                string element = "";
                element += getRandomCapitalLetter();
                element += getRandomCapitalLetter();
                int priority = rand() % 1000000;
                auto start = chrono::high_resolution_clock::now();
                pq->enqueue(element, priority);
                auto stop = chrono::high_resolution_clock::now();
                pq->dequeue();
                enqueueTime += chrono::duration_cast<chrono::nanoseconds>(stop-start).count();

                //Dequeue
                start = chrono::high_resolution_clock::now();
                pq->dequeue();
                stop = chrono::high_resolution_clock::now();
                element = "";
                element += getRandomCapitalLetter();
                element += getRandomCapitalLetter();
                priority = rand() % 1000000;
                pq->enqueue(element, priority);
                dequeueTime += chrono::duration_cast<chrono::nanoseconds>(stop-start).count();

                //Peek
                start = chrono::high_resolution_clock::now();
                pq->peek();
                stop = chrono::high_resolution_clock::now();
                peekTime += chrono::duration_cast<chrono::nanoseconds>(stop-start).count();

                //GetSize
                start = chrono::high_resolution_clock::now();
                pq->getSize();
                stop = chrono::high_resolution_clock::now();
                getSizeTime += chrono::duration_cast<chrono::nanoseconds>(stop-start).count();

                //ModifyPriority
                element = "";
                element += getRandomCapitalLetter();
                element += getRandomCapitalLetter();
                priority = rand() % 1000000;
                start = chrono::high_resolution_clock::now();
                pq->modifyPriority(element, priority);
                stop = chrono::high_resolution_clock::now();
                modifyPriorityTime += chrono::duration_cast<chrono::nanoseconds>(stop-start).count();
                for (int i = 0; i < size; i++){
                    pq->dequeue();
                }
            }
            enqueueTime /= testsNum*1000;
            dequeueTime /= testsNum*1000;
            peekTime /= testsNum*1000;
            getSizeTime /= testsNum*1000;
            modifyPriorityTime /= testsNum*1000;
            cout << "Size: " << size <<"; Enqueue: " << enqueueTime << "; Dequeue: " << dequeueTime << "; Peek: "
            << peekTime << "; GetSize: " << getSizeTime << "; ModifyPriority: " << modifyPriorityTime << "\n";
        }
        cout << "\n";
    }
    delete linkedList;
    delete heap;
    delete fibonacciHeap;
}