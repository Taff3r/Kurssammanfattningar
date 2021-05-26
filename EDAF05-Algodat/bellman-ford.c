#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#define NUM_VERTICES (4)
#define NUM_EDGES (5)

typedef struct node_t node_t;
typedef struct edge_t edge_t;

struct edge_t {
    int u;
    int v; 
    int cost;
};
struct node_t {
    char letter;
    edge_t* edges;
    size_t num_edges;
    node_t* pred;
    int d;
};

void make_table(node_t* G, edge_t* E, node_t* s)
{
    int n;
    int i;

    for (i = 0; i < NUM_VERTICES; ++i) {
        G[i].d = INT_MAX;
        G[i].pred = NULL;
    }
    
    s->d = 0;
    i = 1; 
    while (i++ <= NUM_VERTICES - 1) {
        for (int k = 0; k < NUM_EDGES; ++k) {
            edge_t e = E[k];
            node_t *v, *w;
            v = &G[e.u];
            w = &G[e.v];
            if (v->d + e.cost < w->d) {
               w->d = e.cost + v->d;
               w->pred = v; 
            }
        }
    }
}
void print_shortest(node_t s, node_t t)
{
    int total;
    total = t.d;
    printf("Total cost %d using path:\n", total);
    node_t* curr = &t;
    while(curr != NULL) {
        printf("%c -> ", curr->letter);
        curr = curr->pred;
    }
    printf("\n");
}
void print_graph(node_t* G)
{
    for (int i = 0; i < NUM_VERTICES; ++i) {
        node_t curr = G[i];
        printf("Node %c: has neigbors:\n", curr.letter);
        for (int n = 0; n < curr.num_edges; ++n) {
            node_t w = G[curr.edges[n].v];
            printf("\tNode %c with cost %d\n", w.letter, curr.edges[n].cost); 
        }
        printf("\n");
    }
}
int main(void)
{
    node_t* graph; 
    graph = malloc(NUM_VERTICES * sizeof(node_t));
    
    graph[0].letter = 's';  
    graph[1].letter = 'a';  
    graph[2].letter = 'b';  
    graph[3].letter = 't';  
    
    graph[0].edges = malloc(sizeof(edge_t) * 2);
    graph[1].edges = malloc(sizeof(edge_t) * 2);
    graph[2].edges = malloc(sizeof(edge_t) * 1);
    graph[3].edges = NULL; 

    graph[0].num_edges = 2;
    graph[1].num_edges = 2;
    graph[2].num_edges = 1;
    graph[3].num_edges = 0;
   
    edge_t edges[NUM_EDGES]; 

    edges[0] = (edge_t) {.u = 0, .v = 1, .cost = 4};
    edges[1] = (edge_t) {.u = 0, .v = 2, .cost = 3};
    edges[2] = (edge_t) {.u = 1, .v = 3, .cost = 1};
    edges[3] = (edge_t) {.u = 1, .v = 2, .cost = -2};
    edges[4] = (edge_t) {.u = 2, .v = 3, .cost = 1};

    graph[0].edges[0] = edges[0];
    graph[0].edges[1] = edges[1];

    graph[1].edges[0] = edges[2];
    graph[1].edges[1] = edges[3];

    graph[2].edges[0] = edges[4];
    print_graph(graph);
    make_table(graph, edges, &graph[0]);
    print_shortest(graph[0], graph[3]);
    for (int i = 0; i < NUM_VERTICES; ++i)
        free(graph[i].edges);

    free(graph);
}
