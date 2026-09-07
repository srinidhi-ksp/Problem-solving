#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

int networkDelayTime(int times[][3], int timesSize,
                     int n, int k) {

    int graph[n + 1][n + 1];

    // Initialize
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= n; j++) {

            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    // Build graph
    for (int i = 0; i < timesSize; i++) {

        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];

        graph[u][v] = w;
    }

    int dist[n + 1];
    int visited[n + 1];

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[k] = 0;

    // Dijkstra
    for (int count = 1; count <= n; count++) {

        int u = -1;
        int minDist = INF;

        for (int i = 1; i <= n; i++) {

            if (!visited[i] && dist[i] < minDist) {

                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 1; v <= n; v++) {

            if (!visited[v] &&
                graph[u][v] != INF &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] =
                    dist[u] + graph[u][v];
            }
        }
    }

    int answer = 0;

    for (int i = 1; i <= n; i++) {

        if (dist[i] == INF)
            return -1;

        if (dist[i] > answer)
            answer = dist[i];
    }

    return answer;
}
