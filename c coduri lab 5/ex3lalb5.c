#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Refolosim o structură simplă de stivă
typedef struct {
    int top;
    int a[MAX];
} SimpleStack;

void initS(SimpleStack* s) { s->top = -1; }
bool isEmp(SimpleStack* s) { return s->top < 0; }
void pushS(SimpleStack* s, int x) { s->a[++(s->top)] = x; }
int popS(SimpleStack* s) { return s->a[(s->top)--]; }

typedef struct {
    SimpleStack s1;
    SimpleStack s2;
} QueueUsingStacks;

void initQUS(QueueUsingStacks* q) {
    initS(&q->s1);
    initS(&q->s2);
}

void enqueueQUS(QueueUsingStacks* q, int x) {
    // Punem elementul în prima stivă
    pushS(&q->s1, x);
}

int dequeueQUS(QueueUsingStacks* q) {
    if (isEmp(&q->s1) && isEmp(&q->s2)) {
        printf("Coada este goala\n");
        return -1;
    }
    // Dacă a doua stivă e goală, mutăm tot din s1 în s2
    if (isEmp(&q->s2)) {
        while (!isEmp(&q->s1)) {
            pushS(&q->s2, popS(&q->s1));
        }
    }
    return popS(&q->s2);
}