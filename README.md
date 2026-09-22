# Graph Theory Assignment W3-Group 4

## Step/Explanation about the algorithm

<table>
  <tr>
    <td width="50%" valign="top">

### Fleury's Algorithm  

  Steps:  
  1. Check the degree of all vertices. If any vertex has an odd degree, return IMPOSSIBLE.
  2. Start the tour at crossing 1 and record it as the current vertex in the path array.
  3. Look for the next valid edge connected to the current vertex:
     - Iterate through all neighboring vertices connected by an unused street.
     - Check if traversing the edge acts as a bridge (which disconnects the remaining graph) using is_valid_next_edge().
     - Pick a non-bridge edge if available; otherwise, pick the bridge edge if it is the only option left.
  4. Remove the selected edge from the graph and move to the destination vertex.
  5. Append the new vertex to the path array.
  6. Repeat steps 3–5 until no remaining edges are connected to the current vertex.
  7. Verify that the path array contains exactly $m + 1$ vertices; if not, return IMPOSSIBLE due to disconnected streets.
  8. Print the collected path array sequentially from start to end as the final Eulerian route.   


  </td>
    <td >
      Code:
      
     #include <stdio.h>
    #include <string.h>

    #define MAX_VERTICES 2005 
    #define MAX_EDGES 200005

    int graph[MAX_VERTICES][MAX_VERTICES];
    int n, m;

    int path[MAX_EDGES];
    int path_sz = 0;

    int count_reachable(int v, int visited[]) {
        visited[v] = 1;
        int count = 1;
        for (int i = 1; i <= n; i++) {
            if (graph[v][i] && !visited[i]) {
                count += count_reachable(i, visited);
            }
        }
        return count;
    }

    int is_valid_next_edge(int u, int v) {
        int count = 0;
    
        for (int i = 1; i <= n; i++) {
            if (graph[u][i]) count++;
        }
    if (count == 1) return 1;

    int visited[MAX_VERTICES] = {0};
    int count1 = count_reachable(u, visited);

    graph[u][v]--;
    graph[v][u]--;
    memset(visited, 0, sizeof(visited));
    int count2 = count_reachable(u, visited);

    graph[u][v]++;
    graph[v][u]++;

    return (count1 <= count2);
    }

    void find_euler_tour(int start) {
        int curr = start;
        path[path_sz++] = curr;
    
        while (1) {
            int next_v = -1;
        
            for (int v = 1; v <= n; v++) {
                if (graph[curr][v]) {
                    if (next_v == -1) {
                        next_v = v;
                    }
                    if (is_valid_next_edge(curr, v)) {
                        next_v = v;
                        break; 
                    }
                }
            }
        
            if (next_v == -1) break;
        
            graph[curr][next_v]--;
            graph[next_v][curr]--;
            curr = next_v;
        
            path[path_sz++] = curr;
        }
    }

    int main() {
        if (scanf("%d %d", &n, &m) != 2) return 0;
    
        int deg[MAX_VERTICES] = {0};
    
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u][v]++;
            graph[v][u]++;
            deg[u]++;
            deg[v]++;
        }
    
        for (int i = 1; i <= n; i++) {
            if (deg[i] % 2 != 0) {
                printf("IMPOSSIBLE\n");
                return 0;
            }
        }
    
        find_euler_tour(1);
    
        // Connectivity check: Did we traverse all m edges?
        if (path_sz != m + 1) {
            printf("IMPOSSIBLE\n");
        } else {
            for (int i = 0; i < path_sz; i++) {
                printf("%d ", path[i]);
            }
            printf("\n");
        }
    
        return 0;
    }
  </td>
  </tr>
</table>
<table>
  <tr>
    <td width="50%" valign="top">

### Hielholzier's Algorithm 

  Steps:
  
  1. Check the degree of all vertices. If any vertex has an odd degree, return IMPOSSIBLE.
  2. Initialize an empty traversal stack and push the starting vertex (node 1) onto it.
  3. Look at the top vertex on the stack.
  4. If the top vertex has unvisited edges:
     - Select an unvisited edge and mark both forward and reverse directions as used.
     - Advance the vertex's edge pointer to skip used edges in future checks.
     - Push the destination vertex onto the stack.
  5. Else (if no unvisited edges remain for the top vertex):
     - Pop the vertex from the stack and append it to the circuit result array.
  6. Repeat steps 3–5 until the traversal stack is completely empty.
  7. Verify that the result array contains exactly m + 1 vertices. If not, return IMPOSSIBLE due to disconnected edges.
  8. Print the circuit result array in reverse order to get the correct path starting from node 1.   

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

