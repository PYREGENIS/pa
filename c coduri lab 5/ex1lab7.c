#include <stdio.h>
#include <stdbool.h>

#define V 5

// Funcție recursivă pentru DFS
void DFS(int graf[V][V], int nod, bool vizitat[V]) {
    vizitat[nod] = true;
    printf("%d ", nod);

    for (int i = 0; i < V; i++) {
        if (graf[nod][i] == 1 && !vizitat[i]) {
            DFS(graf, i, vizitat);
        }
    }
}

// Funcție pentru BFS folosind o coadă
void BFS(int graf[V][V], int start) {
    bool vizitat[V] = {false};
    int coada[V], front = 0, rear = 0;

    vizitat[start] = true;
    coada[rear++] = start;

    while (front < rear) {
        int nod = coada[front++];
        printf("%d ", nod);

        for (int i = 0; i < V; i++) {
            if (graf[nod][i] == 1 && !vizitat[i]) {
                vizitat[i] = true;
                coada[rear++] = i;
            }
        }
    }
}

int main() {
    int graf[V][V] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0}
    };

    bool vizitat[V] = {false};

    printf("Parcurgere DFS incepand de la nodul 0: ");
    DFS(graf, 0, vizitat);
    
    printf("\nParcurgere BFS incepand de la nodul 0: ");
    BFS(graf, 0);
    printf("\n");

    return 0;
}