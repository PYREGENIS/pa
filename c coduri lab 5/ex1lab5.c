#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// --- Implementare Stivă ---
typedef struct {
    int top;
    int a[MAX];
} Stack;

void initStack(Stack* s) { s->top = -1; }
bool isFullStack(Stack* s) { return s->top >= MAX - 1; }
bool isEmptyStack(Stack* s) { return s->top < 0; }

bool push(Stack* s, int x) {
    if (isFullStack(s)) {
        printf("Stack Overflow\n");
        return false;
    }
    s->a[++(s->top)] = x;
    return true;
}

int pop(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->a[(s->top)--];
}

// --- Implementare Coadă ---
typedef struct {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->array = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

bool isFullQueue(Queue* q) { return q->size == q->capacity; }
bool isEmptyQueue(Queue* q) { return q->size == 0; }

void enqueue(Queue* q, int item) {
    if (isFullQueue(q)) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = item;
    q->size = q->size + 1;
}

int dequeue(Queue* q) {
    if (isEmptyQueue(q)) return -1;
    int item = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return item;
}