### Tucker’s Algorithm

  Steps:
  
  1. Check the degree of all vertices; if any vertex has an odd degree, return IMPOSSIBLE.
  2. Partition all $M$ streets into a set of edge-disjoint closed cycles by traversing unvisited edges until returning to a visited node.   
  3. Initialize the main circuit (which starts at crossing 1).   
  4. Find an unabsorbed cycle Ci that shares a common vertex v with the main circuit.   
  5. Merge Ci into T at vertex v (k absorption) by traversing T up to v, inserting the entire cycle Ci, and continuing the rest of T.   
  6. Repeat steps 4–5 until all cycles are merged into T.   
  7. Verify that T contains all M edges. If not, return IMPOSSIBLE due to disconnected streets.   
  8. Print the merged circuit T as the final Eulerian route starting from crossing 1.   

  </td>
    <td >
      Code:

      #include <stdio.h>
      #include <stdlib.h>

      int main(void) {
        // Fast I/O for C execution
        int n, m;
        if (scanf("%d %d", &n, &m) != 2) {
            return 0;
        }

    // Allocate memory for Forward Star / Adjacency List graph structure
    int *head = malloc((size_t)(n + 1) * sizeof(int));
    int *next = malloc((size_t)(2 * m) * sizeof(int));
    int *to = malloc((size_t)(2 * m) * sizeof(int));
    int *degree = calloc((size_t)(n + 1), sizeof(int));
    int *used = calloc((size_t)(2 * m), sizeof(int));
    int *ptr = malloc((size_t)(n + 1) * sizeof(int));

    // Stack and Path tracking for Hierholzer's Algorithm
    int *stack = malloc((size_t)(m + 1) * sizeof(int));
    int *path = malloc((size_t)(m + 1) * sizeof(int));

    if (head == NULL || next == NULL || to == NULL || degree == NULL ||
        used == NULL || ptr == NULL || stack == NULL || path == NULL) {
        free(head);
        free(next);
        free(to);
        free(degree);
        free(used);
        free(ptr);
        free(stack);
        free(path);
        return 1;
    }

    // Initialize adjacency list heads
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }

    // Graph Construction: Each street is added as two directed edges
    int edge_count = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) {
            free(head);
            free(next);
            free(to);
            free(degree);
            free(used);
            free(ptr);
            free(stack);
            free(path);
            return 1;
        }

        // Edge u -> v (at index 2*i)
        to[edge_count] = v;
        next[edge_count] = head[u];
        head[u] = edge_count++;

        // Edge v -> u (at index 2*i + 1)
        to[edge_count] = u;
        next[edge_count] = head[v];
        head[v] = edge_count++;

        degree[u]++;
        degree[v]++;
    }

    // Check 1: Every crossing must have an even degree for an Eulerian circuit
    for (int i = 1; i <= n; ++i) {
        if (degree[i] % 2 != 0) {
            printf("IMPOSSIBLE\n");
            free(head); free(next); free(to); free(degree);
            free(used); free(ptr); free(stack); free(path);
            return 0;
        }
    }

    // Set traversal pointers to current head of adjacency list
    for (int i = 1; i <= n; ++i) {
        ptr[i] = head[i];
    }

    int stack_size = 0;
    int path_size = 0;

    // Start Hierholzer's algorithm at crossing 1 (Post Office)
    stack[stack_size++] = 1;

    while (stack_size > 0) {
        int u = stack[stack_size - 1];

        // Advance pointer to skip already visited edges connected to node u
        while (ptr[u] != -1 && used[ptr[u]]) {
            ptr[u] = next[ptr[u]];
        }

        if (ptr[u] != -1) {
            int e = ptr[u];
            ptr[u] = next[e]; // Move pointer forward

            used[e] = 1;        // Mark forward edge as used
            used[e ^ 1] = 1;    // Mark reverse edge as used in O(1) time

            stack[stack_size++] = to[e]; // Traversal step
        } else {
            // Backtracking step: Node u has no unvisited edges left
            path[path_size++] = u;
            stack_size--;
        }
    }

    // Check 2: Connectivity verification
    // A complete route visiting m streets must contain m + 1 crossings
    if (path_size != m + 1) {
        printf("IMPOSSIBLE\n");
    } else {
        // Output the path in reverse order (since nodes were pushed during backtrack)
        for (int i = path_size - 1; i >= 0; --i) {
            printf("%d%c", path[i], i == 0 ? '\n' : ' ');
        }
    }

    // Free dynamically allocated memory
    free(head); free(next); free(to); free(degree);
    free(used); free(ptr); free(stack); free(path);

    return 0;
}
       
  </td>
  </tr>
</table>

## Instructions to run the Code

- Open a C compiler
- Run the code

## Result of sample 

### Fleury

 <img width="417" height="332" alt="image" src="https://github.com/user-attachments/assets/54cb57d0-b1ec-47c5-a077-e55e63aae2ef" />

### Hielholzier

<img width="432" height="338" alt="image" src="https://github.com/user-attachments/assets/25950eb8-0d03-430d-9adc-48534fc194d9" />

### Tucker

<img width="420" height="340" alt="image" src="https://github.com/user-attachments/assets/17944f41-99ea-4d91-828e-685f5f607dd4" />


## Usage of Ai

- https://share.gemini.google/TAsWWn5vB5ZW
- 
