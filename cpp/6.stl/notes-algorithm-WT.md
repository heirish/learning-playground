## Algorithms Walkthrough
https://www.youtube.com/watch?v=eV7tVdNIw9o&t=10s

https://www.quantstart.com/articles/C-Standard-Template-Library-Part-III-Algorithms/
### Non-modifying Algoritms
count, min, max, compare, linear search, attribute
- most algorithms have a simple form and a generalized form
  
### Modifying Algorithms
- copy, move, transform, swap, fill, replace, remove:change the element value
- order-changing algorithm:reverse, rotate, permute, shuffle:they changes the order of elements in container, but not necessarily the elements themselves.

### Sorting Algorithms
- Sorting algorithm **requires random access iterators**: vector, deque, container array, native array
- list can NOT use this algorithm, but it has a .sort() member function  
- Heap Algorithms
  - First element is always the largest
  - Add/remove takes O(logn) time

### sorted data algorithms and Numeric algorithms
- Sorted data algorithms: algorithms that require data being pre-sorted.
  - binary search, merge, set operations,
  - every sorted data algorithm has a generialized form with a same name
- numeric algorithms 
  - defined in header `<numeric>`
  - accumulate, inner product, partial sum, adjacent difference