#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX 100

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;


Node* newNode(int v, int w) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->vertex = v;
    temp->weight = w;
    temp->next = NULL;
    return temp;
}


void addEdge(Node* adj[], int u, int v, int w) {
    Node* n1 = newNode(v, w);
    n1->next = adj[u];
    adj[u] = n1;

    Node* n2 = newNode(u, w);
    n2->next = adj[v];
    adj[v] = n2;
}


int extractMin(int dist[], int visited[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void dijkstra(Node* adj[], int V, int src) {
    int dist[MAX];
    int visited[MAX] = {0};

 
    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[src] = 0;

   
    for (int count = 0; count < V - 1; count++) {
        int u = extractMin(dist, visited, V);
        if (u == -1) break; 
        visited[u] = 1;

        
        Node* p = adj[u];
        while (p != NULL) {
            int v = p->vertex;
            int weight = p->weight;
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
            p = p->next;
        }
    }

   
    printf("\nVertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}


int main() {
    int V = 5;
    Node* adj[MAX] = {NULL};

    int edges[][3] = {
        {0, 1, 9},
        {0, 2, 6},
        {0, 3, 5},
        {0, 4, 3},
        {2, 1, 2},
        {2, 3, 4}
    };

    int E = sizeof(edges) / sizeof(edges[0]);
    for (int i = 0; i < E; i++)
        addEdge(adj, edges[i][0], edges[i][1], edges[i][2]);

    dijkstra(adj, V, 0);
    return 0;
}
