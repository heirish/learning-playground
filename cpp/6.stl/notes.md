### Algorithms-iterators-containters
https://www.youtube.com/watch?v=ltBdTiRgSaw&t=24s
### Containers
- Sequence containers(array and linked list): vector, deque, list, forward list, array
  - don't have find() member function(use algorithm std::find)
- Associate Containers(binary tree): set, multiset, map, multimap
  - always sorted, default criteria is <
  - no push_back(), push_front()
  - what does associate mean? actually if comes from map, which means a value associated with a key. for set/multiset, just think it as value == key
- Unordered Containers(hash table): unordered set/multiset, unordered map/multimap
  - hash_function, bucket, entry list
  - hash collision => performance degrade
  - Properties of Unordered containers:
    - fastest search/insert at any place:O(1)
      associative container takes O(logn)
      vector, deque taks O(n)
      list taks O(1) to insert, O(n) to search
    - Unordered set/multiset: element value cannot be changed.
    - Unordered map/multimap: element key cannot be changed.
- Container Adaptor
   - Provide a restricted interface to meet special needs
   - Implemented with fundamental container classes
     - Stack: LIFO, push(), pop(), top()
     - queue: FIFO, push(), pop(), front(), back()
     - priority queue: first item always has the highest priority, push(), pop(), top() 
- Another way of categorizing containers:
    - Array based containers:vector, deque, Note:Array based containers invalidates pointers: native pointers, iterators, references. **due to memory move/expand**
    ```
    vector<int> vec{1,2,3,4};
    int* p = &vec[3]; // p points to 3
    vec.insert(vec.begin(), 0);
    std::cout << *p << std::endl; //2, or ?
    ```
    - Node based containers: list + associative containers + unordered containers
- common member functions of all containers:
  - .empty()
  - .size()
  - copy constructor
  - .clear()  //remove all items in container
  - .swap() 
### Iterators and Algorithms
- Iterators:
  - Random access iterator: vector, deque, array
     > ++iter, --iter, iter1 > iter2, iter+n, iter-n.(++iter is faster than iter++ because it doesn't have to return the old value)
  - Bidirectional iterator: list, set/multiset, map/multimap
    > ++iter, --iter
  - forward iterator: forward_list
    > ++iter
  - Unordered containers provide "at least" forward iterators.
  - Input iterator:read and process value while iterating forward, read
   > int x= *iter 
  - Output iterator:output values while iterating forward, write
   > *itr = 100;