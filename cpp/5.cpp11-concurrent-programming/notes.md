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
