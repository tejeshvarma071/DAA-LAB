#include <stdio.h>
#include <stdlib.h>


typedef struct Edge {
    int src, dest, weight;
} Edge;


typedef struct Graph {
    int V, E;
    Edge* edges;
} Graph;


typedef struct Subset {
    int parent;
    int rank;
} Subset;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V]; 
    int e = 0; 
    int i = 0;

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("Edges in the MST:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost of MST: %d\n", minimumCost);

    free(subsets);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V, E);

    printf("Enter edges in the format: source destination weight\n");
    printf("Vertices should be numbered from 0 to %d\n", V - 1);
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i+1);
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    KruskalMST(graph);

    free(graph->edges);
    free(graph);

    return 0;
}
