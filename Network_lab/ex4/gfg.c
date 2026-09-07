import java.util.ArrayList;

class Solution {
    public ArrayList<Integer> bellmanFord(int V, int[][] edges, int src) {

        int INF = (int) 1e8;

        // Step 1: Initialize distances
        int[] dist = new int[V];

        for (int i = 0; i < V; i++) {
            dist[i] = INF;
        }

        // Distance from source to itself = 0
        dist[src] = 0;

        // Step 2: Relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {

            boolean changed = false;

            for (int j = 0; j < edges.length; j++) {

                int u = edges[j][0];
                int v = edges[j][1];
                int weight = edges[j][2];

                // Relaxation
                if (dist[u] != INF &&
                    dist[u] + weight < dist[v]) {

                    dist[v] = dist[u] + weight;
                    changed = true;
                }
            }

            // If no distance changed, we can stop early
            if (!changed)
                break;
        }

        // Step 3: Check for negative weight cycle
        for (int j = 0; j < edges.length; j++) {

            int u = edges[j][0];
            int v = edges[j][1];
            int weight = edges[j][2];

            if (dist[u] != INF &&
                dist[u] + weight < dist[v]) {

                // Negative weight cycle exists
                ArrayList<Integer> result = new ArrayList<>();
                result.add(-1);
                return result;
            }
        }

        // Step 4: Convert distance array to ArrayList
        ArrayList<Integer> result = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            result.add(dist[i]);
        }

        return result;
    }
}
