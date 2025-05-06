#include <iostream>
#include <chrono>
#include <string>
#include <map>
#include <random>
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
    PriorityQueue<string>* pq;
    PriorityQueue<string>* linkedList = new PriorityQueueLinkedList<string>();
    PriorityQueue<string>* heap = new PriorityQueueMinHeap<string>();
    PriorityQueue<string>* fibonacciHeap = new PriorityQueueFibonacciHeap<string>();

    int structures[] = {0, 1,2};
    map<int, string> structuresMap = {
            {0, "Linked List"},
            {1, "Heap"},
            {2, "Fibonacci Heap"}
    };

    int operationsNumber[] = {1000, 5000, 10000, 50000, 100000};

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

        cout << "Structure: " << structuresMap[structure] << "\n";

        for (int num : operationsNumber) {
            while (!pq->isEmpty()) pq->dequeue();

            double enqueueTime = 0;
            double peekTime = 0;
            for (int i = 0; i < num; ++i) {
                string elementName;
                elementName += getRandomCapitalLetter();
                elementName += getRandomCapitalLetter();
                auto start = chrono::high_resolution_clock::now();
                pq->enqueue(elementName, generateRandomPriority());
                auto end = chrono::high_resolution_clock::now();
                enqueueTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                pq->peek();
                end = chrono::high_resolution_clock::now();
                peekTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            double modifyTime = 0;
            for (int i = 0; i < num; ++i) {
                string elementName;
                elementName += getRandomCapitalLetter();
                elementName += getRandomCapitalLetter();
                auto start = chrono::high_resolution_clock::now();
                pq->modifyPriority(elementName, generateRandomPriority());
                auto end = chrono::high_resolution_clock::now();
                modifyTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            double dequeueTime = 0;
            for (int i = 0; i < num; ++i) {
                auto start = chrono::high_resolution_clock::now();
                pq->dequeue();
                auto end = chrono::high_resolution_clock::now();
                dequeueTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

			double sizeTime = 0;
			for (int i = 0; i < num; ++i) {
				auto start = chrono::high_resolution_clock::now();
				pq->getSize();
				auto end = chrono::high_resolution_clock::now();
				sizeTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
			}

            cout << "n: " << num << "; "
                 << "Enqueue: " << enqueueTime << " us; "
                 << "Peek: " << peekTime << " us; "
                 << "Dequeue: " << dequeueTime << " us; "
				 << "Size: " << sizeTime << " us; "
				 << "Modify: " << modifyTime << " us\n";

			double averageEnqueueTime = enqueueTime / num;
			double averagePeekTime = peekTime / num;
			double averageDequeueTime = dequeueTime / num;
			double averageModifyTime = modifyTime / num;
			double averageSizeTime = sizeTime / num;

			cout << "n: " << num << "; "
				<< "Average Enqueue: " << averageEnqueueTime << " us; "
				<< "Average Peek: " << averagePeekTime << " us; "
				<< "Average Dequeue: " << averageDequeueTime << " us; "
				<< "Average Size: " << averageSizeTime << " us; "
				<< "Average Modify: " << averageModifyTime << " us\n";
        }

        cout << endl << endl;
    }

    delete linkedList;
    delete heap;
    delete fibonacciHeap;
    return 0;
}
