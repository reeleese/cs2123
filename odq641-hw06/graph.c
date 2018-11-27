#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

#define MAXV 100
typedef struct edgenode {
    int y;
    int weight;
    struct edgenode *next;
} edgenodeT;

typedef struct {
    edgenodeT *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
} graphT;


void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g, char *filename);
void insert_edge(graphT *g, int x, int y, int w);
void print_graph(graphT *g, char *name);
void free_graph(graphT *g);
graphT *copy_graph(graphT *g);
/* put prototypes for other functions here.... */


int main(int argc, char *argv[]) 
{
    graphT *myg1=NULL, *myg2=NULL;
    if(argc < 2){
        fprintf(stderr, "Usage: %s graph_filename", argv[0]);
        exit(-1);
    }
    myg1 = (graphT *) malloc(sizeof(graphT));
    if (myg1==NULL) {
        fprintf(stderr, "Cannot allocate memory for the graph");
        exit(-1);
    }
    initialize_graph(myg1, FALSE);
    read_graph(myg1, argv[1]);
    print_graph(myg1, "myg1");
    /* first implement copy_graph function and call it here */
    myg2 = copy_graph(myg1); 
    print_graph(myg2, "myg2");
    /* NOW in a loopget commands and call related functions to perform them... */
    free_graph(myg1);
}
void initialize_graph(graphT *g, bool directed)
{
    int i;
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;
    for (i=1; i<=MAXV; i++) 
	g->edges[i] = NULL;
    for (i=1; i<=MAXV; i++) 
	g->degree[i] = 0;
}

void read_graph(graphT *g, char *filename)
{
    int i;
    int n, m, dir;
    int x, y, w;
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL){
	fprintf(stderr, "Cannot open the graph file");
	exit(-1);
    }
    fscanf(fp,"%d %d %d", &n, &m, &dir);
    g->nvertices = n; 
    g->nedges  = 0; /* insert function will increase it */
    g->directed  = dir;
    for (i=1; i<=m; i++) {
	fscanf(fp,"%d %d %d", &x, &y, &w);
	insert_edge(g, x, y, w);
	if(dir==FALSE) 
	    insert_edge(g, y, x, w);
    }
    fclose(fp);
}

void insert_edge(graphT *g, int x, int y, int w)
{
    edgenodeT *pe;
    pe = malloc(sizeof(edgenodeT));
    /* check if NULL */
    pe->weight = w;
    pe->y = y;
    /* YOU MUST MODIFY THIS FUNCTION SO IT WILL KEEP LINK LIST SORTED W.R.T. NEIGHBOR IDs. */
    pe->next = g->edges[x];   
    g->edges[x] = pe;
    g->degree[x]++;
    g->nedges++;
}

void print_graph(graphT *g, char *name)
{
    edgenodeT *pe;
    int i;
    if(!g) return;
    printf("Graph Name: %s\n", name);
    for(i=1; i<=g->nvertices; i++) {
	printf("Node %d: ", i);
	pe = g->edges[i];
	while(pe){
	    /* printf(" %d", pe-n>y); */
	    printf(" %d(w=%d),", pe->y, pe->weight);
	    pe = pe->next;
	}
	printf("\n");
    }
}

void free_graph(graphT *g)
{
    edgenodeT *pe, *olde;
    int i;
    for(i=1; i<=g->nvertices; i++) {
	pe = g->edges[i];
	while(pe){
	    olde = pe;
	    pe = pe->next; 
	    free(olde);
	}
    }
    free(g);
}

graphT *copy_graph(graphT *g)
{
    graphT *newg;
    /* I simply return the same graph as a copy
     * but you really need to dynamically create 
     * another copy of the given graph */
    newg = g;
    return newg;
}
/* your other functions */
