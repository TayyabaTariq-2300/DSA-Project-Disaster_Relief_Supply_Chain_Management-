// supplyQueue.cpp
#include "supplyQueue.h"
#include <iostream>

supplyQueue::supplyQueue() : size(0) {}

void supplyQueue::enqueue(Supplies sup) {
    if (size == 10) {
        std::cout << "\nQueue is full.\n";
        return;
    }

    int i = size - 1;
    while (i >= 0 && sup.getMed() > queue[i].getMed()) {
        queue[i + 1] = queue[i];
        i--;
    }
    queue[i + 1] = sup;
    size++;
}

Supplies supplyQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "\n Queue is empty.\n";
    }
    Supplies front = queue[0];
    for (int i = 1; i < size; i++) {
        queue[i - 1] = queue[i];
    }
    size--;
    return front;
}

bool supplyQueue::isEmpty() {
    return size == 0;
}
