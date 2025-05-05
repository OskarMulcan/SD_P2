#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"

#ifndef SD_P2_PRIORITYQUEUELINKEDLIST_H
#define SD_P2_PRIORITYQUEUELINKEDLIST_H

template <typename T>
struct Node {
    T element;
    int priority;
    Node* next;

    Node(T element, int priority) : element(element), priority(priority), next(nullptr) {}
};

template <typename T>
class PriorityQueueLinkedList : public PriorityQueue<T> {
private:
    Node<T>* head;

public:
    PriorityQueueLinkedList() : head(nullptr) {}

    void enqueue(T element, int priority) {
        Node<T>* newNode = new Node(element, priority);
        if (!head || priority < head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next && current->next->priority <= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    T dequeue() {
        if (!head) throw std::runtime_error("Queue is empty");
        Node<T>* temp = head;
        T element = temp->element;
        head = head->next;
        delete temp;
        return element;
    }

    int getSize() const {
        Node<T>* current = head;
        if(!head) return 0;
        int size = 1;
        while (current->next != nullptr){
            size++;
            current = current->next;
        }
        return size;
    }

    T peek() const {
        if (!head) throw std::runtime_error("Queue is empty");
        return head->element;
    }

    void modifyPriority(T element, int newPriority) {
        if (!head) return;

        if (head->element == element) {
            Node<T>* toReinsert = head;
            head = head->next;
            enqueue(toReinsert->element, newPriority);
            delete toReinsert;
            return;
        }

        Node<T>* prev = head;
        Node<T>* current = head->next;

        while (current) {
            if (current->element == element) {
                prev->next = current->next;
                enqueue(current->element, newPriority);
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void isEmpty() const{
        return head == nullptr;
    }

};

#endif //SD_P2_PRIORITYQUEUELINKEDLIST_H
