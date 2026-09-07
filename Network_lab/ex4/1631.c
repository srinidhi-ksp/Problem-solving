#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

typedef struct {
    int r;
    int c;
    int effort;
} Node;

typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;

void swap(Node *a, Node *b) {

    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *heap, Node value) {

    int i = heap->size++;

    heap->data[i] = value;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (heap->data[parent].effort <=
            heap->data[i].effort)
            break;

        swap(&heap->data[parent], &heap->data[i]);

        i = parent;
    }
}

Node pop(MinHeap *heap) {

    Node result = heap->data[0];

    heap->data[0] =
        heap->data[--heap->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size &&
            heap->data[left].effort <
            heap->data[smallest].effort)
            smallest = left;

        if (right < heap->size &&
            heap->data[right].effort <
            heap->data[smallest].effort)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap->data[i],
             &heap->data[smallest]);

        i = smallest;
    }

    return result;
}

int minimumEffortPath(int **heights,
                      int heightsSize,
                      int *heightsColSize) {

    int rows = heightsSize;
    int cols = heightsColSize[0];

    int **dist = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {

        dist[i] = malloc(cols * sizeof(int));

        for (int j = 0; j < cols; j++)
            dist[i][j] = INF;
    }

    MinHeap heap;

    heap.capacity = rows * cols * 4 + 10;
    heap.size = 0;
    heap.data = malloc(heap.capacity * sizeof(Node));

    dist[0][0] = 0;

    push(&heap, (Node){0, 0, 0});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (heap.size > 0) {

        Node current = pop(&heap);

        int r = current.r;
        int c = current.c;
        int effort = current.effort;

        if (r == rows - 1 &&
            c == cols - 1) {

            return effort;
        }

        if (effort > dist[r][c])
            continue;

        for (int d = 0; d < 4; d++) {

            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= rows ||
                nc < 0 || nc >= cols)
                continue;

            int difference =
                abs(heights[r][c] -
                    heights[nr][nc]);

            int newEffort =
                effort > difference
                ? effort
                : difference;

            if (newEffort < dist[nr][nc]) {

                dist[nr][nc] = newEffort;

                push(&heap,
                     (Node){nr, nc, newEffort});
            }
        }
    }

    return 0;
}
