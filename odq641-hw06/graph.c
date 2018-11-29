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
    int visited[MAXV+1];
    int parent[MAXV+1];
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
edgenodeT *copy_list(edgenodeT *);
void print_path(graphT *g, int start, int end);

void delete_edge(graphT *g, int x, int y);
void print_degree(graphT *g);
void print_complement(graphT *g);
void eliminate_links(graphT *g, int minW, int maxW);
void different_links(graphT *g1, graphT *g2);
void common_links(graphT *g1, graphT *g2);
void dfs_print(graphT *g, int start);
void dfs(graphT *g, int v, bool VERBOSE);
void bfs_print(graphT *g, int start);
void bfs(graphT *g, int start, bool verbose);
void is_connected(graphT *g);
void num_of_conn_comp(graphT *g);
int conn_comp_helper(graphT *g, int v);

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
            if (g1 && !g1->directed)
                insert_edge(g1, i_arg2, i_arg1, i_arg3); 
        } else if (equal(command, "delete")) {
            scanf("%s %d %d", s_arg1, &i_arg1, &i_arg2);
            g1 = which_graph(s_arg1, myg1, myg2);
            delete_edge(g1, i_arg1, i_arg2);
            if (g1 && !g1->directed)
                delete_edge(g1, i_arg2, i_arg1);
        } else if (equal(command, "printgraph")) {
            scanf("%s", s_arg1);
            g1 = which_graph(s_arg1, myg1, myg2);
            print_graph(g1, s_arg1);
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
            dfs_print(g1, i_arg1);
        } else if (equal(command, "bfs")) {
            scanf("%s %d", s_arg1, &i_arg1);
            g1 = which_graph(s_arg1, myg1, myg2);
            bfs_print(g1, i_arg1);
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
    edgenodeT *pe, *ep, *prep=NULL;
    pe = malloc(sizeof(edgenodeT));
    if (pe == NULL) {
        fprintf(stderr, "Not enough memory");
        exit(-1);
    }
    
    pe->weight = w;
    pe->y = y;

    for (ep=g->edges[x]; ep; ep=ep->next) {
        if (ep->y > pe->y)
            break;
        prep = ep;
    }
    if (prep)
        prep->next = pe;
    else
        g->edges[x] = pe;
    pe->next = ep;

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
        printf("\b \n");
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
    int i;
    graphT *newg;

    if (!g) return NULL;

    newg = (graphT *) malloc(sizeof(graphT));
    if (newg == NULL) {
        fprintf(stderr, "Not enough memory");
        exit(-1);
    }

    /* Fill newg with g values */ 
    newg->nvertices = g->nvertices;
    newg->nedges = g->nedges;
    newg->directed = g->directed;
    for (i=1; i<=newg->nedges; ++i)
        newg->edges[i] = copy_list(g->edges[i]);
    for (i=1; i<=newg->nvertices; ++i)
        newg->degree[i] = g->degree[i];

    return newg;
}

