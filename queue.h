#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
    int top, itemSize, size, bottom;
    char *data;
};

#endif