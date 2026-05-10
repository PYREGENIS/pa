#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 15
#define INF 999999

// Funcție pentru a afișa drumul și muchiile din arbore
void printPath(int parent[], int j, int graph[V][V]) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j], graph);
    printf(" -> %d (cost: %d)", j, graph[parent[j]][j]);
}

// Funcție pentru a găsi nodul cu distanța minimă (pentru Dijkstra)
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// ---------------- ALGORITMUL DIJKSTRA ----------------
void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    int visited[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1; // Marcam nodul ca vizitat (finalizat)

        for (int v = 0; v < V; v++) {
            // Dijkstra ignoră nodurile deja vizitate, o problemă majoră la costuri negative
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\n--- Rezultat DIJKSTRA (Sursa: %d, Destinatia: %d) ---\n", src, dest);
    printf("Cost total: %d\n", dist[dest]);
    printf("Ordinea nodurilor si valoarea muchiilor:\n");
    printPath(parent, dest, graph);
    printf("\n");
}

// ---------------- ALGORITMUL BELLMAN-FORD ----------------
void bellmanFord(int graph[V][V], int src, int dest) {
    int dist[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Relaxarea muchiilor de V-1 ori
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != INF && dist[u] != INF 
                    && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Verificare cicluri negative (optional pentru problema noastra, dar o buna practica)
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                printf("Graful contine un ciclu de cost negativ!\n");
                return;
            }
        }
    }

    printf("\n--- Rezultat BELLMAN-FORD (Sursa: %d, Destinatia: %d) ---\n", src, dest);
    printf("Cost total: %d\n", dist[dest]);
    printf("Ordinea nodurilor si valoarea muchiilor:\n");
    printPath(parent, dest, graph);
    printf("\n");
}

int main() {
    int graph[V][V];

    // Initializare matrice cu infinit
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = INF;

    // Adaugare muchii conform schemei
    graph[0][1] = 3;
    graph[0][2] = 5;
    graph[2][1] = -4; // Muchia cu cost negativ
    graph[0][4] = 10;
    graph[1][3] = 2;
    graph[3][4] = 4;
    graph[4][5] = 1;
    graph[2][5] = 8;
    graph[5][6] = 2;
    graph[6][7] = 3;
    graph[7][8] = 1;
    graph[5][8] = 6;
    graph[8][9] = 2;
    graph[9][10] = 1;
    graph[10][11] = 2;
    graph[11][12] = 3;
    graph[12][13] = 1;
    graph[13][14] = 2;

    int sursa = 0;
    int destinatie = 14;

    dijkstra(graph, sursa, destinatie);
    bellmanFord(graph, sursa, destinatie);

    return 0;
}