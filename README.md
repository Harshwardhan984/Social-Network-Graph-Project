# README: Social Network Graph Project

Project Overview
This project is a C-based implementation of a Social Network Graph. It models users as nodes and their connections as edges in a graph, allowing users to perform operations such as adding connections, detecting cycles, finding shortest paths, and generating recommendations. The project utilizes data structures like adjacency lists and matrices for efficient graph representation and algorithms for advanced functionalities.

Features
Graph Operations:

Add or remove connections between users.
Print the structure of the graph.
Perform Breadth-First Search (BFS) and Depth-First Search (DFS).
Detect cycles in the graph.

Pathfinding and Recommendations:

Calculate the shortest path between two users using Dijkstra's Algorithm.
Find the Minimum Spanning Tree (MST) using Prim's Algorithm.
Suggest friend recommendations for users based on mutual connections.
Display first-level friends (directly connected users).
Identify mutual friends between two users.

Dynamic User Management:

Load user data from a file (names.txt).
Display and manage user connections interactively.

Menu-Driven Interface:

User-friendly console menu for performing operations interactively.

Project Structure
main.c: Contains the main function with the interactive menu for managing the social network graph.
Project.h: Header file with declarations of the data structures and functions used in the project.
names.txt: Text file storing user names for initialization.

File Description

Project.h: Contains:

Function declarations for graph operations (e.g., addConnection, BFS, DFS, etc.).
Data structures such as adjacency list, adjacency matrix, and user list.

names.txt:

Stores user names, one per line.
Example:
Raj
Amit
Yash
Om
Suraj
Nilesh
Prakash
Ankit
Amol
Mayank

main.c:

Implements the user interface and menu logic.
Demonstrates graph operations using the provided functions.

# How to Run

Requirements:

GCC compiler
C standard library (stdio.h, stdlib.h, etc.)
Steps:

Compile the project using:

gcc -Wall -c Project.c Project_main.c
cc Project.o Project_main.o -o output


Run the executable:
./output

Interactive Menu:

Follow the on-screen instructions to add connections, view the graph, perform BFS/DFS, and more.
Main Functionality Walkthrough
Loading Users:

Users are loaded from names.txt using the loadName() function and initialized into the graph.
Adding Connections:

Users can interactively add connections between two nodes using the menu option.
Menu Options:

Add/Remove Connections: Dynamically update graph edges.
Pathfinding Algorithms: Perform BFS/DFS, detect cycles, and find shortest paths.
Recommendations: Suggest new connections based on mutual friends or shortest paths.
Algorithms Used
Breadth-First Search (BFS):

Traverses the graph level by level starting from a source node.
Depth-First Search (DFS):

Explores as far as possible along each branch before backtracking.
Dijkstra's Algorithm:

Calculates the shortest path from a source to all other nodes.
Prim's Algorithm:

Constructs the Minimum Spanning Tree (MST) for the graph.
Cycle Detection:

Identifies whether a cycle exists in the graph.
Friend Recommendation Algorithm:

Suggests friends by finding nodes at a distance of 2 in the graph.
Sample Graph
Graph Representation:

markdown

                  Raj
               /   |   \
           Ankit - Amit - Yash  
          /         |         \
         Amol     Suraj       Om
          |
       Prakash
      /       \
    Nilesh   Mayank
Adjacency Matrix Example:

1 for connected nodes, 0 otherwise:

   Raj  Amit  Yash  Om  Suraj  Nilesh  Prakash  Ankit  Amol  Mayank
Raj    0     1     1    0     0      0        0       1      0      0
Amit   1     0     1    0     1      0        0       0      0      0
Yash   1     1     0    1     0      0        0       0      0      0
...
Future Enhancements
Add file-based persistence for connections.
Implement weighted edges for more complex networks.
Develop a GUI for visualizing the graph.
Include advanced recommendation algorithms.

Acknowledgments
Developed as part of a Data Structures and Algorithms project.
COEP Technological University.
