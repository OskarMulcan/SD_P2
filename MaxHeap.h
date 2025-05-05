#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "DynamicArray.h"

//Maximum heap class template
template <typename T>
class MaxHeap {
public:
	MaxHeap() = default; //Default constructor
	MaxHeap(int capacity); //Constructor with initial capacity
	~MaxHeap() = default; //Destructor
	void insert(const T& element); //Insert element into the heap
	void removeMax(); //Remove maximum element from the heap
	T extractMax(); //Extract maximum element from the heap
	const T& max() const; //Get maximum element (const version)
	bool empty() const; //Check if the heap is empty
private:
	void heapifyUp(); //Heapify up operation
	void heapifyDown(); //Heapify down operation
	DynamicArray<T> heap_; //Dynamic array to store heap elements
};

//Constructor with initial capacity
template <typename T>
MaxHeap<T>::MaxHeap(int capacity) {
	if (capacity < 0)
		throw std::out_of_range("Given capacity is negative"); //Check for negative capacity
	heap_ = DynamicArray<T>(capacity); //Initialize heap with given capacity
}

//Destructor
template <typename T>
void MaxHeap<T>::insert(const T& element) {
	heap_.pushBack(element); //Add element to the end
	heapifyUp(); //Heapify up to maintain heap property
}

//Insert element into the heap
template <typename T>
void MaxHeap<T>::removeMax() {
	if (heap_.empty())
		throw std::out_of_range("Heap is empty"); //Check if heap is empty
	std::swap(heap_[0], heap_[heap_.size() - 1]); //Swap maximium element with last element
	heap_.popBack(); //Remove last element
	heapifyDown(); //Heapify down to maintain heap property
}

//Remove maximium element from the heap
template <typename T>
T MaxHeap<T>::extractMax() {
	T maximum = max(); //Get maximium element
	removeMax(); //Remove maximium element
	return maximum; //Return maximium element
}

//Extract maximium element from the heap
template <typename T>
const T& MaxHeap<T>::max() const {
	if (heap_.empty())
		throw std::out_of_range("Heap is empty"); //Check if heap is empty
	return heap_.front(); //Return maximium element
}

//Check if the heap is empty
template <typename T>
bool MaxHeap<T>::empty() const {
	return heap_.empty(); //Check if heap is empty
}

//Heapify up operation
template <typename T>
void MaxHeap<T>::heapifyUp() {
	int i = heap_.size() - 1; //Start from the last element
	while (i > 0) {
		int parent = (i - 1) / 2; //Get parent index
		if (heap_[i] > heap_[parent]) {
			std::swap(heap_[i], heap_[parent]); //Swap with parent if current element is greater
			i = parent; //Move to parent index
		}
		else
			break;
	}
}

//Heapify down operation
template <typename T>
void MaxHeap<T>::heapifyDown() {
	int size = heap_.size(); //Get size of heap
	int i = 0; //Start from the root
	while (2 * i + 1 < size) {
		int left = 2 * i + 1; //Get left child index
		int right = 2 * i + 2; //Get right child index
		int child = i; //Assume current element is the greatest
		if (left < size && heap_[left] > heap_[child])
			child = left; //Update child index if left child is greater
		if (right < size && heap_[right] > heap_[child])
			child = right; //Update child index if right child is greater

		if (child != i) {
			std::swap(heap_[i], heap_[child]); //Swap with greatest child
			i = child; //Move to child index
		}
		else
			break;
	}
}


#endif // !MAXHEAP_H