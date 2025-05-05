﻿#ifndef PRIORITY_QUEUE_MIN_HEAP_H
#define PRIORITY_QUEUE_MIN_HEAP_H

#include "PriorityQueue.h"
#include "MinHeap.h"

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
class PriorityQueueMinHeap : public PriorityQueue<T> {
private:
	MinHeap<Node<T>>* heap;
public:
	//Constructor
	PriorityQueueMinHeap() {
		heap = new MinHeap<Node<T>>();
	}
	//Destructor
	~PriorityQueueMinHeap() {
		delete heap;
		heap = nullptr;
	}
	//Implementation of enqueue, dequeue, peek and getSize methods
	void enqueue(T element, int priority) override {
		Node<T> node(element, priority);
		heap->insert(node);
	}
	T dequeue() override {
		Node<T> node = heap->extractMin();
		return node.element;
	}
	T peek() const override {
		Node<T> node = heap->min();
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

#endif // !PRIORITY_QUEUE_MIN_HEAP_H
