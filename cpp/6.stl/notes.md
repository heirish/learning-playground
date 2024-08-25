### Algorithms-iterators-containters
https://www.youtube.com/watch?v=ltBdTiRgSaw&t=24s
### Containers
- Sequence containers(array and linked list): vector, deque, list, forward list, array
  - don't have find() member function(use algorithm std::find)
  - list: 很高效的切片插入 mylist1.splice(iter, mylist2, iter_a, iter_b) //O(1)
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
  - Every container has an iterator and a const_iterator
  - Iterator Functions: advance(iter, 5), distance(iter1, iter2) 
  - Iterator Adaptor (predefined iterator): A special, more powerful iterator
    - Insert iterator
    - Stream iterator
    - Reverse iterator
    - Move iterator(c++11)
- Algorithms: mostly loops
   - if there's for loop or while loop in your code, you should seriously consider replacing them with a function all from algorithm, make your code more efficient, less buggy, more readable, more clean
   - algorithm always process ranges in a half-open way: [begin, end)
   - std::copy, ensure there's enough space pre-allocated in destination iter.
   - algorithm with function: `std::find_if`
### Functors
- Functor expands the concept of function by saying anything behave like a function is a function.
- 不要与type conversion function混淆了
  ```
  void operator() (String str);//functor
  operator string(); //type conversion function
  ```
- Function Objets
- Benefits of functor:
  - Smart function: capabilities beyond operator(), It can remember state(member variable).
  - It can have its own type.
     - regular functions can only be defferenciated by their function signature, if two functions have the same function signatures, they have the same type.but two functors can be of different type event if they have the exact same functions signature.
- Build-in Functors
  - less, greater, greater_equal, less_equal, not_equal_to, logical_and, logical_not, logical_or, mutiplies, minus, plus, devide, modulus, negate
- Parameter Binder: std::bind
- convert regular function to a functor: std::function<>
- why do we need functor in STL？
  - without functor, associative containers will not work.
  `std::set<int>` is equivalent to `std::vect<int, std::less<int>>`, but what if we want to create a different set sorted in a differetn order?比如我想创建一个按最低位数字排序的set?
    ```
    bool lsb_less(int a, int b) {
      return (x%10) < (y%10);
    }
    class Lsb_less {
    public:
      bool operator()(int a, int b) {
        return (x%10) < (y%10);
      }
    };
    void test() {
      //will not compile, STL need a functor type instead of function
      //std::set<int, lsb_less> myset;
      std::set<int, Lsb_less> myset;
    }

    ```
  - Predicate functor: A functor or function that returns a boolean, does not modify data
    predicate is used for comparison or condition check.
    widely used in STL algorithm
    - 注：在有些algorithm中，针对同一个element, predicate可能不止被调用一次, 因此predicate最后是状态无关的