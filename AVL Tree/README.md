Output:

Inserting values: 10, 5, 15, 3, 7, 12, 20

=== Tree Structure ===
└── 10 (bf:0)
    ├── 15 (bf:0)
    │   ├── 20 (bf:0)
    │   └── 12 (bf:0)
    └── 5 (bf:0)
        ├── 7 (bf:0)
        └── 3 (bf:0)
=====================

Adding 1, 2 (forces rotations):

=== Tree Structure ===
└── 10 (bf:1)
    ├── 15 (bf:0)
    │   ├── 20 (bf:0)
    │   └── 12 (bf:0)
    └── 5 (bf:1)
        ├── 7 (bf:0)
        └── 2 (bf:0)
            ├── 3 (bf:0)
            └── 1 (bf:0)
=====================

Tree saved as balanced_tree_before_removal.dot
Tree after removing element 10 (root)

=== Tree Structure ===
└── 12 (bf:1)
    ├── 15 (bf:-1)
    │   └── 20 (bf:0)
    └── 5 (bf:1)
        ├── 7 (bf:0)
        └── 2 (bf:0)
            ├── 3 (bf:0)
            └── 1 (bf:0)
            