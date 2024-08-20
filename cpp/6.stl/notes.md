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
- common member functions of all containers:
  - .empty()
  - .size()
  - copy constructor
  - .clear()  //remove all items in container
  - .swap() 