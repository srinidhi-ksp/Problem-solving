#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define INF 9999

int num_nodes;
int adj_matrix[MAX_NODES][MAX_NODES];
int dv_dist[MAX_NODES][MAX_NODES];
int next_hop[MAX_NODES][MAX_NODES];

void initialize_graph();
void compute_distance_vector();
void print_specific_path(int src, int dest);
void print_individual_routing_table();
void print_initial_routing_matrix();
void print_final_converged_matrix(const char *title);
void print_final_frame_format();

int main() {
    int i, j;
    int update_choice = 1;
    int src, dest, new_cost;
    int q_src, q_dest;

    printf("=== Distance Vector Routing Setup ===\n");
    initialize_graph();

    // 1. Initial direct connections table
    print_initial_routing_matrix();

    // 2. Compute first convergence
    compute_distance_vector();

    // 3. Print converged matrix
    print_final_converged_matrix("--- Final Converged Routing Table Matrix ---");

    // 4. View an individual router's specific list
    print_individual_routing_table();

    // 5. Shortest path query
    printf("\n--- Query Minimum Cost and Shortest Path ---\n");
    printf("Enter Source Node (0 to %d): ", num_nodes - 1);
    scanf("%d", &q_src);
    printf("Enter Destination Node (0 to %d): ", num_nodes - 1);
    scanf("%d", &q_dest);
    print_specific_path(q_src, q_dest);

    // 6. Dynamic update menu
    printf("\nDo you want to update any link cost? (1 for Yes, 0 for No): ");
    scanf("%d", &update_choice);
   
    if (update_choice == 1) {
        printf("Enter Link Source Node (0 to %d): ", num_nodes - 1);
        scanf("%d", &src);
        printf("Enter Link Destination Node (0 to %d): ", num_nodes - 1);
        scanf("%d", &dest);
        printf("Enter New Link Cost (Use %d for Link Down/Infinity): ", INF);
        scanf("%d", &new_cost);

        adj_matrix[src][dest] = new_cost;
        adj_matrix[dest][src] = new_cost;

        printf("\nRecalculating routing modifications...\n");
        compute_distance_vector();

        print_final_converged_matrix("--- Final Converged Routing Table Matrix After Update ---");
        print_individual_routing_table();

        printf("\n--- Query Minimum Cost and Shortest Path After Update ---\n");
        printf("Enter Source Node (0 to %d): ", num_nodes - 1);
        scanf("%d", &q_src);
        printf("Enter Destination Node (0 to %d): ", num_nodes - 1);
        scanf("%d", &q_dest);
        print_specific_path(q_src, q_dest);
    }

    // 7. Visualized network packages
    print_final_frame_format();

    printf("Exiting Distance Vector Routing simulation. Goodbye!\n");
    return 0;
}

void initialize_graph() {
    int i, j;
    printf("Enter the number of nodes (Max %d): ", MAX_NODES);
    scanf("%d", &num_nodes);

    printf("\nEnter the Cost Adjacency Matrix row by row (Space-separated, Use %d for INF):\n", INF);
    for (i = 0; i < num_nodes; i++) {
        printf("Row %d: ", i);
        for (j = 0; j < num_nodes; j++) {
            scanf("%d", &adj_matrix[i][j]);
            if (i == j) {
                adj_matrix[i][j] = 0;
            }
        }
    }
}

void compute_distance_vector() {
    int i, j, k, count;
   
    /* Copy base network connections first */
    for (i = 0; i < num_nodes; i++) {
        for (j = 0; j < num_nodes; j++) {
            dv_dist[i][j] = adj_matrix[i][j];
            if (adj_matrix[i][j] != INF && i != j) {
                next_hop[i][j] = j;
            } else {
                next_hop[i][j] = -1;
            }
        }
    }

    /* Distance Vector iterations (Bellman-Ford equation) */
    do {
        count = 0;
        for (i = 0; i < num_nodes; i++) {
            for (j = 0; j < num_nodes; j++) {
                for (k = 0; k < num_nodes; k++) {
                    /* If a route through neighbor 'k' is shorter, choose it */
                    if (dv_dist[i][k] != INF && adj_matrix[k][j] != INF) {
                        if (dv_dist[i][k] + adj_matrix[k][j] < dv_dist[i][j]) {
                            dv_dist[i][j] = dv_dist[i][k] + adj_matrix[k][j];
                            next_hop[i][j] = next_hop[i][k];
                            count++;
                        }
                    }
                }
            }
        }
    } while (count != 0);
}