/* your other functions */
void help()
{
    printf("List of available commands: \n");
    printf("*  insert\t\t[myg1 | myg2] x y w\n");
    printf("*  delete\t\t[myg1 | myg2] x y\n");
    printf("*  printgraph\t\t[myg1 | myg2]\n");
    printf("*  printdegree\t\t[myg1 | myg2]\n");
    printf("*  printcomplement\t[myg1 | myg2]\n");
    printf("*  eliminatelinks\t[myg1 | myg2] minW maxW\n");
    printf("*  differentlinks\t[myg1 | myg2] [myg1 | myg2]\n");
    printf("*  commonlinks\t\t[myg1 | myg2] [myg1 | myg2]\n");
    printf("*  dfs\t\t\t[myg1 | myg2] x\n");
    printf("*  bfs\t\t\t[myg1 | myg2] x\n");
    printf("*  isconnected\t\t[myg1 | myg2]\n");
    printf("*  numofconncomp\t[myg1 | myg2]\n");
    printf("*  quit\n");
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

edgenodeT *copy_list(edgenodeT *list)
{
    edgenodeT *new, *start=NULL, *tail=NULL;

    /* For every node in list... */
    while (list) {
        /* Create copy of node */
        new = (edgenodeT *) malloc(sizeof(edgenodeT));
        new->y = list->y;
        new->weight = list->weight;
        new->next = NULL;

        /* Append copy to new list */
        if (tail)
            tail->next = new;
        else
            start = new;
        
        tail = new;
        list = list->next;
    }
    return start;
}

void print_path(graphT *g, int start, int end)
{
    int i;
    stackADT s;

    s = NewStack();
    for (i=end; i!=-1; i=g->parent[i])
        Push(s, i);
    while(!StackIsEmpty(s)) {
        printf(" %d ->", Pop(s)); 
    }
    printf("\b\b  \n");
    FreeStack(s);
}

void delete_edge(graphT *g, int x, int y)
{
    edgenodeT *ep, *prep=NULL;
    
    if (!g) return;

    /* For every edge from node x... */
    for (ep=g->edges[x]; ep; ep=ep->next) {
        /* if edge matches, delete it. NOTE: will not delete duplicates */
        if (ep->y == y) {
            if (prep)
                prep->next = ep->next;
            else
                g->edges[x] = ep->next;
            free(ep);
            return;
        } else
            prep = ep;
    }
}

void print_degree(graphT *g)
{
    int i;
    edgenodeT *ep;

    if (!g) return;
    int in_degree[g->nvertices+1];

    /* zero out in degree for accumulatiion later */
    for (i=1; i<=g->nvertices; ++i)
        in_degree[i] = 0;

    /* For each node in the graph... */
    for (i=1; i<=g->nvertices; ++i)
        for (ep=g->edges[i]; ep; ep=ep->next)
            ++in_degree[ep->y];
    
    /* Print degrees for each node */
    for (i=1; i<=g->nvertices; ++i) {
        if (g->directed)
            printf("Node %d:  in degree=%-3d out degree=%-3d\n", i, in_degree[i],
                   g->degree[i]);
        else
            printf("Node %d:  degree=%-3d\n", i, g->degree[i]);
    }
}

void print_complement(graphT *g)
{
    int i, j;
    edgenodeT *ep;
    graphT *gcomp;
    
    /* init complement to be g with no edges */
    gcomp = (graphT *) malloc(sizeof(graphT));
    initialize_graph(gcomp, g->directed);
    gcomp->nvertices = g->nvertices;

    /* For each pair of vertices, i and j,  determine if g has
     * an edge between them. If so, skip it. Otherwise,
     * insert that edge to gcomp */
    for (i=1; i<=g->nvertices; ++i) {
        ep = g->edges[i];
        for (j=1; j<=g->nvertices; ++j) {
            if (ep && j<ep->y) { /* edge DNE in g */
                insert_edge(gcomp, i, j, 1);
            } else if (ep && j==ep->y) { /* edge in g, move on */
                ep=ep->next;
            } else { /* no more edges to i in g, insert remaining j edges */
                insert_edge(gcomp, i, j, 1);
            }
        }
    }
    print_graph(gcomp, "complement");
    free_graph(gcomp);
}

/* MAKE AN EFFORT TO CLEAN THIS UP */
void eliminate_links(graphT *g, int minW, int maxW)
{
    int i;
    edgenodeT *tmp, *ep, *prep;

    if (!g) return;

    /* For each edge in g... */
    for (i=1; i<=g->nvertices; ++i) {
        prep=NULL;
        ep = g->edges[i];
        while(ep) {
            /* delete edge if necessary */
            if (ep->weight < minW || ep->weight > maxW) {
                if (prep)
                    prep->next = ep->next;
                else
                    g->edges[i] = ep->next;
                tmp = ep;
                ep = ep->next;
                free(tmp);
            } else {
                prep = ep;
                ep = ep->next;
            }
        }
    }
}

void different_links(graphT *g1, graphT *g2)
{
    int i, size;
    edgenodeT *ep1, *ep2;

    if (!g1 || !g2) return;
    
    size = (g1->nvertices > g2->nvertices? g1->nvertices
                                         : g2->nvertices);
    
    /* For each node, stopping at last node in larger graph... */
    for (i=1; i<=size; ++i) {
        ep1 = g1->edges[i];
        ep2 = g2->edges[i];
        /* Print out only different nodes, increment otherwise */
        while (ep1) {
            if (ep2 && ep1->y == ep2->y) { /* same, skip both */
                ep1 = ep1->next;
                ep2 = ep2->next;
            } else if (ep2 && ep1->y > ep2->y) { /* ep1->y might be in ep2 */
                ep2=ep2->next;
            } else {
                printf("%d -> %d\n", i, ep1->y);
                ep1=ep1->next;
            }
        }
    }
}

void common_links(graphT *g1, graphT *g2)
{
    int i, size;
    edgenodeT *ep1, *ep2;

    if (!g1 || !g2) return;
    
    size = (g1->nvertices < g2->nvertices? g1->nvertices
                                         : g2->nvertices);
    
    /* For each node, stopping at last node in smaller graph... */
    for (i=1; i<=size; ++i) {
        ep1 = g1->edges[i];
        ep2 = g2->edges[i];
        /* Print out only common nodes, increment otherwise */
        while (ep1 && ep2) {
            if (ep1->y < ep2->y) {
                ep1=ep1->next;
            } else if (ep1->y > ep2->y) {
                ep2=ep2->next;
            } else {
                printf("%d -> %d\n", i, ep1->y);
                ep1 = ep1->next;
                ep2 = ep2->next;
            }
        }
    }
    
}

void dfs_print(graphT *g, int start)
{
    int i;

    if (!g) return;

    /* init parent and visited */
    for (i=1; i<=g->nvertices; ++i) {
        g->visited[i] = FALSE;
        g->parent[i] = -1;
    }
    
    /* Do all the dfs business */
    g->visited[start] = TRUE;
    dfs(g, start, TRUE);
    printf("\n");

    /* Print paths to each node */
    for (i=1; i<=g->nvertices; ++i) {
        printf("Path to %d from %d:", i, start);
        print_path(g, start, i);
    }
}

void dfs(graphT *g, int v, bool VERBOSE)
{
    edgenodeT *ep;
    if (VERBOSE)
        printf("Node %d visited.\n", v);

    /* For each edge to v, dfs unvisited node */
    for (ep=g->edges[v]; ep; ep=ep->next) {
        if (g->visited[ep->y] == TRUE) continue;
        g->parent[ep->y] = v;
        g->visited[ep->y] = TRUE;
        dfs(g, ep->y, VERBOSE);
    }
}

void bfs_print(graphT *g, int start)
{
    int i;
        
    if (!g) return;

    /* init parent, visited */
    for (i=1; i<=g->nvertices; ++i) {
        g->visited[i] = FALSE;
        g->parent[i] = -1;
    }
   
    /* Do all the bfs business */
    bfs(g, start, TRUE);

    /* Print paths to each node */
    for (i=1; i<=g->nvertices; ++i) {
        printf("Path to %d from %d:", i, start);
        print_path(g, start, i);
    }
}

void bfs(graphT *g, int v, bool VERBOSE)
{
    queueADT q;
    edgenodeT *ep;
    
    if (!g) return;
    
    q = NewQueue();

    /* Prime loop */
    g->visited[v] = TRUE;
    if (VERBOSE)
        printf("Node %d visited.\n", v);
    Enqueue(q, &v);

    /* Main BFS loop */
    while(!QueueIsEmpty(q)) {
        v = *((int *) Dequeue(q));
        for (ep=g->edges[v]; ep; ep=ep->next) {
            if (g->visited[ep->y] == TRUE) continue;
            g->parent[ep->y] = v;
            g->visited[ep->y] = TRUE;
            if (VERBOSE)
                printf("Node %d visited.\n", ep->y);
            Enqueue(q, &ep->y);
        }
    }
    FreeQueue(q);
}

void is_connected(graphT *g)
{
    int i;
    
    if (!g) return;

    /* Don't do this for directed graphs */
    if (g->directed) {
        printf("We do not provide this functionality for directed graphs.\n");
        printf("Purchase the next version of this program :)\n");
        return;
    }
        

    /* init visited */
    for (i=1; i<=g->nvertices; ++i)
        g->visited[i] = FALSE;

    bfs(g, 1, FALSE);

    for (i=1; i<=g->nvertices; ++i)
        if (g->visited[i] == FALSE) {
            printf("NOT CONNECTED\n");
            return;
        }
    printf("CONNECTED");
}

void num_of_conn_comp(graphT *g)
{
    int i, count;

    if (!g) return;

    /* Don't do this for directed graphs */
    if (g->directed) {
        printf("We do not provide this functionality for directed graphs.\n");
        printf("Purchase the next version of this program :)\n");
        return;
    }

    /* init visited */
    for (i=1; i<=g->nvertices; ++i)
        g->visited[i] = 0;

    /* bfs and check for unvisited vertices, bfs again and
     * increment count if a vertex was not visited */
    count = 0;
    for (i=1; i<=g->nvertices; ++i) {
        if (g->visited[i] == FALSE) {
            ++count;
            bfs(g, i, FALSE);
        }
    }
    printf("%d components.\n", count);
}

