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

### Kruskal's Algorithm [kalo udah diganti hapus ini]

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
      <img width="400" height="208" alt="WhatsApp Video 2026-09-15 at 00 35 03 (1)" src="https://github.com/user-attachments/assets/127d3b6e-d448-4be2-8ded-b164160aedbb" />

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

### Kruskal

<img width="308" height="293" alt="image" src="https://github.com/user-attachments/assets/f5cc38e6-fa92-454b-aa33-14da3f647b30" />

### Reverse-Delete

<img width="472" height="494" alt="image" src="https://github.com/user-attachments/assets/262956b9-29c0-492f-8b12-6292c8d586ba" />

## Usage of Ai

- https://claude.ai/share/6ca69834-0ce3-4beb-b3e5-3a9a2dee0408
- https://share.gemini.google/Z8uD9kv3qFwU
