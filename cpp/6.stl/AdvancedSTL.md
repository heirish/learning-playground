### Containers member functions vs algorithms
- Member Functions with same name as in algorithm:
  ```
  //List
  void remove(const T); template<class Comp> void remove_if(Comp);
  void unique();        template<class Comp> void unique(Comp);
  void sort();          template<class Comp> void sort(Comp);
  void merge(list&);    template<class Comp> void merge(Comp);
  void reverse();

  //associative containers:
  size_type count(const T&) const;
  iterator find(const T&) const;
  iterator lower_bound(const T&) const; 
  iterator upper_bound(const T&) const; 
  std::pair<iterator, iterator> equal_range(const T&) const;
  //Note: they don't have generialized form, because comparison is defined by the container.

  //unordered container
  size_type count(const T&) const;
  iterator find(const T&) const;
  std::pair<iterator, iterator> equal_range(const T&) const;
  //Note: No generalized form; use hash function to search
  ```
- why? same function exist as member function and algorithm function?
  > same purpose, but they do things in a different way, they're not equal because one way is better than the other
  - there are duplicated functions between container's member functions and algorithm functions
  - in general, perfer member functions over algorithm functions with the same names.except
    - find of std::set, see next section **Equivalence vs Equality**
### Tricky reverse iterator
  reverse_iterator and iterator can be converted to each other,
  but they don't point to the same element, they're off by one item.
  iter -> riter: (-1), riter -> iter: (+1)
  ![](images/reverse_iterator.png)
  ```
  std::vector<int>::reverse_iterator ritr;
  std::vector<int>::iterator it;

  riter = std::vector<int>::reverse_iterator(it);
  it = riter.base();
  ```
### Equivalence vs Equality
  - find in std::set for algorithm and member function
    - algorithm std::find() looks for equality if (x==y)
    - std::set::find() looks for equivalence: if (!compare(x,y) && !compare(y,x))
  - GuideLines:
    - if the function is using operator "<"(compare) or it's like, it's checking equivalence, typically it's algorithm that works with sorted data, or a member function of a container with sorted data, such as associative container.
    - if the function is using operator "==" or it's like, it's checking equality, typically the data is not required to be sorted.
      ```
      //algorithm of equality
      std::search
      std::find_end
      std::find_first_of
      std::adjacent_search

      //algorithms of equivalence
      std::binary_earch
      std::includes
      std::lower_bound
      std::upper_bound
      ```
    - Summary: when using a function to search or remove certain element, make sure you understand the difference between equality and equivalence
### Removing elements
  - vector or deque: algorithm remove() followed by member function erase()
  - List: member function remove()
  - associative container or unordered container:erase()
  - remove and do something else?
    - sequence container and unordered container: `iter = c.erase(iter)`
    - associative container: `iter= c.erase(iter) or c.erase(iter++)`