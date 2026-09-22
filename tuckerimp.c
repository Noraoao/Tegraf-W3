#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int id;
    struct Edge* next;
} Edge;

#define MAXN 100005
#define MAXM 200005

Edge* adj[MAXN];
int degree[MAXN];
int visited_edge[MAXM];

// Struktur Doubly Linked List untuk menyimpan Tour dan mempermudah Absorption
typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* create_node(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

void add_edge(int u, int v, int id) {
    Edge* e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = v;
    e1->id = id;
    e1->next = adj[u];
    adj[u] = e1;

    Edge* e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = u;
    e2->id = id;
    e2->next = adj[v];
    adj[v] = e2;

    degree[u]++;
    degree[v]++;
}

// Fungsi untuk membentuk 1 siklus tunggal dari simpul awal (Cycle Decomposition)
Node* get_cycle(int start_node) {
    Node* head = create_node(start_node);
    Node* tail = head;
    int curr = start_node;

    while (1) {
        // Cari edge yang belum terpakai
        while (adj[curr] != NULL && visited_edge[adj[curr]->id]) {
            adj[curr] = adj[curr]->next;
        }

        if (adj[curr] == NULL) break;

        Edge* e = adj[curr];
        visited_edge[e->id] = 1;
        adj[curr] = adj[curr]->next;

        curr = e->to;
        tail->next = create_node(curr);
        tail = tail->next;

        if (curr == start_node) break; // Siklus tertutup terbentuk
    }

    return head;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, i);
    }

    // 1. Degree Check
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    // 2. Start Main Tour T with initial cycle from Node 1
    Node* tour_head = get_cycle(1);

    // Array penanda apakah simpul berada dalam main tour T
    // Mengimpan pointer ke node di tour agar absorption O(1)
    Node** node_in_tour = (Node**)calloc(n + 1, sizeof(Node*));

    Node* curr = tour_head;
    while (curr != NULL) {
        if (node_in_tour[curr->val] == NULL) {
            node_in_tour[curr->val] = curr;
        }
        curr = curr->next;
    }

    // 3. k-Absorption Phase
    // Cari simpul di dalam tour yang masih punya edge sisa, lalu bentuk siklus baru & serap
    int total_edges_visited = 0;

    curr = tour_head;
    while (curr != NULL) {
        int u = curr->val;

        // Bersihkan edge terpakai
        while (adj[u] != NULL && visited_edge[adj[u]->id]) {
            adj[u] = adj[u]->next;
        }

        // Jika simpul u di tour masih punya edge belum terpakai, buat siklus baru & serap
        if (adj[u] != NULL) {
            Node* new_cycle = get_cycle(u);

            // Sisipkan new_cycle ke dalam tour di posisi curr (k-Absorption)
            Node* cycle_tail = new_cycle;
            while (cycle_tail->next != NULL) {
                cycle_tail = cycle_tail->next;
            }

            // Hubungkan ekor siklus baru ke sisa tur lama
            cycle_tail->next = curr->next;
            // Hubungkan tur sebelum u ke kepala siklus baru (melewati node u ganda)
            curr->next = new_cycle->next;

            // Bebaskan memory node head siklus baru karena nilainya sama dengan curr
            free(new_cycle);
        } else {
            curr = curr->next;
        }
    }

    // 4. Hitung jumlah total node dalam tur untuk validasi konektivitas
    int node_count = 0;
    curr = tour_head;
    while (curr != NULL) {
        node_count++;
        curr = curr->next;
    }

    if (node_count != m + 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    // 5. Cetak Hasil Eulerian Tour
    curr = tour_head;
    while (curr != NULL) {
        printf("%d%c", curr->val, (curr->next == NULL) ? '\n' : ' ');
        Node* temp = curr;
        curr = curr->next;
        free(temp); // Free memory
    }

    free(node_in_tour);
    return 0;
}