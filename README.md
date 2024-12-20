# Pointer Lab: A Review of C and Pointers

## Introduction

This project revisits fundamental concepts in C programming with an emphasis on **pointers** and **data structures**. It is structured to progressively build an understanding of pointer manipulation, polymorphism, linked lists, tree iterators, and tree analysis. All implementations will be made in **`pointer.c`**, with definitions provided in **`pointer.h`**.

---

## Features

### Part 1: Shape Functions (20 pts)

#### Overview
Implement polymorphic behavior in C by working with shapes represented as structures:
- **`rectangle_t`**: Represents rectangles with width and length.
- **`triangle_t`**: Represents equilateral triangles with a side length.

#### Key Concepts
- Use **virtual function tables** to emulate object-oriented programming.
- Implement the following shape functions:
  1. Area calculations
  2. Perimeter calculations
  3. Shape initialization
  4. Shape comparison

#### Goals
- Understand how base pointers (`shape_t`) can refer to different shape types.
- Implement polymorphic behavior using function pointers.

---

### Part 2: Linked List Functions (30 pts)

#### Overview
Create a basic singly linked list that can be optionally sorted.

#### Functionality
1. **`init`**: Initializes the list and configures sorting based on a comparison function.
2. **`insert`**: Adds new nodes to the list:
   - Unsorted: Insert at the head.
   - Sorted: Use the comparison function to maintain order.
3. **`remove`**: Deletes nodes that contain the specified shape pointer.

#### Goals
- Work with function pointers for custom sorting.
- Manage dynamic memory safely within a linked list structure.

---

### Part 3: Tree Iterator Functions (30 pts)

#### Overview
Develop an iterator for a binary tree of shapes. Iterators encapsulate the process of traversing a data structure without exposing its implementation details.

#### Functionality
1. **`begin`**: Initializes the iterator at the first in-order node.
2. **`next`**: Moves the iterator to the next in-order node.
3. **`at_end`**: Checks if the iterator has reached the end of the tree.
4. **Accessors**:
   - Current node.
   - Shape at the current iterator position.

#### Key Challenges
- Use a **parents array** to simulate a recursive stack for tree traversal.
- Efficiently manage tree traversal without starting from the root.

#### Goals
- Implement in-order traversal using an iterator.
- Leverage parent pointers for non-recursive traversal.

---

### Part 4: Tree Analysis Functions (20 pts)

#### Overview
Analyze and compute properties of the binary tree.

#### Functionality
1. Compute **max**, **min**, and **average area** of shapes in the tree.
2. Apply a user-provided function to each shape in the tree using in-order traversal.

#### Goals
- Iterate through the tree using the implemented iterator or recursion.
- Perform computations on tree nodes efficiently.

---

## Project Structure

### Core Files

- **`pointer.c`**: Main implementation file (modifiable).
- **`pointer.h`**: Definitions for shapes, linked lists, and tree structures.
- **`test.c`**: Contains test cases for verifying functionality.

### Supporting Files

- **`Makefile`**: Build and testing commands.
- **`grade.py`**: Script for automated grading.

---

## Implementation Guidelines

1. **Use Provided Definitions**:
   - All structures and inline functions are defined in **`pointer.h`**.

2. **Polymorphism**:
   - Use function pointers to implement polymorphic behavior.

3. **Linked List**:
   - Handle sorting and unsorted modes using a comparison function pointer.

4. **Tree Iterator**:
   - Use the `parents` array to simulate recursive traversal.

5. **Rules**:
   - Do not include any libraries other than `math.h`.
   - Modify only **`pointer.c`**.

---

## Building and Testing

### Build Commands

- **Build the Project**:
  ```bash
  make
  ```

- **Build in Debug Mode**:
  ```bash
  make debug
  ```

### Running Tests

- **Run All Tests**:
  ```bash
  make test
  ```

- **Debugging Specific Tests**:
  ```bash
  gdb pointer
  ```
  Use `r <test_name>` to run specific tests.

---

## Evaluation Criteria

1. **Shape Functions (20 pts)**:
   - Area and perimeter calculations.
   - Shape initialization and comparison.

2. **Linked List Functions (30 pts)**:
   - Correct insertion, deletion, and optional sorting.

3. **Tree Iterator Functions (30 pts)**:
   - Efficient in-order traversal.

4. **Tree Analysis Functions (20 pts)**:
   - Correct computation of shape properties.

---

## Debugging Tips

1. **Draw Diagrams**:
   - Visualize linked lists and trees to understand behavior.

2. **Conditional Breakpoints**:
   - Use GDB to stop execution when specific conditions are met.

3. **Test Small Examples**:
   - Start with simple shapes and small data structures.

---

## Resources

- [Polymorphism in C](https://en.wikipedia.org/wiki/Polymorphism_(computer_science))
- [Linked List Basics](https://www.geeksforgeeks.org/linked-list-set-1-introduction/)
- [Binary Tree Traversal](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

---

## Author
Implemented by **Vishvendra Reddy Bhoomidi** as part of the Pointer Lab course by Timothy Zhu.
