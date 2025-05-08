#pragma once

#include "Supplies.h"

class supplyQueue {
    Supplies queue[10];
    int size;
public:
    supplyQueue();
    void enqueue(Supplies s);
    Supplies dequeue();
    bool isEmpty();
};

