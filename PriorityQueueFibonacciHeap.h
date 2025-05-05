#include <stdexcept>
#include <algorithm>
#include "PriorityQueue.h"
#ifndef SD_P2_PRIORITYQUEUEFIBONACCIHEAP_H
#define SD_P2_PRIORITYQUEUEFIBONACCIHEAP_H

template <typename T>
struct FibNode {
    T element;
    int priority;
    int degree;
    bool mark;

    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;

    FibNode(T element, int priority)
            : element(element), priority(priority), degree(0), mark(false),
              parent(nullptr), child(nullptr), left(this), right(this) {}
};

template <typename T>
class PriorityQueueFibonacciHeap : public PriorityQueue<T> {

private:
    FibNode<T>* minNode;
    int n;

    //Takes one tree and makes it a subtree of another tree
    void link(FibNode<T>* nodeCh, FibNode<T>* nodeP){
        nodeCh->left->right = nodeCh->right;
        nodeCh->right->left = nodeCh->left;

        nodeCh->parent = nodeP;
        if(!nodeP->child){
            nodeP->child = nodeCh;
            nodeCh->left = nodeCh;
            nodeCh->right = nodeCh;
        } else {
            nodeCh->left = nodeP->child;
            nodeCh->right = nodeP->child->right;
            nodeP->child->right->left = nodeCh;
            nodeP->child->right = nodeCh;
        }
        nodeP->degree++;
        nodeCh->mark = false;
    }

    //Connects the subtree of the given node with the root list
    void mergeWithRootList(FibNode<T>* node){
        if(!minNode) {
            minNode = node;
            node->left = node;
            node->right = node;
        } else {
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;
        }

        if (node->priority < minNode->priority){
            minNode = node;
        }
    }

    //Cuts the subtree of nodeCh from its parent nodeP and connects it with the root list
    void cut(FibNode<T>* nodeCh, FibNode<T>* nodeP){
        if(nodeCh->right == nodeCh){
            nodeP->child = nullptr;
        } else {
            nodeCh->left->right = nodeCh->right;
            nodeCh->right->left = nodeCh->left;
        }
        nodeP->degree--;

        nodeCh->right = nodeCh;
        nodeCh->left = nodeCh;
        mergeWithRootList(nodeCh);
        nodeCh->parent = nullptr;
        nodeCh->mark = false;
    }

    //Tests the parent's patience – if multiple children cut, it cuts itself too
    void cascadingCut(FibNode<T>* node){
        FibNode<T>* nodeP = node->parent;
        if(nodeP) {
            if(!node->mark) {
                node->mark = true;
            } else {
                cut(node, nodeP);
                cascadingCut(nodeP);
            }
        }
    }

    //Removes the given node entirely (for utility purposes -> modifyPriority)
    void remove(FibNode<T>* node){
        decreasePriority(node, INT32_MIN);
        dequeue();
    }

    //Recursively looks for the node storing the given element and provides a pointer to it
    FibNode<T>* findNode(FibNode<T>* start, const T& element) {
        if (!start) return nullptr;

        FibNode<T>* current = start;
        do {
            if (current->element == element) return current;

            FibNode<T>* foundInChild = findNode(current->child, element);
            if (foundInChild) return foundInChild;

            current = current->right;
        } while (current != start);

        return nullptr;
    }

    //Decreases the priority of the given node and reorganizes the heap in necessary
    void decreasePriority(FibNode<T>* node, int newPriority) {
        if (newPriority > node->priority) {
            throw std::invalid_argument("New priority is greater than the current priority");
        }
        node->priority = newPriority;
        FibNode<T>* parent = node->parent;

        if (parent && node->priority < parent->priority) {
            cut(node, parent);
            cascadingCut(parent);
        }

        if (node->priority < minNode->priority) {
            minNode = node;
        }
    }

    //Keeps the Fibonacci heap nice and neat; makes it so that it doesn't have two roots of the same degree, then rebuilds the root list
    void consolidate(){
        int maxDegree = 45;
        FibNode<T>* trees[46] = {nullptr };

        FibNode<T>* start = minNode;
        FibNode<T>* min = minNode;

        do {
            FibNode<T>* node1 = min;
            min = min->right;
            int degree = node1->degree;
            while (trees[degree]) {
                FibNode<T>* node2 = trees[degree];
                if (node1->priority > node2->priority) std::swap(node1, node2);
                link(node2, node1);
                trees[degree] = nullptr;
                degree++;
            }
            trees[degree] = node1;
        } while (min != start);

        minNode = nullptr;
        for (auto & treeRoot : trees) {
            if (treeRoot) {
                treeRoot->left = treeRoot;
                treeRoot->right = treeRoot;
                if (!minNode) {
                    minNode = treeRoot;
                } else {
                    mergeWithRootList(treeRoot);
                }
            }
        }
}

public:
    PriorityQueueFibonacciHeap() : minNode(nullptr), n(0) {}

    void enqueue(T element, int priority) {
        FibNode<T> *node = new FibNode<T>(element, priority);
        if (!minNode) {
            minNode = node;
        } else {
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;
            if (priority < minNode->priority) {
                minNode = node;
            }
        }
        n++;
    }
    T dequeue(){
        if (!minNode) throw std::runtime_error("Heap is empty");

        FibNode<T>* min = minNode;
        if(min->child){
            FibNode<T>* minCh = min->child;
            do{
                FibNode<T>* next = minCh->right;
                mergeWithRootList(minCh);
                minCh->parent = nullptr;
                minCh = next;
            } while(minCh != min->child);
        }

        min->left->right = min->right;
        min->right->left = min->left;

        if(min == min->right){
            minNode = nullptr;
        } else {
            minNode = min->right;
            consolidate();
        }
        T element = min->element;
        delete min;
        n--;
        return element;

    }

    T peek() const{
        if (!minNode) throw std::runtime_error("Heap is empty");
        return minNode->element;
    }

    int getSize() const{
        return n;
    }

    //Uses decreasePriority if the priority is to be decreased
    //If it is to be increased it merges all the children of the node with the root list and then does the same itself
    void modifyPriority(T element, int newPriority) {
        FibNode<T>* node = findNode(minNode, element);
        if (!node) return;

        if (newPriority < node->priority) {
            decreasePriority(node, newPriority);
        } else if (newPriority > node->priority) {
            if (node->child) {
                FibNode<T>* child = node->child;
                do {
                    FibNode<T>* next = child->right;
                    mergeWithRootList(child);
                    child->parent = nullptr;
                    child = next;
                } while (child != node->child);
            }
            remove(node);
            enqueue(element, newPriority);
        }
    }

    bool isEmpty() const {
        return minNode == nullptr;
    }
};

#endif //SD_P2_PRIORITYQUEUEFIBONACCIHEAP_H
