#include <stdio.h>
#include <stdlib.h>  
#include <stdbool.h>
#include <string.h>
#include "Queue.h"

void push(Queue* q, int *item) {
    if (q->top > q->size) {
        q->size <<= 1;
        q->data = (char*)realloc(q->data, q->size);
        printf("Size Of Stack Doubled\n");
    }
    memcpy(q->data + q->top, item, q->itemSize);
    q->top += q->itemSize;
};

bool pop(Queue* q, void *item) {
    if (q->top <= 0) {
        printf("Invalid Pop\n");
        return false;
    }
    q->top -= q->itemSize;
    memcpy(item, q->data, q->itemSize);


    char *tempData = (char*)malloc(q->size);
    memcpy(tempData, q->data + q->itemSize, q->size - q->itemSize);
    free(q->data);
    q->data = tempData;
    return true;
};

bool isEmpty(Queue* q) {
    if (q->top == 0)
        return true;
    return false;
};

void print(Queue* q) {
    int* intData = (int*)q->data;
    for (int i = 0; i <= (q->top - q->itemSize)/4; i += 1)
        printf("%i ", intData[i]);

    printf("\n");
};

int main() {
    Queue q = {
        0,
        4, 
        100,
        0,
        (char*)malloc(100)
    };

    for (int i = 0; i < 200; i++)
        push(&q, &i);
    int x;
    
    print(&q);
    pop(&q, &x);
    push(&q, &x);
    pop(&q, &x);
    push(&q, &x);
    print(&q);
	
	return 0;
}