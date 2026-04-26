#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct dnode {
    int data;
    struct dnode *next, *prev;
};

void insertStart(struct node **head, int val) {
    struct node *nou = malloc(sizeof(struct node));
    nou->data = val;
    nou->next = *head;
    *head = nou;
}

void insertEnd(struct node **head, int val) {
    struct node *nou = malloc(sizeof(struct node));
    nou->data = val;
    nou->next = NULL;
    if (!*head) { *head = nou; return; }
    struct node *t = *head;
    while (t->next) t = t->next;
    t->next = nou;
}

void deleteNode(struct node **head, int val) {
    struct node *t = *head, *prev = NULL;
    if (t && t->data == val) { *head = t->next; free(t); return; }
    while (t && t->data != val) { prev = t; t = t->next; }
    if (t) { prev->next = t->next; free(t); }
}

void sort(struct node *h) {
    for (struct node *i = h; i; i = i->next)
        for (struct node *j = i->next; j; j = j->next)
            if (i->data > j->data) {
                int aux = i->data;
                i->data = j->data;
                j->data = aux;
            }
}

void reverseIterativ(struct node **head) {
    struct node *prev = NULL, *curr = *head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void removeDuplicates(struct node *h) {
    struct node *i, *j, *dup;
    for (i = h; i; i = i->next) {
        for (j = i; j->next; ) {
            if (i->data == j->next->data) {
                dup = j->next;
                j->next = j->next->next;
                free(dup);
            } else j = j->next;
        }
    }
}

int isPalindrome(struct node *h) {
    int v[100], n = 0;
    struct node *t = h;
    while (t) { v[n++] = t->data; t = t->next; }
    for (int i = 0; i < n/2; i++)
        if (v[i] != v[n-i-1]) return 0;
    return 1;
}

void findMinMaxCircular(struct dnode *head) {
    if (!head) return;
    int min = head->data, max = head->data;
    struct dnode *curr = head;
    do {
        if (curr->data < min) min = curr->data;
        if (curr->data > max) max = curr->data;
        curr = curr->next;
    } while (curr != head);
    printf("Min: %d, Max: %d\n", min, max);