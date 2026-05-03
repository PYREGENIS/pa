#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EDGES 100
#define MAX_NODES 26 // Folosim literele A-Z ca indici 0-25
#define INF 999999

// Structura pentru o muchie
struct Edge {
    char src, dest;
    int weight;
};

// Functie de comparare pentru qsort (necesara la Kruskal)
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// ----------------- Functii Union-Find (Kruskal) -----------------
int find(int i, int parent[]) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i], parent);
}

void Union(int i, int j, int parent[], int rank[]) {
    int root_i = find(i, parent);
    int root_j = find(j, parent);

    if (rank[root_i] < rank[root_j]) {
        parent[root_i] = root_j;
    } else if (rank[root_i] > rank[root_j]) {
        parent[root_j] = root_i;
    } else {
        parent[root_j] = root_i;
        rank[root_i]++;
    }
}

// ----------------- Algoritmul Kruskal -----------------
void kruskal(struct Edge edges[], int num_edges, int num_nodes) {
    qsort(edges, num_edges, sizeof(struct Edge), compareEdges);

    int parent[MAX_NODES];
    int rank[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    FILE *fout = fopen("kruskal_output.csv", "w");
    fprintf(fout, "Algoritm,Kruskal\n");
    fprintf(fout, "Sursa,Destinatie,Cost\n");

    printf("\n--- Rulare Algoritm Kruskal ---\n");
    int cost_total = 0;
    int edges_added = 0;

    for (int i = 0; i < num_edges && edges_added < num_nodes - 1; i++) {
        int u = edges[i].src - 'A';
        int v = edges[i].dest - 'A';

        if (find(u, parent) != find(v, parent)) {
            printf("Muchie: %c - %c | Cost: %d\n", edges[i].src, edges[i].dest, edges[i].weight);
            fprintf(fout, "%c,%c,%d\n", edges[i].src, edges[i].dest, edges[i].weight);
            cost_total += edges[i].weight;
            Union(u, v, parent, rank);
            edges_added++;
        }
    }
    printf("Cost Total (Kruskal): %d\n", cost_total);
    fprintf(fout, "Cost Total,,%d\n", cost_total);
    fclose(fout);
}

// ----------------- Functie Ajutatoare pentru Prim -----------------
int minKey(int key[], bool mstSet[], bool nodes_present[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < MAX_NODES; v++) {
        if (nodes_present[v] && mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// ----------------- Algoritmul Prim -----------------
void prim(int graph[MAX_NODES][MAX_NODES], bool nodes_present[], int num_nodes) {
    int parent[MAX_NODES];
    int key[MAX_NODES];
    bool mstSet[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++) {
        key[i] = INF;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Gaseste primul nod prezent pentru a incepe
    int start_node = -1;
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes_present[i]) {
            start_node = i;
            break;
        }
    }

    key[start_node] = 0;

    for (int count = 0; count < num_nodes - 1; count++) {
        int u = minKey(key, mstSet, nodes_present);
        if (u == -1) break;
        mstSet[u] = true;

        for (int v = 0; v < MAX_NODES; v++) {
            if (graph[u][v] && nodes_present[v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    FILE *fout = fopen("prim_output.csv", "w");
    fprintf(fout, "Algoritm,Prim\n");
    fprintf(fout, "Sursa,Destinatie,Cost\n");

    printf("\n--- Rulare Algoritm Prim ---\n");
    int cost_total = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes_present[i] && parent[i] != -1) {
            printf("Muchie: %c - %c | Cost: %d\n", parent[i] + 'A', i + 'A', graph[i][parent[i]]);
            fprintf(fout, "%c,%c,%d\n", parent[i] + 'A', i + 'A', graph[i][parent[i]]);
            cost_total += graph[i][parent[i]];
        }
    }
    printf("Cost Total (Prim): %d\n", cost_total);
    fprintf(fout, "Cost Total,,%d\n", cost_total);
    fclose(fout);
}

// ----------------- Executia Principala -----------------
int main() {
    FILE *file = fopen("graf_intrare.csv", "r");
    if (!file) {
        printf("Eroare: Nu s-a putut deschide graf_intrare.csv\n");
        return 1;
    }

    struct Edge edges[MAX_EDGES];
    int num_edges = 0;
    bool nodes_present[MAX_NODES] = {false};
    int graph[MAX_NODES][MAX_NODES] = {0};

    char line[256];
    fgets(line, sizeof(line), file); // Sarim peste antetul CSV

    while (fgets(line, sizeof(line), file)) {
        char u, v;
        int w;
        if (sscanf(line, "%c,%c,%d", &u, &v, &w) == 3) {
            edges[num_edges].src = u;
            edges[num_edges].dest = v;
            edges[num_edges].weight = w;
            num_edges++;

            nodes_present[u - 'A'] = true;
            nodes_present[v - 'A'] = true;

            // Populam matricea de adiacenta pentru Prim (graf neorientat)
            graph[u - 'A'][v - 'A'] = w;
            graph[v - 'A'][u - 'A'] = w;
        }
    }
    fclose(file);

    int num_nodes = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes_present[i]) num_nodes++;
    }

    printf("Citire finalizata: %d noduri si %d muchii gasite.\n", num_nodes, num_edges);

    // Rulam algoritmii
    kruskal(edges, num_edges, num_nodes);
    prim(graph, nodes_present, num_nodes);

    printf("\nFisierele 'kruskal_output.csv' si 'prim_output.csv' au fost generate cu succes!\n");

    return 0;
}