#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int graph[V][V];
    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    int key[V], parent[V];
    bool mstSet[V];

  
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
       
        int min = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

      
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edges in MST:\n");
    int cost = 0;
    for (int i = 1; i < V; i++) {
        printf("%d - %d (weight %d)\n", parent[i], i, graph[i][parent[i]]);
        cost += graph[i][parent[i]];
    }
    printf("Total cost: %d\n", cost);

    return 0;
}
