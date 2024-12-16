#include "Project.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

/*
    Our social network graph looks like - 
                  Raj
               /   |   \
           Ankit - Amit - Yash  
          /         |         \
         Amol     Suraj       Om
          |
       Prakash
      /       \
    Nilesh   Mayank

*/

int main()
{
    int numVertices = MAX_NODE;
    GraphList G;
    initGraph(&G, numVertices);

    // Initialising cost matrix
    int cm[MAX_NODE][MAX_NODE];
    for (int i = 1; i <= numVertices; i++)
    {
        for (int j = 1; j <= numVertices; j++)
        {
            cm[i][j] = 0;
        }
    }

    // These are the users of the social network
    /*char usersList[12][12] = {
        "", "Raj", "Amit", "Yash", "Om",
        "Suraj", "Nilesh", "Prakash",
        "Ankit", "Amol", "Mayank"
    };
    */
	
	// Initialize users array
        initUsers();
	
	loadName("names.txt");
	
    printf("The users of this social network and their respective numbers are:\n");
    for (int i = 1; i <= MAX_NODE && users[i][0] != '\0'; i++) {
        printf("%d. %s\n", i, users[i]);
    }

    printf("\n");
/*
    addvertexwithWT(&G, 1, 3, 1, cm);
    addvertexwithWT(&G, 8, 9, 1, cm);
    addvertexwithWT(&G, 2, 5, 1, cm);
    addvertexwithWT(&G, 1, 8, 1, cm);
    addvertexwithWT(&G, 2, 8, 1, cm);
    addvertexwithWT(&G, 1, 2, 1, cm);
    addvertexwithWT(&G, 6, 7, 1, cm);
    addvertexwithWT(&G, 2, 3, 1, cm);
    addvertexwithWT(&G, 4, 3, 1, cm);
    addvertexwithWT(&G, 9, 7, 1, cm);
    addvertexwithWT(&G, 10, 7, 1, cm);
*/
char name1[50], name2[50];
    char a;

	printf("Do you want to add Connection (y/n): ");
    scanf(" %c", &a); // Use a space before %c to consume the newline

    switch (a) {
        case 'y': 
            do {
                printf("Enter first name: ");
                scanf("%s", name1);
                printf("Enter second name: ");
                scanf("%s", name2);

                addConnection(name1, name2, &G, cm);

                printf("Do you want to add another connection? (y/n): ");
                scanf(" %c", &a); // Again, use a space before %c
            } while (a == 'y');
            break;

        case 'n': 
            printf("You need to add at least one connection.\n");
            break;

        default:
            printf("Unexpected input. Exiting.\n");
            break;
    }

    int choice;
    bool flag = true;

    printf("\nMenu : \n");
    printf("    1.to remove a connection between 2 users\n");
    printf("    2.to free graph of users\n");
    printf("    3.to print graph of users\n");
    printf("    4.to find BFS of graph of users\n");
    printf("    5.to find DFS of graph of users\n");
    printf("    6.to detect cycle in a graph of users\n");
    printf("    7.to find minimum spanning graph of users using Prim's Algorithm\n");
    printf("    8.to find shortest distance beween a user and remaining users using Dijkstra's Algorithm\n");
    printf("    9.to find shortest path between two users\n");

    printf("    10.to find mutual friends of two users\n");
    // if i connected to k , j connected to k and i != j then k is mutual friend of i and j

    printf("    11.to find first-level friends of the user\n");
    // if j is directly connected to user then , j is first-level friend of user

    printf("    12.to display the recommendations to the user\n");
    // if the shortest distance between j and user is == 2 ( that is , if j and user have at least one
    //      mutual friend then , recommend j to user

    printf("Enter 0 to exit\n\n");

    while (flag == true)
    {

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("\nThank You for visiting!\n\n");
            flag = false;
            break;

        case 1:
        {
            int scr, dess;
            printf("\nEnter the vertices to remove ( scr and dess ) : \n");
            scanf("%d", &scr);
            scanf("%d", &dess);
            removeVertex(&G, scr, dess, cm);
            break;
        }

        case 2:
            freeGraph(&G);
            printf("\nThe graph is cleared successfully\n\n");
            break;

        case 3:
            printf("\nThe graph structure will be : \n");
            printgraph(G);
            break;

        case 4:
        {
            int startbfs;
            printf("\nEnter the vertex from which you want to find BFS : ");
            scanf("%d", &startbfs);
            BFS(G, startbfs);
            break;
        }

        case 5:
        {
            int startdfs;
            printf("\nEnter the vertex from which you want to find DFS : ");
            scanf("%d", &startdfs);
            DFS(G, startdfs);
            break;
        }

        case 6:
        {
            int val = Checkifcircular(G, 1);
            if (val == 1)
                printf("\nThe graph contains a cycle\n\n");
            else
                printf("\nThe graph don't contain a cycle\n\n");
            break;
        }

        case 7:
        {
            int Prims;
            printf("\nEnter the vertex from which you have to find minimum spanning graph : ");
            scanf("%d", &Prims);
            prims(G, Prims);
            break;
        }

        case 8:
        {
            int dijkstras;
            printf("\nEnter the vertex from which you have to find the shortest distance to all vertices : ");
            scanf("%d", &dijkstras);
            Dijkstras(G, dijkstras);
            break;
        }

        case 9:
        {
            int src, dest;
            printf("\nEnter the vertices to find shortest path ( src and dest ) : \n");
            scanf("%d", &src);
            scanf("%d", &dest);
            PrintShortPath(G, src, dest);
            break;
        }

        case 10:
        {
            int s1, s2;
            printf("\nEnter the vertices to find mutual friends ( s1 and s2 ) : \n");
            scanf("%d", &s1);
            scanf("%d", &s2);
            mutual_friends(G, cm, s1, s2);
            break;
        }

        case 11:
        {
            int user;
            printf("\nEnter the vertex to find its first-level friends : ");
            scanf("%d", &user);
            first_level_friends(G, cm, user);
            break;
        }

        case 12:
        {
            int user;
            printf("\nEnter the vertex to find its recommendations : ");
            scanf("%d", &user);
            recommendations(G, cm, user);
            break;
        }

        default:
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
