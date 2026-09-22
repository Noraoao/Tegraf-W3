## Network Failure Simulations (Kruskal's Algorithm)

### Simulation 1: Single Edge Failure (Edge A–G Fails)

To simulate a link disconnection between **A** and **G**, edge `{0, 6, 5}` is removed from the active edge list before executing Kruskal's algorithm.

**Execution Step-by-Step:**

1. **Sort active edges by weight**: 
   - Weight 5: `B-C` (5), `E-D` (5), `F-E` (5)
   - Weight 6: `A-C` (6), `G-F` (6)
   - Weight 7: `A-B` (7), `B-D` (7), `C-E` (7)
   - Weight 9: `B-E` (9), `F-C` (9)
   - Weight 10: `A-F` (10)
2. **Process Weight 5**:
   - Accept `B-C` (5) -> Connects B and C
   - Accept `E-D` (5) -> Connects E and D
   - Accept `F-E` (5) -> Connects F, E, D
3. **Process Weight 6**:
   - Accept `A-C` (6) -> Connects A, B, C
   - Accept `G-F` (6) -> Connects G to F, E, D
4. **Process Weight 7**:
   - Skip `A-B` (7) -> Forms cycle in {A, B, C}
   - Skip `B-D` (7) -> Connects existing components
   - Accept `C-E` (7) -> Merges {A, B, C} with {G, F, E, D}

**Adapted Output:**

    Edge    Weight
    -----------------
    B - C   5
    E - D   5
    F - E   5
    A - C   6
    G - F   6
    C - E   7
    -----------------
    Total MST weight: 34

---

### Simulation 2: Node Failure (Node C Fails)

When node **C** suffers a total breakdown, all edges connected to vertex `2` (`A-C`, `F-C`, `C-E`, `B-C`) are filtered out.

**Execution Step-by-Step:**

1. **Sort active edges (excluding C)**:
   - Weight 5: `A-G` (5), `E-D` (5), `F-E` (5)
   - Weight 6: `G-F` (6)
   - Weight 7: `A-B` (7), `B-D` (7)
   - Weight 9: `B-E` (9)
   - Weight 10: `A-F` (10)
2. **Process Weight 5**:
   - Accept `A-G` (5) -> Connects A and G
   - Accept `E-D` (5) -> Connects E and D
   - Accept `F-E` (5) -> Connects F, E, D
3. **Process Weight 6**:
   - Accept `G-F` (6) -> Merges component {A, G} with {F, E, D}
4. **Process Weight 7**:
   - Accept `A-B` (7) -> Connects B to component {A, G, F, E, D}
   - Skip `B-D` (7) -> Forms cycle

**Adapted Output:**

    Edge    Weight
    -----------------
    A - G   5
    E - D   5
    F - E   5
    G - F   6
    A - B   7
    -----------------
    Total MST weight: 28
