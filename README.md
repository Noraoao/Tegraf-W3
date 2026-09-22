# Graph Theory Assignment W3-Group 4

## Step/Explanation about the algorithm

<table>
  <tr>
    <td width="50%" valign="top">

### Prim's Algorithm [kalo udah diganti hapus ini]

  Steps:  
  1. Start with any vertex in the graph
  2. Mark the starting vertex as part of the spanning tree
  3. Look at all edges that connect a vertex inside the tree to a vertex outside the tree.
  4. Choose the edge with the *smallest* weight.
  5. Add the chosen edge and its outside vertex to the spanning tree.
  6. Repeat steps 3–5 until all vertices are included in the spanning tree.
  7. The edges selected during the process form the minimum spanning tree.


  </td>
    <td >
      <img width="400" height="205" alt="WhatsApp Video 2026-09-15 at 00 35 04 (1)" src="https://github.com/user-attachments/assets/4577feee-3539-4d79-aff6-0a6bfab07256" />

  </td>
  </tr>
</table>
<table>
  <tr>
    <td width="50%" valign="top">

### Hielholzier's Algorithm 

  Steps:
  
  1. Start with all vertices as separate components
  2. Sort all edges in increasing order of their weights
  3. Consider the edge with the *smallest* weight
  4. If adding the edge does not create a cycle:
     
  * add it to the spanning tree.
  - Else
  * skip it.
    
  
  6. Move to the next *smallest* edge.
  7. Repeat steps 4–6 until all vertices are connected.
  8. The edges selected during the process form the minimum spanning tree.


  </td>
    <td >
      Code :
      
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
      
  </td>
  </tr>
</table>
<table>
  <tr>
    <td width="50%" valign="top">

### Reverse-Delete Algorithm [kalo udah diganti hapus ini]

  Steps:
  
  1. Start with the full connected graph containing all its original edges.
  2. Sort all edges in decreasing order of their weights.
  3. Consider the edge with the *largest* weight.
  4. Temporarily remove the edge from the graph and check if the graph remains connected:
     
  * If the graph remains connected, permanently delete the edge.
  * Else, restore the edge back to the graph.
  
  5. Move to the next *largest* edge.
  6. Repeat steps 4–5 until all remaining edges have been evaluated.
  7. The remaining connected graph forms the minimum spanning tree.


  </td>
    <td >
      <img width="400" height="205" alt="WhatsApp Video 2026-09-15 at 00 35 05 (1)" src="https://github.com/user-attachments/assets/8fd3a865-d929-4ad6-a8f9-513f1b6ac02f" />
      
  </td>
  </tr>
</table>

## Instructions to run the Code

- Open a C compiler
- Run the code

## Result of sample [kalo udah diganti hapus ini]

### Prim

<img width="327" height="289" alt="image" src="https://github.com/user-attachments/assets/8e3b8c0a-c10a-4b4c-a5cd-09f24b4e4754" />

### Hielholzier

<img width="432" height="338" alt="image" src="https://github.com/user-attachments/assets/25950eb8-0d03-430d-9adc-48534fc194d9" />

### Reverse-Delete

<img width="472" height="494" alt="image" src="https://github.com/user-attachments/assets/262956b9-29c0-492f-8b12-6292c8d586ba" />

## Usage of Ai [kalo udah diganti hapus ini]

- https://claude.ai/share/6ca69834-0ce3-4beb-b3e5-3a9a2dee0408
- https://share.gemini.google/Z8uD9kv3qFwU
