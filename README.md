# Task Manager — C++ OOP & Data Structures

## Overview

PS: This file was automatically generated

This project is a small C++ task-management system designed to practice and demonstrate core concepts required for a **Junior C++ Software Engineer** technical interview.

The project combines:

* Object-Oriented Programming
* Inheritance and polymorphism
* Dynamic memory management
* STL containers
* Priority-based task execution
* Stack-based undo functionality
* Binary Search Tree operations
* Recursion
* Searching and deletion algorithms

The goal is not to build a production-ready application, but to practice integrating multiple C++ concepts into a single system.

---

## Project Structure

```text
.
├── Task.h
├── DependencyTree.h
├── TaskManager.h
├── main.cpp
└── README.md
```

### `Task.h`

Contains the task hierarchy.

```text
Task
├── CalculationTask
└── ReportTask
```

`Task` is an abstract base class containing:

* Task ID
* Priority
* Name
* Virtual `execute()` function
* Virtual destructor

The derived classes implement their own version of `execute()`.

---

### `DependencyTree.h`

Implements a Binary Search Tree containing task IDs.

Supported operations:

```cpp
insertDependency(int id);
removeDependency(int id);
dependencyExists(int id);
printDependencies();
treeHeight();
isBalanced();
```

The tree uses the following BST rule:

```text
smaller ID → left
larger ID  → right
```

It also handles the three standard BST deletion cases:

1. Leaf node
2. Node with one child
3. Node with two children

---

### `TaskManager.h`

Contains the main task-management logic.

It uses several data structures:

```text
unordered_map
    ↓
Task ID → Task*

priority_queue
    ↓
Task execution ordering

stack
    ↓
Undo history

DependencyTree
    ↓
BST of task IDs
```

Supported operations include:

```cpp
addTask();
findTask();
removeTask();
executeNext();
undo();
getExecutionOrder();
```

---

### `main.cpp`

Contains a simple interactive command-line menu for testing the system.

The menu allows you to:

```text
1.  Add Calculation Task
2.  Add Report Task
3.  Find Task
4.  Remove Task
5.  Execute Next Task
6.  Undo Last Action
7.  Show Execution Order
8.  Add Dependency
9.  Remove Dependency
10. Search Dependency
11. Print Dependency Tree
12. Show Tree Height
13. Check If Tree Is Balanced
0.  Exit
```

---

# OOP Concepts

## Abstraction

`Task` is an abstract class because `execute()` is pure virtual:

```cpp
virtual void execute() const = 0;
```

This forces derived task types to provide their own implementation.

---

## Inheritance

Two classes inherit from `Task`:

```cpp
class CalculationTask : public Task
```

and:

```cpp
class ReportTask : public Task
```

---

## Polymorphism

Tasks are stored through base-class pointers:

```cpp
Task*
```

but the appropriate derived `execute()` implementation is called at runtime.

For example:

```cpp
Task* task = new CalculationTask(...);

task->execute();
```

calls:

```text
CalculationTask::execute()
```

---

## Virtual Destructor

The base class contains:

```cpp
virtual ~Task() = default;
```

This is important because derived objects are managed through `Task*`.

For example:

```cpp
Task* task = new CalculationTask(...);

delete task;
```

The derived destructor can therefore be correctly invoked through the base pointer.

---

# Data Structures

## `unordered_map`

Tasks are stored using their ID as the key:

```cpp
unordered_map<int, Task*> tasks;
```

This provides efficient average-case lookup:

```text
find task by ID → O(1) average
```

---

## `priority_queue`

Task execution is priority-based.

The ordering rules are:

```text
Higher priority → first

If priorities are equal:
smaller ID → first
```

For example:

```text
ID    Priority

10       5
20       8
30       5
40      10
```

Execution order:

```text
40
20
10
30
```

---

## `stack`

The undo system uses:

```cpp
stack<Action> history;
```

Actions are stored using LIFO ordering:

