#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    /* Each undirected street is stored as two directed edges. */
    int *head = malloc((size_t)(n + 1) * sizeof(int));
    int *next = malloc((size_t)(2 * m) * sizeof(int));
    int *to = malloc((size_t)(2 * m) * sizeof(int));
    int *degree = calloc((size_t)(n + 1), sizeof(int));
    int *used = calloc((size_t)(2 * m), sizeof(int));
    int *stack = malloc((size_t)(m + 1) * sizeof(int));
    int *path = malloc((size_t)(m + 1) * sizeof(int));

    if (head == NULL || next == NULL || to == NULL || degree == NULL ||
        used == NULL || stack == NULL || path == NULL) {
        free(head);
        free(next);
        free(to);
        free(degree);
        free(used);
        free(stack);
        free(path);
        return 1;
    }

    for (int vertex = 1; vertex <= n; ++vertex) {
        head[vertex] = -1;
    }

    int edge_count = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);

        to[edge_count] = v;
        next[edge_count] = head[u];
        head[u] = edge_count++;

        to[edge_count] = u;
        next[edge_count] = head[v];
        head[v] = edge_count++;

        degree[u]++;
        degree[v]++;
    }

    for (int vertex = 1; vertex <= n; ++vertex) {
        if (degree[vertex] % 2 != 0) {
            printf("IMPOSSIBLE\n");
            free(head);
            free(next);
            free(to);
            free(degree);
            free(used);
            free(stack);
            free(path);
            return 0;
        }
    }

    /* ptr[vertex] points to the next adjacency edge to inspect. */
    int *ptr = malloc((size_t)(n + 1) * sizeof(int));
    if (ptr == NULL) {
        free(head);
        free(next);
        free(to);
        free(degree);
        free(used);
        free(stack);
        free(path);
        return 1;
    }

    for (int vertex = 1; vertex <= n; ++vertex) {
        ptr[vertex] = head[vertex];
    }

    int stack_size = 0;
    int path_size = 0;
    stack[stack_size++] = 1;

    while (stack_size > 0) {
        int vertex = stack[stack_size - 1];

        while (ptr[vertex] != -1 && used[ptr[vertex]]) {
            ptr[vertex] = next[ptr[vertex]];
        }

        if (ptr[vertex] != -1) {
            int edge = ptr[vertex];
            ptr[vertex] = next[edge];
            used[edge] = 1;
            used[edge ^ 1] = 1;
            stack[stack_size++] = to[edge];
        } else {
            path[path_size++] = vertex;
            stack_size--;
        }
    }

    if (path_size != m + 1) {
        printf("IMPOSSIBLE\n");
    } else {
        for (int i = path_size - 1; i >= 0; --i) {
            printf("%d%c", path[i], i == 0 ? '\n' : ' ');
        }
    }

    free(head);
    free(next);
    free(to);
    free(degree);
    free(used);
    free(stack);
    free(path);
    free(ptr);
    return 0;
}
