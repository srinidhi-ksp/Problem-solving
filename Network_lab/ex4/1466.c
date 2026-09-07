#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int to;
    int cost;
    struct Node *next;
} Node;

void addEdge(Node **graph, int from, int to, int cost) {

    Node *newNode = malloc(sizeof(Node));

    newNode->to = to;
    newNode->cost = cost;
    newNode->next = graph[from];

    graph[from] = newNode;
}

void dfs(Node **graph, int node, int parent, int *answer) {

    Node *current = graph[node];

    while (current != NULL) {

        if (current->to != parent) {

            *answer += current->cost;

            dfs(graph, current->to, node, answer);
        }

        current = current->next;
    }
}

int minReorder(int n, int connections[][2]) {

    Node **graph = calloc(n, sizeof(Node *));

    for (int i = 0; i < n - 1; i++) {

        int a = connections[i][0];
        int b = connections[i][1];

        // Original direction a -> b
        // If traversing a -> b from 0, reverse needed
        addEdge(graph, a, b, 1);

        // Reverse representation
        // b -> a is already correct
        addEdge(graph, b, a, 0);
    }

    int answer = 0;

    dfs(graph, 0, -1, &answer);

    return answer;
}
