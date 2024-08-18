###  Refer: https://www.youtube.com/watch?v=LL8wkskDlbs&t=43s
### Processes vs. Threads
### hardware concurrency
### data race and mutex
- use mutex to synchronize data access
- Never leak a handle of data to outside.
- Design interface appropriately
- mutex.lock()/mutex.unlock() may have problem if there's expcetion happens in between the 2 APIS call, it may never be unlocked, use std::lock_guard instead
### Avoiding Deadlock  
- Prefer locking single mutex
- Avoid locking a mutex and then calling a user provided function
- Use std::lock() to lock more than one mutex;
- Lock the mutex in same order.
### unique_lock and Lazy initialization
- std::once_flag, std::call_once
### condition variable
- spurious wake,  prediction
### Future, Promise and async()
- async() execute function in a different thread or in the same thread.
### callable objects
- std::function(callable, parames);
- std::async(callable, params);
- std::bind(callable, prarams);
- std::call_once(once_flag, callable, params);
### packaged_task
- package of task that can be transported to different place in the program and be executed over there.
- summary: 3 ways to get a future
  - pomise::get_future()
  - packaged_task::get_future()
  - async() returns a future