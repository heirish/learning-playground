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
  - in general, perfer member functions over algorithm functions with the same names.