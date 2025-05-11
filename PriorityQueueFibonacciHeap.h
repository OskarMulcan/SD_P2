#include <stdexcept>
#include <algorithm>
#include <vector>
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
        node->left = node;
        node->right = node;

        if (!minNode) {
            minNode = node;
        } else {
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;

            if (node->priority < minNode->priority) {
                minNode = node;
            }
        }
    }


    //Cuts the subtree of nodeCh from its parent nodeP and connects it with the root list
    void cut(FibNode<T>* nodeCh, FibNode<T>* nodeP){
        // Remove nodeCh from the sibling list
        if (nodeCh->right == nodeCh) {
            nodeP->child = nullptr;
        } else {
            nodeCh->left->right = nodeCh->right;
            nodeCh->right->left = nodeCh->left;
            if (nodeP->child == nodeCh) {
                nodeP->child = nodeCh->right;
            }
        }

        nodeP->degree--;

        // Reset nodeCh's sibling pointers
        nodeCh->left = nodeCh;
        nodeCh->right = nodeCh;

        // Move to root list
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

    void consolidate(){
        std::vector<FibNode<T>*> roots;

        FibNode<T>* curr = minNode;
        if (curr) {
            do {
                roots.push_back(curr);
                curr = curr->right;
            } while (curr != minNode);
        }

        int maxDegree = 45;
        FibNode<T>* trees[46] = {nullptr};

        for (FibNode<T>* node : roots) {
            int degree = node->degree;
            while (trees[degree]) {
                FibNode<T>* other = trees[degree];
                if (node->priority > other->priority) std::swap(node, other);
                link(other, node);
                trees[degree] = nullptr;
                degree++;
            }
            trees[degree] = node;
        }

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

    /*
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
     */
    void enqueue(T element, int priority) override {
        FibNode<T>* node = new FibNode<T>(element, priority);
        mergeWithRootList(node);
        n++;
    }
    T dequeue(){
        if (!minNode) throw std::runtime_error("Dequeue: Heap is empty");

        FibNode<T>* min = minNode;
        if (min->child) {
            std::vector<FibNode<T>*> children;
            FibNode<T>* child = min->child;
            do {
                children.push_back(child);
                child = child->right;
            } while (child != min->child);

            for (FibNode<T>* ch : children) {
                mergeWithRootList(ch);
                ch->parent = nullptr;
            }

            min->child = nullptr;
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
        if (!minNode) throw std::runtime_error("Peek: Heap is empty");
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

        int oldPriority = node->priority;

        if (newPriority == oldPriority) return;

        if (newPriority < oldPriority) {
            decreasePriority(node, newPriority);
            return;
        }

        // Increasing priority
        node->priority = newPriority;

        // If node has a parent and violates heap order, cut and cascade
        FibNode<T>* parent = node->parent;
        if (parent && node->priority > parent->priority) {
            cut(node, parent);
            cascadingCut(parent);
        }

        // Reinsert children (conservative way to avoid broken child pointer rings)
        if (node->child) {
            std::vector<FibNode<T>*> children;
            FibNode<T>* start = node->child;
            FibNode<T>* curr = start;

            do {
                children.push_back(curr);
                curr = curr->right;
            } while (curr && curr != start);  // null-check protects against corrupted circular list
            node->child = nullptr;
            node->degree = 0;

            for (FibNode<T>* ch : children) {
                ch->left = ch->right = ch; // break circular links to avoid multi-link bugs
                ch->parent = nullptr;
                mergeWithRootList(ch);
            }
        }

        // Ensure minNode is still correct
        if (minNode == nullptr || node->priority < minNode->priority) {
            minNode = node;
        }
    }



    bool isEmpty() const {
        return minNode == nullptr;
    }
};

#endif //SD_P2_PRIORITYQUEUEFIBONACCIHEAP_H
