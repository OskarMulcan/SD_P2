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
	int find(const T& element) const; //Find element in the heap
	void remove(int index); //Remove element at index
	void replace(int index, const T& element); //Replace element at index
	const T& get(int index) const; //Get element at index (const version)
	int size() const; //Get size of the heap
private:
	void heapifyUp(); //Heapify up operation
	void heapifyUp(int index); //Heapify up operation with index
	void heapifyDown(); //Heapify down operation
	void heapifyDown(int index); //Heapify down operation with index
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

//Find element in the heap
template <typename T>
int MinHeap<T>::find(const T& element) const {
	return heap_.find(element); //Find element in the heap
}

//Remove element at index
template <typename T>
void MinHeap<T>::remove(int index) {
	if (index < 0 || index >= heap_.size())
		throw std::out_of_range("Index out of range"); //Check for valid index
	std::swap(heap_[index], heap_[heap_.size() - 1]); //Swap with last element
	heap_.popBack(); //Remove last element
	heapifyDown(index); //Heapify down to maintain heap property
	heapifyUp(index); //Heapify up to maintain heap property
}

//Replace element at index
template <typename T>
void MinHeap<T>::replace(int index, const T& element) {
	if (index < 0 || index >= heap_.size())
		throw std::out_of_range("Index out of range"); //Check for valid index
	T oldElement = heap_[index]; //Store old element
	heap_[index] = element; //Replace element at index
	if (element < oldElement)
		heapifyUp(index); //Heapify up if new element is smaller
	else
		heapifyDown(index); //Heapify down if new element is larger
}

//Get element at index (const version)
template <typename T>
const T& MinHeap<T>::get(int index) const {
	if (index < 0 || index >= heap_.size())
		throw std::out_of_range("Index out of range"); //Check for valid index
	return heap_[index]; //Return element at index
}

//Get size of the heap
template <typename T>
int MinHeap<T>::size() const {
	return heap_.size(); //Get size of the heap
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

//Heapify up operation with index
template <typename T>
void MinHeap<T>::heapifyUp(int index) {
	if (index < 0 || index >= heap_.size())
		throw std::out_of_range("Index out of range"); //Check for valid index
	int i = index; //Start from the given index
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

//Heapify down operation with index
template <typename T>
void MinHeap<T>::heapifyDown(int index) {
	if (index < 0 || index >= heap_.size())
		throw std::out_of_range("Index out of range"); //Check for valid index
	int size = heap_.size(); //Get size of heap
	int i = index; //Start from the given index
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