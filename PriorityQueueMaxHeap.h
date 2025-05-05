#ifndef PRIORITY_QUEUE_MAX_HEAP_H
#define PRIORITY_QUEUE_MAX_HEAP_H

#include "PriorityQueue.h"
#include "MaxHeap.h"

template <typename T>
struct Node {
	T element;
	int priority;
	Node* next;
	Node(T element, int priority) : element(element), priority(priority), next(nullptr) {}
	Node operator<(const Node& other) const {
		return priority < other.priority;
	}
	Node operator>(const Node& other) const {
		return priority > other.priority;
	}
	Node operator==(const Node& other) const {
		return priority == other.priority;
	}
	Node operator!=(const Node& other) const {
		return priority != other.priority;
	}
	Node operator<=(const Node& other) const {
		return priority <= other.priority;
	}
	Node operator>=(const Node& other) const {
		return priority >= other.priority;
	}
	Node operator=(const Node& other) const {
		element = other.element;
		priority = other.priority;
		return *this;
	}
	Node(const Node& other) {
		element = other.element;
		priority = other.priority;
	}
};

template <typename T>
class PriorityQueueMaxHeap : public PriorityQueue<T> {
private:
	MaxHeap<Node<T>>* heap;
public:
	//Constructor
	PriorityQueueMaxHeap() {
		heap = new MaxHeap<Node<T>>();
	}
	//Destructor
	~PriorityQueueMaxHeap() {
		delete heap;
		heap = nullptr;
	}
	//Implementation of enqueue, dequeue, peek and getSize methods
	void enqueue(T element, int priority) override {
		Node<T> node(element, priority);
		heap->insert(node);
	}
	T dequeue() override {
		if (heap->empty()) throw std::runtime_error("Heap is empty");
		Node<T> node = heap->extractMax();
		return node.element;
	}
	T peek() const override {
		if (heap->empty()) throw std::runtime_error("Heap is empty");
		Node<T> node = heap->max();
		return node.element;
	}
	int getSize() const override {
		return heap->size();
	}
	//Implementatotion of changing priority of selected element
	void modifyPriority(T element, int newPriority) override {
		int index = heap->find(Node<T>(element, 0));
		if (index == -1) {
			throw std::invalid_argument("Element not found in the heap");
		}
		Node<T> node = heap->get(index);
		node.priority = newPriority;
		heap->replace(index, node);
	}
};

#endif
