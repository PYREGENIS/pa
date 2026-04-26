#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define DECK_SIZE 52
#define MAX_ROUNDS 10000 // Limită pentru a evita bucle infinite

// Coadă pentru pachetul fiecărui jucător
typedef struct {
    int cards[1000]; // Buffer mare
    int front, rear, size;
} CardQueue;

void initCQ(CardQueue* q) {
    q->front = 0; q->rear = -1; q->size = 0;
}
void enqueueCQ(CardQueue* q, int card) {
    q->rear = (q->rear + 1) % 1000;
    q->cards[q->rear] = card;
    q->size++;
}
int dequeueCQ(CardQueue* q) {
    int card = q->cards[q->front];
    q->front = (q->front + 1) % 1000;
    q->size--;
    return card;
}
bool isEmptyCQ(CardQueue* q) { return q->size == 0; }

void amesteca(int* deck, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void joacaRazboi() {
    int pachet[DECK_SIZE];
    int index = 0;
    
    // Generăm pachetul
    for (int valoare = 2; valoare <= 14; valoare++) {
        for (int i = 0; i < 4; i++) {
            pachet[index++] = valoare;
        }
    }

    srand(time(NULL)); // Inițializare random
    amesteca(pachet, DECK_SIZE);

    CardQueue jucator1, jucator2;
    initCQ(&jucator1);
    initCQ(&jucator2);

    // Împărțim cărțile
    for (int i = 0; i < 26; i++) enqueueCQ(&jucator1, pachet[i]);
    for (int i = 26; i < 52; i++) enqueueCQ(&jucator2, pachet[i]);

    int runde = 0;

    while (!isEmptyCQ(&jucator1) && !isEmptyCQ(&jucator2) && runde < MAX_ROUNDS) {
        runde++;
        int carte1 = dequeueCQ(&jucator1);
        int carte2 = dequeueCQ(&jucator2);

        if (carte1 > carte2) {
            enqueueCQ(&jucator1, carte1);
            enqueueCQ(&jucator1, carte2);
        } else if (carte2 > carte1) {
            enqueueCQ(&jucator2, carte2);
            enqueueCQ(&jucator2, carte1);
        }
        // La egalitate, cărțile se pierd (pentru a simplifica implementarea de bază)
    }

    printf("Numar de runde jucate: %d\n", runde);
    if (isEmptyCQ(&jucator1) && isEmptyCQ(&jucator2)) {
        printf("Egalitate! Ambii au ramas fara carti.\n");
    } else if (isEmptyCQ(&jucator1)) {
        printf("Castigator: Jucatorul 2\n");
    } else {
        printf("Castigator: Jucatorul 1\n");
    }
}