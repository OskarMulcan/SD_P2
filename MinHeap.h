#ifndef MINHEAP_H
#define MINHEAP_H

#include "DynamicArray.h"

//Minimum heap class template
template <typename T>
class MinHeap {
public:
	MinHeap() = default; //Default constructor
	MinHeap(int capacity); //Constructor with initial capacity
	~MinHeap() = default; //Destructor
	void insert(const T& element); //Insert element into the heap
	void removeMin(); //Remove minimum element from the heap
	T extractMin(); //Extract minimum element from the heap
	const T& min() const; //Get minimum element (const version)
	bool empty() const; //Check if the heap is empty
private:
	void heapifyUp(); //Heapify up operation
	void heapifyDown(); //Heapify down operation
	DynamicArray<T> heap_; //Dynamic array to store heap elements
};

//Constructor with initial capacity
template <typename T>
MinHeap<T>::MinHeap(int capacity) {
	if (capacity < 0)
		throw std::out_of_range("Given capacity is negative"); //Check for negative capacity
	heap_ = DynamicArray<T>(capacity); //Initialize heap with given capacity
}

//Destructor
template <typename T>
void MinHeap<T>::insert(const T& element) {
	heap_.pushBack(element); //Add element to the end
	heapifyUp(); //Heapify up to maintain heap property
}

//Insert element into the heap
template <typename T>
void MinHeap<T>::removeMin() {
	if (heap_.empty())
		throw std::out_of_range("Heap is empty"); //Check if heap is empty
	std::swap(heap_[0], heap_[heap_.size() - 1]); //Swap minimum element with last element
	heap_.popBack(); //Remove last element
	heapifyDown(); //Heapify down to maintain heap property
}

//Remove minimum element from the heap
template <typename T>
T MinHeap<T>::extractMin() {
	T minimal = min(); //Get minimum element
	removeMin(); //Remove minimum element
	return minimal; //Return minimum element
}

//Extract minimum element from the heap
template <typename T>
const T& MinHeap<T>::min() const {
	if (heap_.empty())
		throw std::out_of_range("Heap is empty"); //Check if heap is empty
	return heap_.front(); //Return minimum element
}

//Check if the heap is empty
template <typename T>
bool MinHeap<T>::empty() const {
	return heap_.empty(); //Check if heap is empty
}

//Heapify up operation
template <typename T>
void MinHeap<T>::heapifyUp() {
	int i = heap_.size() - 1; //Start from the last element
	while (i > 0) {
		int parent = (i - 1) / 2; //Get parent index
		if (heap_[i] < heap_[parent]) {
			std::swap(heap_[i], heap_[parent]); //Swap with parent if current element is smaller
			i = parent; //Move to parent index
		}
		else
			break;
	}
}

//Heapify down operation
template <typename T>
void MinHeap<T>::heapifyDown() {
	int size = heap_.size(); //Get size of heap
	int i = 0; //Start from the root
	while (2 * i + 1 < size) {
		int left = 2 * i + 1; //Get left child index
		int right = 2 * i + 2; //Get right child index
		int child = i; //Assume current element is the smallest
		if (left < size && heap_[left] < heap_[child])
			child = left; //Update child index if left child is smaller
		if (right < size && heap_[right] < heap_[child])
			child = right; //Update child index if right child is smaller

		if (child != i) {
			std::swap(heap_[i], heap_[child]); //Swap with smallest child
			i = child; //Move to child index
		}
		else
			break;
	}
}


#endif // !MINHEAP_H