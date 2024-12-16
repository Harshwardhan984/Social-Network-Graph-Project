// Graph using adt LIsts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "Project.h"

char users[MAX_NODE + 1][50];

// Here , we are analysing graph according to social network , hence dist. of an edge is always = 1

// These are the users of the social network
/*
char users[12][12] = {
    "", "Raj", "Amit", "Yash", "Om",
    "Suraj", "Nilesh", "Prakash",
    "Ankit", "Amol", "Mayank"
};

*/

void initUsers() {
    for (int i = 0; i <= MAX_NODE; i++) {
        users[i][0] = '\0'; // Set each string as empty
    }
}

void loadName(const char* file){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[100];
    int i = 1;
    while (fgets(buffer, sizeof(buffer), fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        strcpy(users[i], buffer);
        i++;
        if (i > MAX_NODE) {
            printf("Maximum user limit reached.\n");
            break;
        }
    }
    fclose(fptr);
    printf("%d names loaded successfully.\n", i - 1);
}

// Function to find the index of a name in the users array
int findUserIndex(const char *name) {
    for (int i = 0; i < MAX_NODE; i++) {
        if (strcmp(users[i], name) == 0) {
            return i;
        }
    }
    return -1; // User not found
}

// stack

void initStack(Stack *stack, int size)
{
    stack->top = -1;
    stack->size = size;
    stack->items = (int *)malloc(sizeof(int) * size);
}

bool isEmptys(Stack *stack)
{
    return stack->top == -1;
}

bool isFulls(Stack *stack)
{
    return stack->top == stack->size - 1;
}

void push(Stack *stack, int item)
{
    if (isFulls(stack))
    {
        // printf("Stack is full\n");
        return;
    }
    stack->items[++(stack->top)] = item;
}

int pop(Stack *stack)
{
    if (isEmptys(stack))
    {
        // printf("Stack is empty\n");
        return -1;
    }
    return stack->items[(stack->top)--];
}

int peek(Stack *stack)
{
    if (isEmptys(stack))
    {
        // printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top];
}

// queue

// Initialize the queue with a given size
void initQueue(Queue *queue, int size)
{
    queue->size = size;
    queue->items = (int *)malloc(sizeof(int) * size);
    queue->front = -1;
    queue->rear = -1;
}

// Check if the queue is empty
bool isEmptyq(Queue *queue)
{
    return queue->front == -1;
}

// Check if the queue is full
bool isFullq(Queue *queue)
{
    return (queue->rear + 1) % queue->size == queue->front;
}

// Add an element to the queue (enqueue)
void enqueue(Queue *queue, int item)
{
    if (isFullq(queue))
    {
        // printf("Queue is full\n");
        return;
    }

    if (isEmptyq(queue))
    {
        queue->front = 0; // Set front to 0 if the queue is empty
    }

    queue->rear = (queue->rear + 1) % queue->size; // Circular increment of rear
    queue->items[queue->rear] = item;
}

// Remove an element from the queue (dequeue)
int dequeue(Queue *queue)
{
    if (isEmptyq(queue))
    {
        // printf("Queue is empty\n");
        return -1;
    }

    int item = queue->items[queue->front];
    if (queue->front == queue->rear)
    {
        // Queue is now empty, reset front and rear
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % queue->size; // Circular increment of front
    }

    return item;
}

void initGraph(GraphList *g, int vertx)
{
    g->numVertices = vertx;
    g->arrOfLists = (Node **)malloc(sizeof(Node *) * g->numVertices);
    int i;
    for (i = 0; i < g->numVertices; i++)
    {
        g->arrOfLists[i] = NULL;
    }
    return;
}

Node *createnodeWT(int index, int wt)
{
    Node *nn = (Node *)malloc(sizeof(Node));
    nn->ver = index;
    nn->wt = wt;
    nn->next = NULL;
    return nn;
}

void addvertexwithWT(GraphList *g, int scr, int dess, int wt, int cm[MAX_NODE][MAX_NODE])
{
    Node *forscr = createnodeWT(dess, wt);
    forscr->next = g->arrOfLists[scr - 1];
    g->arrOfLists[scr - 1] = forscr;
    cm[scr][dess] = 1;

    Node *fordess = createnodeWT(scr, wt);
    fordess->next = g->arrOfLists[dess - 1];
    g->arrOfLists[dess - 1] = fordess;
    cm[dess][scr] = 1;

    return;
}

void addConnection(const char *name1, const char *name2, GraphList *g, int cm[MAX_NODE][MAX_NODE]){
    int index1 = findUserIndex(name1);
    int index2 = findUserIndex(name2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both users not found in the file.\n");
        return;
    }
	if(cm[index1][index2] == 1){
	printf("Connection already exists between %s and %s.\n", name1, name2);
	return;
	}
	
    addvertexwithWT(g, index1, index2, 1, cm);
    return;
}

void deletnode(Node **headAD, int d)
{
    if (*headAD == NULL)
        return;
    Node *head = *(headAD);
    if (head->ver == d)
    {
        // printf("in con\n");
        Node *tem = *(headAD);
        *(headAD) = tem->next;
        free(tem);
        return;
    }
    else
    {
        Node *p = *(headAD);
        Node *q = p->next;
        while (q && q->ver != d)
        {
            p = p->next;
            q = q->next;
        }
        p->next = q->next;
        free(q);
        return;
    }
}

void removeVertex(GraphList *g, int scr, int dess, int cm[MAX_NODE][MAX_NODE])
{
    // remove from scr

    deletnode(&(g->arrOfLists[scr - 1]), dess);
    cm[scr][dess] = 0;

    // remove from dess

    deletnode(&(g->arrOfLists[dess - 1]), scr);
    cm[dess][scr] = 1;

    printf("The edge from %s to %s removed successfully\n\n", users[scr], users[dess]);
    return;
}

void freeGraph(GraphList *g)
{
    int i;
    for (i = 0; i < g->numVertices; i++)
    {
        Node *p = g->arrOfLists[i];
        while (p)
        {
            Node *tem = p->next;
            free(p);
            p = tem;
        }
        g->arrOfLists[i] = NULL; // Set each list pointer to NULL
    }

    free(g->arrOfLists);  // Free the array of adjacency lists
    g->arrOfLists = NULL; // Set the pointer to NULL
    g->numVertices = 0;      // Reset the vertex count

    return;
}

void BFS(GraphList g, int ver)
{
    Queue q;
    initQueue(&q, g.numVertices);

    int *visited = (int *)calloc(g.numVertices, sizeof(int)); // set all to zero

    int *bfs = (int *)malloc(sizeof(int) * g.numVertices);
    int sbfs = 0;

    int n = ver;

    enqueue(&q, n);
    visited[ver - 1] = 1;
    bfs[sbfs] = n;
    sbfs++;

    while (!isEmptyq(&q))
    {
        int n = dequeue(&q);
        Node *p = g.arrOfLists[n - 1]; // Access adjacency list for vertex `n`

        while (p != NULL)
        {
            if (!visited[p->ver - 1])
            {
                enqueue(&q, p->ver);
                visited[p->ver - 1] = 1; // Mark the node as visited
                bfs[sbfs++] = p->ver;    // Add to BFS result
            }
            p = p->next;
        }
    }

    // Print BFS result
    printf("The BFS traversal for the given graph starting from %s will be : \n",users[bfs[0]]);
    for (int i = 0; i < sbfs; i++)
    {
        printf("%s", users[bfs[i]]);
        if (i < sbfs - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n\n");

    free(visited);
    free(bfs);
    return;
}

void DFS(GraphList g, int ver)
{
    Stack s;
    initStack(&s, g.numVertices);
    int *visited = (int *)calloc(g.numVertices + 1, sizeof(int)); // set all to zero

    int *dfs = (int *)malloc(sizeof(int) * g.numVertices);
    int sdfs = 0;

    int n = ver;

    push(&s, n);
    visited[n] = 1;

    while (!isEmptys(&s))
    {
        n = pop(&s);
        dfs[sdfs] = n;
        sdfs++;

        Node *p = g.arrOfLists[n - 1];
        while (p != NULL)
        {
            if (!visited[p->ver])
            {
                push(&s, p->ver);    // Push unvisited neighbor onto stack
                visited[p->ver] = 1; // Mark it as visited
            }
            p = p->next;
        }
    }

    // Print DFS result
    printf("The DFS traversal for the given graph starting from %s will be : \n",users[dfs[0]]);
    for (int i = 0; i < sdfs; i++)
    {
        printf("%s", users[dfs[i]]);
        if (i < sdfs - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n\n");

    free(visited);
    free(dfs);
    return;
}

int Checkifcircular(GraphList g, int ver)
{
    Stack s;
    initStack(&s, g.numVertices);
    int *visited = (int *)calloc(g.numVertices + 1, sizeof(int)); // set all to zero
    int *parent = (int *)calloc(g.numVertices + 1, sizeof(int));

    push(&s, ver);
    visited[ver] = 1;
    parent[ver] = -1; // Root node has no parent

    while (!isEmptys(&s))
    {
        int current = pop(&s);
        Node *adj = g.arrOfLists[current - 1];

        while (adj != NULL)
        {
            int neighbor = adj->ver;
            if (!visited[neighbor])
            {
                push(&s, neighbor);
                visited[neighbor] = 1;
                parent[neighbor] = current; // Set parent
            }
            else if (parent[current] != neighbor)
            {
                // Cycle detected if revisiting node that's not parent
                free(visited);
                free(parent);

                return 1;
            }
            adj = adj->next;
        }
    }

    free(visited);
    free(parent);

    return 0;
}

/*
A Minimum Spanning Tree (MST) is a subset of edges in a weighted, connected, undirected graph that connects all the vertices with the minimum total edge weight, without forming any cycles.

Key Properties of MST
Spanning Tree:

A spanning tree of a graph connects all vertices with exactly

V−1 edges (where

V is the number of vertices).
It does not contain any cycles.
Minimum Total Weight:

Among all possible spanning trees, the MST has the smallest possible sum of edge weights.
Unique or Multiple MSTs:

If all edge weights are distinct, the MST is unique.
If there are multiple edges with the same weight, there can be more than one valid MST.

*/

void prims(GraphList g, int ver)
{
    printf("The minimum spanning graph starting from %s will be : \n",users[ver]);

    int totalver = g.numVertices;
    int start = ver - 1;
    int *vis = (int *)calloc(totalver, sizeof(int));

    int minwt = INT_MAX, u = start, v;

    int *MST[2];

    MST[0] = (int *)calloc(totalver - 1, sizeof(int));
    MST[1] = (int *)calloc(totalver - 1, sizeof(int));

    Node *q = g.arrOfLists[u];
    while (q)
    {
        if (q->wt < minwt)
        {
            minwt = q->wt;
            v = q->ver - 1;
        }
        q = q->next;
    }
    MST[0][0] = u;
    MST[1][0] = v;
    vis[u] = 1;
    vis[v] = 1;

    int i;
    for (i = 1; i < totalver - 1; i++)
    {
        minwt = INT_MAX;
        for (int j = 0; j < totalver; j++)
        {
            if (vis[j] == 1)
            {
                Node *p = g.arrOfLists[j];
                while (p)
                {
                    if (vis[p->ver - 1] != 1 && p->wt < minwt)
                    {
                        minwt = p->wt;
                        u = j;
                        v = p->ver - 1;
                    }
                    p = p->next;
                }
            }
        }
        MST[0][i] = u;
        MST[1][i] = v;
        vis[v] = 1;
    }

    for (int i = 0; i < totalver - 1; i++)
        printf("%s -> %s\n", users[MST[0][i] + 1], users[MST[1][i] + 1]);

    printf("\n");
    free(vis);
    free(MST[0]);
    free(MST[1]);
}

/*
Dijkstra's Algorithm (Short Explanation)
Purpose:
Finds the shortest path from a source node to all other nodes in a graph with non-negative weights.

Steps:

Initialize:

Set all distances to infinity (INF) except the source, which is 0.
Use a priority queue to store nodes by their distance.
Process:

Pick the closest unvisited node.
Update distances to its neighbors if a shorter path is found through it.
Mark the node as visited.

Repeat:
Continue until all nodes are visited or the queue is empty.

*/

int findminfromdis(int numVertices, int *vis, int *dis)
{
    int i, min = INT_MAX, v;
    for (i = 0; i < numVertices; i++)
    {
        if (vis[i] != 1 && dis[i] < min)
        {
            min = dis[i];
            v = i;
        }
    }
    return v;
}

void Dijkstras(GraphList g, int ver)
{
    int totalver = g.numVertices;
    int start = ver - 1;
    int *dis = (int *)malloc(sizeof(int) * totalver);
    int *vis = (int *)calloc(totalver, sizeof(int));

    for (int i = 0; i < totalver; i++)
    {
        dis[i] = INT_MAX;
    }

    dis[start] = 0;
    int donever = 0;
    while (donever < totalver - 1)
    {
        int mindisver = findminfromdis(totalver, vis, dis);
        Node *p = g.arrOfLists[mindisver];
        while (p)
        {
            if (vis[p->ver - 1] != 1 && dis[p->ver - 1] > dis[mindisver] + p->wt)
            {
                dis[p->ver - 1] = dis[mindisver] + p->wt;
            }
            p = p->next;
        }
        vis[mindisver] = 1;
        donever++;
    }

    printf("The shortest distance from %s is : \n", users[ver]);
    for (int i = 0; i < totalver; i++)
    {
        printf("%s -> %d\n", users[i + 1], dis[i]);
    }

    printf("\n");
    free(dis);
    free(vis);
}

void printlist(Node *p)
{
    Node *q = p;
    while (q)
    {
        printf("%s ", users[q->ver]);
        if (q->next != NULL)
            printf("-> ");
        q = q->next;
    }
    return;
}

void printgraph(GraphList g)
{
    int i;
    for (i = 0; i < g.numVertices; i++)
    {
        printf("%s ==> ", users[i + 1]);
        printlist(g.arrOfLists[i]);
        printf("\n");
    }
    printf("\n");
    return;
}

void PrintShortPath(GraphList g, int scr, int dess)
{
    int totalver = g.numVertices;
    int start = scr - 1;
    int *dis = (int *)malloc(sizeof(int) * totalver);
    int *vis = (int *)calloc(totalver, sizeof(int));

    int *parent = (int *)calloc(totalver + 1, sizeof(int));

    for (int i = 0; i < totalver; i++)
    {
        dis[i] = INT_MAX;
    }

    dis[start] = 0;
    int donever = 0;
    while (donever < totalver - 1)
    {
        int mindisver = findminfromdis(totalver, vis, dis);
        Node *p = g.arrOfLists[mindisver];
        while (p)
        {
            if (vis[p->ver - 1] != 1 && dis[p->ver - 1] > dis[mindisver] + p->wt)
            {
                dis[p->ver - 1] = dis[mindisver] + p->wt;
                parent[p->ver] = mindisver + 1;
            }
            p = p->next;
        }
        vis[mindisver] = 1;
        donever++;
    }

    Stack s;
    initStack(&s, g.numVertices);
    int i = dess;
    while (i != 0)
    {
        push(&s, i);
        i = parent[i];
    }

    printf("The shortest path between %s and %s is : \n", users[scr], users[dess]);
    while (!isEmptys(&s))
    {
        printf("%s ", users[pop(&s)]);
        if (s.top != -1)
            printf("-> ");
    }
    printf("\n\n");

    free(dis);
    free(vis);
    free(parent);
    return;
}


void mutual_friends(GraphList G, int cm[MAX_NODE][MAX_NODE], int s1, int s2)
{
    printf("The mutual friends of %s and %s are : \n", users[s1], users[s2]);
    int count = 0;
    for (int i = 1; i <= G.numVertices; i++)
    {
        if ((cm[s1][i] == 1 && i != s2) && (cm[s2][i] == 1 && i != s1))
        {
            printf("%s\n", users[i]);
            count++;
        }    
    }
    if(count == 0)
        printf("The given vertices have no mutual friends");
    printf("\n");
}

void first_level_friends(GraphList G , int cm[MAX_NODE][MAX_NODE] , int user)
{
    printf("The first-level friends of %s are :\n", users[user]);
    for (int i = 1; i <= G.numVertices; i++)
    {
        if(cm[user][i] == 1)
            printf("%s\n",users[i]);
    }
    printf("\n");
}

void recommendations(GraphList G , int cm[MAX_NODE][MAX_NODE], int ver)
{
    // Implement dijkstra's algorithm here , as it is , except printing part
    int totalver = G.numVertices;
    int start = ver - 1;
    int *dis = (int *)malloc(sizeof(int) * totalver);
    int *vis = (int *)calloc(totalver, sizeof(int));

    for (int i = 0; i < totalver; i++)
    {
        dis[i] = INT_MAX;
    }

    dis[start] = 0;
    int donever = 0;
    while (donever < totalver - 1)
    {
        int mindisver = findminfromdis(totalver, vis, dis);
        Node *p = G.arrOfLists[mindisver];
        while (p)
        {
            if (vis[p->ver - 1] != 1 && dis[p->ver - 1] > dis[mindisver] + p->wt)
            {
                dis[p->ver - 1] = dis[mindisver] + p->wt;
            }
            p = p->next;
        }
        vis[mindisver] = 1;
        donever++;
    }

    printf("The recommendations for %s are :\n" , users[ver]);
    for (int i = 0; i < G.numVertices; i++)
    {
        if(dis[i] == 2)
            printf("%s\n",users[i+1]);
    }
    printf("\n");
}
