#include <stdio.h>
#include <stdbool.h>

#define V 4

bool areCicluUtil(int graf[V][V], int nod, int parinte, bool vizitat[V]) {
    vizitat[nod] = true;

    for (int i = 0; i < V; i++) {
        if (graf[nod][i] == 1) {
            if (!vizitat[i]) {
                if (areCicluUtil(graf, i, nod, vizitat)) {
                    return true;
                }
            } else if (i != parinte) {
                // Nod vizitat și nu e părintele celui curent -> am găsit un ciclu
                return true;
            }
        }
    }
    return false;
}

bool areCiclu(int graf[V][V]) {
    bool vizitat[V] = {false};
    
    // Verificăm pentru toate componentele conexe
    for (int i = 0; i < V; i++) {
        if (!vizitat[i]) {
            if (areCicluUtil(graf, i, -1, vizitat)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int grafCuCiclu[V][V] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    if (areCiclu(grafCuCiclu)) {
        printf("Graful contine cel putin un ciclu.\n");
    } else {
        printf("Graful nu contine cicluri.\n");
    }

    return 0;
}