void print_initial_routing_matrix() {
    int i, j;
    printf("\n--- Initial Routing Matrix (Direct Connections) ---\n");
    printf("    ");
    for (j = 0; j < num_nodes; j++) {
        printf("N%-4d", j);
    }
    printf("\n");
    for (i = 0; i < num_nodes; i++) {
        printf("N%-3d", i);
        for (j = 0; j < num_nodes; j++) {
            if (adj_matrix[i][j] >= INF) {
                printf("INF  ");
            } else {
                printf("%-5d", adj_matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void print_final_converged_matrix(const char *title) {
    int i, j;
    printf("\n%s\n", title);
    printf("    ");
    for (j = 0; j < num_nodes; j++) {
        printf("N%-4d", j);
    }
    printf("\n");
    for (i = 0; i < num_nodes; i++) {
        printf("N%-3d", i);
        for (j = 0; j < num_nodes; j++) {
            if (dv_dist[i][j] >= INF) {
                printf("INF  ");
            } else {
                printf("%-5d", dv_dist[i][j]);
            }
        }
        printf("\n");
    }
}

void print_individual_routing_table() {
    int r;
    printf("\nEnter Router Node index to view its full table (0 to %d): ", num_nodes - 1);
    scanf("%d", &r);

    printf("    [ Router Node %d Table ]\n", r);
    printf("---------------------------------\n");
    printf(" Dest Node | Min Cost | Next Hop\n");
    printf("---------------------------------\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("    %-6d | ", i);
        if (dv_dist[r][i] >= INF) {
            printf("INF      |    -\n");
        } else {
            printf("%-8d |    ", dv_dist[r][i]);
            if (i == r) {
                printf("-\n");
            } else {
                printf("%d\n", next_hop[r][i]);
            }
        }
    }
    printf("---------------------------------\n");
}

void print_specific_path(int src, int dest) {
    printf("\n--- Routing Result ---\n");
    if (dv_dist[src][dest] >= INF) {
        printf("Path (%d -> %d): Unreachable\n", src, dest);
        return;
    }
    printf("Path (%d -> %d): ", src, dest);
    int curr = src;
    printf("%d", curr);
    while (curr != dest) {
        curr = next_hop[curr][dest];
        printf(" -> %d", curr);
    }
    printf(" | Total Cost: %d\n", dv_dist[src][dest]);
}

void print_final_frame_format() {
    printf("\n=======================================================\n");
    printf("   FINAL CONVERGED TRANSMISSION FRAME FORMATS\n");
    printf("=======================================================\n");
    printf("Visualizing standard packets shared across links:\n");

    for (int i = 0; i < num_nodes; i++) {
        printf("\n+-----------------------------------------------------+\n");
        printf("| Frame From: Router N%d  | Payload Size: %-2d Vectors   |\n", i, num_nodes);
        printf("+-----------------------------------------------------+\n");
        printf("| Target Destination: ");
        for (int j = 0; j < num_nodes; j++) {
            printf("N%-4d", j);
        }
        printf(" |\n");
        printf("+---------------------+-------------------------------+\n");
        printf("| Vector Cost Value:  ");
        for (int j = 0; j < num_nodes; j++) {
            if (dv_dist[i][j] >= INF) {
                printf("INF  ");
            } else {
                printf("%-5d", dv_dist[i][j]);
            }
        }
        printf(" |\n");
        printf("+-----------------------------------------------------+\n");
    }
    printf("=======================================================\n\n");
}
