int* shortestReach(int n, int edges_rows, int edges_columns,
                   int** edges, int s, int* result_count) {

    // Create adjacency list
    int *head = malloc((n + 1) * sizeof(int));

    int *to = malloc((2 * edges_rows) * sizeof(int));
    int *weight = malloc((2 * edges_rows) * sizeof(int));
    int *next = malloc((2 * edges_rows) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    int edgeCount = 0;

    // Graph is UNDIRECTED
    for (int i = 0; i < edges_rows; i++) {

        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        // u -> v
        to[edgeCount] = v;
        weight[edgeCount] = w;
        next[edgeCount] = head[u];
        head[u] = edgeCount++;

        // v -> u
        to[edgeCount] = u;
        weight[edgeCount] = w;
        next[edgeCount] = head[v];
        head[v] = edgeCount++;
    }

    // Distance array
    int *dist = malloc((n + 1) * sizeof(int));
    int *visited = calloc(n + 1, sizeof(int));

    const int INF = 1000000000;

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }

    dist[s] = 0;

    // Dijkstra
    for (int count = 1; count <= n; count++) {

        int u = -1;
        int minDistance = INF;

        // Find unvisited vertex with minimum distance
        for (int i = 1; i <= n; i++) {

            if (!visited[i] && dist[i] < minDistance) {
                minDistance = dist[i];
                u = i;
            }
        }

        // No more reachable vertices
        if (u == -1) {
            break;
        }

        visited[u] = 1;

        // Relax all neighbours of u
        for (int e = head[u]; e != -1; e = next[e]) {

            int v = to[e];
            int w = weight[e];

            if (!visited[v] &&
                dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
            }
        }
    }

    // Result does NOT include source
    *result_count = n - 1;

    int *result = malloc((n - 1) * sizeof(int));

    int index = 0;

    for (int i = 1; i <= n; i++) {

        if (i == s)
            continue;

        if (dist[i] == INF)
            result[index++] = -1;
        else
            result[index++] = dist[i];
    }

    // Free temporary memory
    free(head);
    free(to);
    free(weight);
    free(next);
    free(dist);
    free(visited);

    return result;
}
