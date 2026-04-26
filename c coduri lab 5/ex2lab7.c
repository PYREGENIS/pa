#include <stdio.h>
#include <stdbool.h>

#define V 5

bool existaDrumUtil(int graf[V][V], int curent, int destinatie, bool vizitat[V]) {
    if (curent == destinatie) return true;
    
    vizitat[curent] = true;
    
    for (int i = 0; i < V; i++) {
        // Verificăm direcția de la "curent" la "i"
        if (graf[curent][i] == 1 && !vizitat[i]) {
            if (existaDrumUtil(graf, i, destinatie, vizitat)) {
                return true;
            }
        }
    }
    return false;
}

bool existaDrum(int graf[V][V], int start, int destinatie) {
    bool vizitat[V] = {false};
    return existaDrumUtil(graf, start, destinatie, vizitat);
}

int main() {
    int grafOrientat[V][V] = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0}
    };

    int start = 0, destinatie = 4;
    if (existaDrum(grafOrientat, start, destinatie)) {
        printf("Exista un drum intre nodul %d si nodul %d.\n", start, destinatie);
    } else {
        printf("Nu exista drum intre nodurile specificate.\n");
    }

    return 0;
}