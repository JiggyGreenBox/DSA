/*
Spanning Tree

    Connect all vertices

    No cycles

    Exactly V-1 edges

-------------------

Minimum Spanning Tree

    Among all spanning trees,

    choose the one with

    minimum total edge weight.

Algorithms

    Prim
    Kruskal

-------------------

1. Kruskal
    uses:
        Disjoint Set Union (Union-Find)


    Sort all edges

    ↓

    Take the cheapest edge

    ↓

    Would it create a cycle?

    No

    ↓

    Take it

    Yes

    ↓

    Skip it

-------------------

2. Prim

    Idea:

        Looks surprisingly similar to Dijkstra.

        Start anywhere.

        Grow the tree.

        Always choose the cheapest outgoing edge.

    Uses

        Priority Queue
*/