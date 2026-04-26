#include <stdio.h>
#include <stdbool.h>

#define V 6

int distantaMinMax(int graf[V][V], int valori[V]) {
    int minVal = valori[0], maxVal = valori[0];
    
    // Aflăm valorile minime și maxime din graf
    for (int i = 1; i < V; i++) {
        if (valori[i] < minVal) minVal = valori[i];
        if (valori[i] > maxVal) maxVal = valori[i];
    }

    if (minVal == maxVal) return 0; // Distanța este 0 dacă min = max

    int distanta[V], coada[V], front = 0, rear = 0;
    
    // Inițializăm distanțele cu -1 (nevizitat)
    for (int i = 0; i < V; i++) {
        distanta[i] = -1;
    }

    // Adăugăm în coadă TOATE nodurile cu valoarea minimă
    for (int i = 0; i < V; i++) {
        if (valori[i] == minVal) {
            coada[rear++] = i;
            distanta[i] = 0;
        }
    }

    // Parcurgere BFS
    while (front < rear) {
        int curent = coada[front++];

        // Dacă am găsit o valoare maximă, returnăm distanța
        if (valori[curent] == maxVal) {
            return distanta[curent];
        }

        for (int i = 0; i < V; i++) {
            if (graf[curent][i] == 1 && distanta[i] == -1) {
                distanta[i] = distanta[curent] + 1;
                coada[rear++] = i;
            }
        }
    }

    return -1; // Returnează -1 dacă graful este neconex și nu există drum
}

int main() {
    int graf[V][V] = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 0}
    };

    // Nodurile 0 și 3 au valoarea minimă (10). Nodul 5 are valoarea maximă (90).
    int valoriNoduri[V] = {10, 20, 50, 10, 70, 90};

    int dist = distantaMinMax(graf, valoriNoduri);
    
    if (dist != -1) {
        printf("Cea mai mica distanta dintre un nod minim si unul maxim este: %d muchii.\n", dist);
    } else {
        printf("Nu exista drum intre nodul minim si cel maxim.\n");
    }

    return 0;
}