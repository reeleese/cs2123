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
void help();
int equal(char *s1, char *s2);
graphT *which_graph(char *g, graphT *myg1, graphT *myg2);

void delete_edge(graphT *g, int x, int y);
void print_degree(graphT *g);
void print_complement(graphT *g);
void eliminate_links(graphT *g, int minW, int maxW);
void different_links(graphT *g1, graphT *g2);
void common_links(graphT *g1, graphT *g2);
void dfs(graphT *g, int start);
void bfs(graphT *g, int start);
void is_connected(graphT *g);
void num_of_conn_comp(graphT *g);

int main(int argc, char *argv[]) 
{
    int done, i_arg1, i_arg2, i_arg3, c;
    char command [100], s_arg1[100], s_arg2[100];
    graphT *g1, *g2;

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
    
    /* Menu loop */
    done = 0;
    while (!done) {
        printf("Enter a command:\n>");
        scanf("%s", command);
        
        if (equal(command, "insert")) {
            scanf("%s %d %d %d", s_arg1, &i_arg1, &i_arg2, &i_arg3);
            g1 = which_graph(s_arg1, myg1, myg2);
	    insert_edge(g1, i_arg1, i_arg2, i_arg3);
	} else if (equal(command, "delete")) {
            scanf("%s %d %d", s_arg1, &i_arg1, &i_arg2);
            g1 = which_graph(s_arg1, myg1, myg2);
	    delete_edge(g1, i_arg1, i_arg2);
        } else if (equal(command, "printgraph")) {
            scanf("%s %s", s_arg1, s_arg2);
            g1 = which_graph(s_arg1, myg1, myg2);
	    print_graph(g1, s_arg2);
        } else if (equal(command, "printdegree")) {
            scanf("%s", s_arg1);
            g1 = which_graph(s_arg1, myg1, myg2);
	    print_degree(g1);
        } else if (equal(command, "printcomplement")) {
            scanf("%s", s_arg1);
            g1 = which_graph(s_arg1, myg1, myg2);
	    print_complement(g1);
        } else if (equal(command, "eliminatelinks")) {
            scanf("%s %d %d", s_arg1, &i_arg1, &i_arg2);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    eliminate_links(g1, i_arg1, i_arg2);	    
        } else if (equal(command, "differentlinks")) {
	    scanf("%s %s", s_arg1, s_arg2);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    g2 = which_graph(s_arg2, myg1, myg2);
	    different_links(g1, g2);
	} else if (equal(command, "commonlinks")) {
	    scanf("%s %s", s_arg1, s_arg2);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    g2 = which_graph(s_arg2, myg1, myg2);
	    common_links(g1, g2);
	} else if (equal(command, "dfs")) {
	    scanf("%s %d", s_arg1, &i_arg1);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    dfs(g1, i_arg1);
        } else if (equal(command, "bfs")) {
	    scanf("%s %d", s_arg1, &i_arg1);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    bfs(g1, i_arg1);
        } else if (equal(command, "isconnected")) {
	    scanf("%s", s_arg1);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    is_connected(myg1);
        } else if (equal(command, "numofconncomp")) {
	    scanf("%s", s_arg1);
	    g1 = which_graph(s_arg1, myg1, myg2);
	    num_of_conn_comp(g1);
        } else if (equal(command, "quit")) {
            done = 1;
	    printf("Bye bye.\n");
        } else if (equal(command, "help")) {
	    help();
        } else { /* Unrecognized command */
	    /* clear stdin */
	    while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Unrecognized command. ");
            printf("Type \"help\" for a list of commands.\n");
        }
	printf("\n");
    }

    free_graph(myg1);
    free_graph(myg2);
    return 0;
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
void help()
{

}

int equal(char *s1, char *s2)
{
    if (strcmp(s1, s2))
	return 0;
    return 1;
}

graphT *which_graph(char *g, graphT *myg1, graphT *myg2)
{
    if (equal(g, "myg1"))
	return myg1;
    else if (equal(g, "myg2"))
	return myg2;
    return NULL;
}

void delete_edge(graphT *g, int x, int y)
{

}

void print_degree(graphT *g)
{

}

void print_complement(graphT *g)
{

}

void eliminate_links(graphT *g, int minW, int maxW)
{

}

void different_links(graphT *g1, graphT *g2)
{

}

void common_links(graphT *g1, graphT *g2)
{

}

void dfs(graphT *g, int start)
{

}

void bfs(graphT *g, int start)
{

}

void is_connected(graphT *g)
{

}

void num_of_conn_comp(graphT *g)
{

}
