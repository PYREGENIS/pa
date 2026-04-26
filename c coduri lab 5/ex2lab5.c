#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int top1;
    int top2;
} TwoStacks;

TwoStacks* createTwoStacks(int n) {
    TwoStacks* ts = (TwoStacks*)malloc(sizeof(TwoStacks));
    ts->size = n;
    ts->arr = (int*)malloc(n * sizeof(int));
    ts->top1 = -1;       // Pornește din stânga
    ts->top2 = n;        // Pornește din dreapta
    return ts;
}

void push1(TwoStacks* ts, int x) {
    if (ts->top1 < ts->top2 - 1) {
        ts->top1++;
        ts->arr[ts->top1] = x;
    } else {
        printf("Stack Overflow stiva 1\n");
    }
}

void push2(TwoStacks* ts, int x) {
    if (ts->top1 < ts->top2 - 1) {
        ts->top2--;
        ts->arr[ts->top2] = x;
    } else {
        printf("Stack Overflow stiva 2\n");
    }
}

int pop1(TwoStacks* ts) {
    if (ts->top1 >= 0) {
        int x = ts->arr[ts->top1];
        ts->top1--;
        return x;
    }
    printf("Stack Underflow stiva 1\n");
    return -1;
}

int pop2(TwoStacks* ts) {
    if (ts->top2 < ts->size) {
        int x = ts->arr[ts->top2];
        ts->top2++;
        return x;
    }
    printf("Stack Underflow stiva 2\n");
    return -1;
}