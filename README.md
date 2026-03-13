# Coursework 2 — Sequence Algorithms

C++ algorithms showcase of fundamental sequence algorithms on integer arrays.

## Algorithms Implemented

| Algorithm | Time Complexity | Space |
|---|---|---|
| Prefix Sums | O(n) build, O(1) query | O(n) |
| Sliding Window Maximum | O(n) monotone deque | O(k) |
| Two-Pointer (Two Sum) | O(n) on sorted data | O(1) |
| Binary Search | O(log n) | O(1) |
| Kadane's Max Subarray | O(n) | O(1) |

## Build & Run

```bash
g++ -std=c++17 -O2 -o coursework2 main.cpp
./coursework2
```

## Description

Generates a random integer array of 20 elements and demonstrates:
- Prefix sums with range sum queries
- Deque-based sliding window maximum
- Two-pointer technique for pair sum on sorted data
- Binary search on sorted array
- Kadane's algorithm for maximum subarray sum
