#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 100

typedef struct {
    char* names[MAX_PLAYERS];
    int front, rear, size;
} StringQueue;

void initQ(StringQueue* q) {
    q->front = 0; q->rear = -1; q->size = 0;
}

void enqueueStr(StringQueue* q, char* name) {
    q->rear = (q->rear + 1) % MAX_PLAYERS;
    q->names[q->rear] = name;
    q->size++;
}

char* dequeueStr(StringQueue* q) {
    char* name = q->names[q->front];
    q->front = (q->front + 1) % MAX_PLAYERS;
    q->size--;
    return name;
}

void hotPotato(char* players[], int n) {
    StringQueue q;
    initQ(&q);
    
    // Adăugăm jucătorii în coadă
    for (int i = 0; i < n; i++) {
        enqueueStr(&q, players[i]);
    }

    char* eliminations[MAX_PLAYERS];
    int top = -1; // Pentru stiva de eliminări

    while (q.size > 1) {
        int random_num = rand() % 7 + 1; // 1-7 pase
        
        for (int i = 0; i < random_num; i++) {
            enqueueStr(&q, dequeueStr(&q)); // Trecem cartoful mai departe
        }
        
        eliminations[++top] = dequeueStr(&q); // Eliminăm și adăugăm în stivă
    }
    
    eliminations[++top] = dequeueStr(&q); // Adăugăm și câștigătorul

    printf("Jucatorii (de la ultimul ramas la primul iesit):\n");
    while (top >= 0) {
        printf("%s ", eliminations[top--]);
    }
    printf("\n");
}