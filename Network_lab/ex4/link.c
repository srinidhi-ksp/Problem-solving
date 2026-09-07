#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNODES 20
#define UNREACHABLE 9999

int nodeCount;
char nodeName[MAXNODES][20];
int link[MAXNODES][MAXNODES];
int dist[MAXNODES][MAXNODES];
int nextHop[MAXNODES][MAXNODES];

/* look up a node's index by name */
int lookup(char name[])
{
    for (int i = 0; i < nodeCount; i++)
        if (strcmp(nodeName[i], name) == 0)
            return i;
    return -1;
}

/* Bellman-Ford: compute shortest paths from every source */
void computeRoutes(void)
{
    for (int src = 0; src < nodeCount; src++)
    {
        for (int i = 0; i < nodeCount; i++)
        {
            dist[src][i] = link[src][i];
            if (i == src)
                nextHop[src][i] = -1;
            else if (link[src][i] != UNREACHABLE)
                nextHop[src][i] = i;
            else
                nextHop[src][i] = -1;
        }

        for (int pass = 0; pass < nodeCount - 1; pass++)
        {
            for (int i = 0; i < nodeCount; i++)
            {
                for (int j = 0; j < nodeCount; j++)
                {
                    if (link[i][j] != UNREACHABLE && dist[src][i] != UNREACHABLE)
                    {
                        if (dist[src][j] > dist[src][i] + link[i][j])
                        {
                            dist[src][j] = dist[src][i] + link[i][j];
                            if (i == src)
                                nextHop[src][j] = j;
                            else
                                nextHop[src][j] = nextHop[src][i];
                        }
                    }
                }
            }
        }
    }
}
