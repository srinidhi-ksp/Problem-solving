#include <stdio.h>

#define INF 1000000000
#define MAX 405

int dist[MAX][MAX];

int main() {

    int n, m;

    scanf("%d %d", &n, &m);

    // Initialize
    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= n; j++) {

            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    // Read edges
    for (int i = 0; i < m; i++) {

        int u, v, w;

        scanf("%d %d %d", &u, &v, &w);

        // Last edge is considered if duplicate
        dist[u][v] = w;
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; k++) {

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= n; j++) {

                if (dist[i][k] != INF &&
                    dist[k][j] != INF) {

                    int newDist =
                        dist[i][k] + dist[k][j];

                    if (newDist < dist[i][j])
                        dist[i][j] = newDist;
                }
            }
        }
    }

    // Queries
    int q;
    scanf("%d", &q);

    while (q--) {

        int u, v;

        scanf("%d %d", &u, &v);

        if (dist[u][v] == INF)
            printf("-1\n");
        else
            printf("%d\n", dist[u][v]);
    }

    return 0;
}