```text
Last operation
      ↓
     TOP
      ↓
Previous operation
      ↓
Older operation
```

Therefore, the most recent operation is the first one undone.

---

## Binary Search Tree

The dependency system is implemented using a BST.

Example:

```text
        10
       /  \
      5    20
     / \   /
    3   7 15
```

Operations include:

* insertion
* search
* deletion
* traversal
* height calculation
* balance checking

---

# Algorithms

## BST Insertion

Average complexity:

```text
O(log n)
```

Worst case:

```text
O(n)
```

The worst case occurs when the tree becomes highly unbalanced.

---

## BST Search

The search uses the BST ordering property.

```text
id < current node
    → search left

id > current node
    → search right
```

Average:

```text
O(log n)
```

Worst case:

```text
O(n)
```

---

## BST Deletion

The implementation handles:

### Leaf

```text
    10
   /
  5
```

Deleting `5`.

### One child

```text
    10
   /
  5
 /
2
```

Deleting `5`.

### Two children

```text
      10
     /  \
    5    20
        /
       15
```

Deleting `10`.

The minimum element of the right subtree is used as the replacement.

---

# Memory Management

Tasks are dynamically allocated:

```cpp
new CalculationTask(...)
```

or:

```cpp
new ReportTask(...)
```

The `TaskManager` is responsible for releasing tasks that remain stored when it is destroyed.

The dependency tree also owns dynamically allocated nodes.

The tree destructor recursively deletes every node.

---

# Complexity Overview

| Operation             |                             Average | Worst Case |
| --------------------- | ----------------------------------: | ---------: |
| Add task              |                                O(1) |       O(1) |
| Find task             |                                O(1) |       O(n) |
| Remove task           |                                O(1) |       O(1) |
| Build execution queue |                          O(n log n) | O(n log n) |
| Execute next task     |                          O(n log n) | O(n log n) |
| BST insertion         |                            O(log n) |       O(n) |
| BST search            |                            O(log n) |       O(n) |
| BST deletion          |                            O(log n) |       O(n) |
| Undo                  |                        O(1) average |       O(1) |
| Tree height           |                                O(n) |       O(n) |
| Balance check         | O(n²) in the current implementation |      O(n²) |

---

# Compilation

Using `g++`:

```bash
g++ -std=c++17 main.cpp -o task_manager
```

Run:

```bash
./task_manager
```

---

# Example Workflow

Start the program:

```text
========== TASK MANAGER ==========
1. Add Calculation Task
2. Add Report Task
3. Find Task
...
Choice:
```

Add several tasks:

```text
ID: 10
Priority: 5
Name: Calculate Risk

ID: 20
Priority: 8
Name: Generate Report

ID: 30
Priority: 5
Name: Calculate Exposure
```

Then select:

```text
7. Show Execution Order
```

The result should be:

```text
20 10 30
```

because:

```text
Priority 8 → ID 20

Priority 5:
    ID 10
    ID 30
```

Therefore:

```text
20 → 10 → 30
```

---

# Purpose of the Project

This project was created as a preparation exercise for a **Junior C++ Software Engineer technical examination**.

It intentionally combines several concepts that commonly appear together in technical programming assessments:

```text
C++
 │
 ├── OOP
 │   ├── Abstraction
 │   ├── Inheritance
 │   ├── Polymorphism
 │   └── Virtual functions
 │
 ├── Memory
 │   ├── Pointers
 │   ├── new/delete
 │   └── Object ownership
 │
 ├── STL
 │   ├── unordered_map
 │   ├── priority_queue
 │   └── stack
 │
 ├── Data Structures
 │   └── Binary Search Tree
 │
 └── Algorithms
     ├── Searching
     ├── Insertion
     ├── Deletion
     ├── Traversal
     └── Ordering
```

The project deliberately does **not** use Dynamic Programming or Greedy algorithms. It is intended as a final review of C++ fundamentals, OOP, STL, data structures, recursion, and basic algorithms before moving on to those topics.
