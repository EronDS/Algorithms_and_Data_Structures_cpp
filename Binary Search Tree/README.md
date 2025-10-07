# BST

## Traversal
### Depth First Traversal (In-Order, Pre-Order and Post-Order)

#### In-Order Traversal

1. Traverse left tree
2. Print or save current value 
3. Traverse right tree

→ This will save/print values in sorted order.

#### Pre-Order Traversal

1. Print or save current value
2. Traverse left tree
3. Traverse right tree

#### Post-Order Traversal

1. Traverse left tree
2. Traverse right tree
3. Print or save current value

### Breadth-First Traversal (Level Traversal)

1. Start from root node
2. Add left and/or right children to queue
3. Continue until queue is empty

## Balancing

In worst-case scenarios, accessing a value in BST can have O(n), same as arrays.

To maintain the O(log n) property in search, the BST must be balanced.

Here, we use balancing through re-adding the sorted nodes using divide and conquer method.

$$BF_i = \text{Left Subtree Height}_i - \text{Right Subtree Height}_i$$

1. Verify if the tree is balanced:
   - For a tree to be balanced, we use the balance factor:
   $$\forall \text{node} \in \text{BST} : -1 \le BF_i \le 1$$

2. If tree is unbalanced: Collect all nodes in sorted order.

3. Insert nodes following divide and conquer method.

## Removing Element

**Case 1:** Node with no children
- Simply delete node and set parent pointer to nullptr

**Case 2:** Node with one child (left or right)
- Replace node with its only child

**Case 3:** Node with two children
- Replace with leftmost node from right subtree (in-order successor)
- Delete the successor node
- *Rightmost from left subtree can be used as well*

