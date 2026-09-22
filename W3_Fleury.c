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