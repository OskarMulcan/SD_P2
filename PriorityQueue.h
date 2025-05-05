#ifndef SD_P2_PRIORITYQUEUE_H
#define SD_P2_PRIORITYQUEUE_H

template <typename T>
class PriorityQueue {
public:
    virtual void enqueue(T element, int priority) = 0;
    virtual T dequeue() = 0;
    virtual T peek() const = 0;
    virtual int getSize() const = 0;
    virtual void modifyPriority(T element, int newPriority) = 0;
    virtual bool isEmpty() const = 0;
    virtual ~PriorityQueue() = default;
};

#endif //SD_P2_PRIORITYQUEUE_H
