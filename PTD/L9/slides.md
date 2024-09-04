## Introduction to Threading
### Part 2 API's Design Patterns and Python

Jon Macey

jmacey@bournemouth.ac.uk

---

## std::thread

- we can use a lambda with [std::thread](https://en.cppreference.com/w/cpp/thread/thread)
- In this case the thread starts immediately and we use join to call the thread destructor

```c++
#include <thread>
#include <iostream>
#include "Logger.h"
#include <fmt/format.h>
#include <fmt/ostream.h>

int main()
{
  Logger::warning(fmt::format("Parent id {}", std::this_thread::get_id()));
  std::thread t1([]()
                 { Logger::info(fmt::format("In thread {}", std::this_thread::get_id())); });
}
```

--

## thread results

- We can capture a value in the lambda and use it in the thread

```c++
#include <thread>
#include <iostream>
#include "Logger.h"
#include <fmt/format.h>
#include <fmt/ostream.h>

int main()
{
  int sum = 0;

  Logger::warning(fmt::format("Sum is {}", sum));

  std::thread t([&]()
                {
                   Logger::info(fmt::format("In thread {}", std::this_thread::get_id()));
                   for (int i = 0; i < 100; ++i)
                     sum += i; 
                });
  t.join();
  Logger::info(fmt::format("Sum is {}", sum));
}
```


--

## race condition

- in the following example we get a race condition as counter is being accessed by the two threads
- this can cause different outcomes depending upon how the value is accessed
- On method of dealing with this is to use a mutex, however in some cases we can also use std::atomic


--

## [std::atomic<T>](https://en.cppreference.com/w/cpp/atomic/atomic)

- Each instantiation and full specialization of the std::atomic template defines an atomic type
- If one thread writes to an atomic object while another thread reads from it, the behavior is well-defined [(see memory model for details on data races)](https://en.cppreference.com/w/cpp/language/memory_model)
- std::atomic is neither copyable nor movable.

--

## using atomic

- [still a semantic data race](https://github.com/CppCon/CppCon2020/blob/main/Presentations/back_to_basics_concurrency/back_to_basics_concurrency__arthur_odwyer__cppcon_2020.pdf) 

```c++
#include <thread>
#include <iostream>
#include "Logger.h"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <chrono>
#include <atomic>
int main()
{
  auto endTime=std::chrono::steady_clock::now() + std::chrono::seconds(3);
  std::atomic<int> counter=0;
  Logger::warning(fmt::format("Counter is {}", counter));

  std::thread t([&]()
                {
                   Logger::info(fmt::format("In thread {}", std::this_thread::get_id()));
                   while(std::chrono::steady_clock::now()<endTime)
                    std::cout<<"from thread "<<counter++<<'\n';
                });
 
  while(std::chrono::steady_clock::now()<endTime)
        std::cout<<"main "<<counter++<<'\n';
  t.join();
  Logger::info(fmt::format("counter is {}", counter));
}
```


--

## Need a better pattern

- [Producer / Consumer or Bounded Buffer](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem) problem
- Different approaches we saw one last week using mutex / semaphores
- Or we can use a [std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic) with the [store](https://en.cppreference.com/w/cpp/atomic/atomic/store) and [load](https://en.cppreference.com/w/cpp/atomic/atomic/load) methods
- This is reliant on the [std::memory_order](https://en.cppreference.com/w/cpp/atomic/memory_order) specification

--

## [std::memory_order](https://en.cppreference.com/w/cpp/atomic/memory_order)

- std::memory_order specifies how memory accesses, including regular, non-atomic memory accesses, are to be ordered around an atomic operation. 
- when multiple threads simultaneously read and write to several variables, one thread can observe the values change in an order different from the order another thread wrote them. 

--

## A Broken example

- It is tempting to write code like this, however we will see this is not good

```c++
#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <iostream>
#include <random>
std::atomic<std::string*> ptr;
std::default_random_engine rng;
constexpr size_t size=20;

std::uniform_int_distribution<int> range(1,size);
std::unique_ptr<std::string> p ;
void producer()
{
  while(true)
  {
   p  = std::make_unique<std::string>(range(rng),'*');
    ptr.store(p.get(), std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
  }
}
void consumer()
{
    std::string clear(size,' ');
    std::string* str;
    while(true)
    {
      while (!(str = ptr.load(std::memory_order_consume))) ;
     
      std::cout<<clear<<'\r';
      std::cout<<*str<<'\r';
      std::cout.flush();
      
      std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}
 
int main()
{
    std::thread produce(producer);
    std::thread consume(consumer);
    produce.join(); 
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    consume.join();
}
```

--

## Problems

- the previous example works as short string optimization is kicking in and data is on the stack
- making the string larger will result in heap allocation and crashes
- We can re-allocate a pointer each time but this results in a memory leak
- We need a better solution (which requires more complex code / design)
  - We shall look at examples later

---

## [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)

- This allows us to do a "wait until" style sync
- Still need to use a mutex as we did in pthread demo
- This example demonstrates a simple [Pool](https://en.wikipedia.org/wiki/Object_pool_pattern) design pattern with more threads accessing than things in the pool.

--

## Pool example

```c++
#include <vector>
#include <thread>
#include <iostream>
#include "Logger.h"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <numeric>
#include <random>

struct Pool
{
  Pool(size_t _size)
  {
    things.resize(_size);
    std::iota(std::begin(things),std::end(things),0);
  }
  int getThing()
  {
    std::unique_lock<std::mutex> lock(mutex);
    while(things.empty())
    {
        Logger::debug("Waiting Lock");
        cv.wait(lock);
    }
    auto r=std::move(things.back()); // I know it's an int
    things.pop_back();
    return r;
  }

  void returnThing(int _t)
  {
    std::unique_lock<std::mutex> lock(mutex);
    things.push_back(_t);
    lock.unlock();
    Logger::error("calling Notify");
    cv.notify_one();
  }
  std::vector<int> things;
  std::mutex mutex;
  std::condition_variable cv;
};

int main()
{
  std::default_random_engine rng;
  std::uniform_int_distribution<int> sleep_for(500,1550);

  Pool pool(4);
  auto nThreads = std::thread::hardware_concurrency();
  Logger::info(fmt::format("Have {} threads",nThreads));
  std::vector<std::thread> workers(nThreads);
  for(auto &t : workers)
  {
    t=std::thread([&](){
      while(true)  
      {
        // grab thing from pool
        auto thing=pool.getThing();
        Logger::warning(fmt::format("Thread {} has thing {}",std::this_thread::get_id(),thing));
        // simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for(rng)));
        // return when done
        pool.returnThing(thing);
      }
    });
  }
  for(auto &t : workers)
    t.join();
}
```

---

## Threading in Python

- Python threading model is a little different than we have seen previously
- most implementations the different threads do not actually execute at the same time they merely appear to
- The CPython implementation of Python threading may not speed up all tasks. 
- This is due to the GIL that essentially limit one Python thread to run at a time.

--

## [Global Interpreter Lock (GIL)](https://wiki.python.org/moin/GlobalInterpreterLock)

- is a binary semaphore with a condition variable that protects access to Python objects (pthreads or windows threads)
- the GIL prevents race conditions and ensures thread safety
- GIL is required due to the memory reference counting model used by CPython
- Python single threaded performance is good, however multi-threaded may be slow.
- Basically [co-operative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking)

--

## Multiprocessor vs Multithreading

- If the GIL is causing issues we can use Multiprocessor
  - Each Python process gets its own Python interpreter and memory space so the GIL won’t be a problem
- Python has a multiprocessing module which lets us create processes easily
- if you have a CPU-bound problem, you should use the multiprocessing module
- If all else fails use a non CPython implementation (usually not a solution for us)

--

## thread1.py

```python
#!/usr/bin/env python
import logging
import threading
import time


def thread_function(name):
    logging.info(f"Thread {name}: starting")
    time.sleep(2)
    logging.info(f"Thread {name}: finishing")


if __name__ == "__main__":
    logging.basicConfig(
        format="%(asctime)s: %(message)s", level=logging.INFO, datefmt="%H:%M:%S"
    )
    logging.info("In Main creating thread")
    thread = threading.Thread(target=thread_function, args=(1,))
    logging.info("Main starting thread")
    thread.start()
    logging.info("Main waiting for finish")
    logging.info("Main finished")

```

--

## [threading](https://docs.python.org/3/library/threading.html)

- The Thread class represents an activity that is run in a separate thread of control. 
- There are two ways to specify the activity: 
  - by passing a callable object to the constructor
  - overriding the run() method in a subclass 
- No other methods (except for the constructor) should be overridden in a subclass. 
- We should only override the ```__init__()``` and ```run()``` methods of this class.

--

## daemon threads

- So far we have used daemon to mean a background process
- Python threading has a more specific meaning for daemon. 
- A daemon thread will shut down immediately when the program exits. 
- If a program is running Threads that are not daemons, then the program will wait for those threads to complete before it terminates.
- can use join to force wait for thread

--

## thread2.py

```python
#!/usr/bin/env python
import logging
import threading
import time


def thread_function(name):
    logging.info(f"Thread {name}: starting")
    time.sleep(2)
    logging.info(f"Thread {name}: finishing")


if __name__ == "__main__":
    logging.basicConfig(
        format="%(asctime)s: %(message)s", level=logging.INFO, datefmt="%H:%M:%S"
    )
    logging.info("In Main creating thread")
    thread = threading.Thread(target=thread_function, args=(1,), daemon=True)
    logging.info("Main starting thread")
    thread.start()
    #thread.join()
    logging.info("Main waiting for finish")
    logging.info("Main finished")

```

---

## multiple_threads.py

- we can use a list to contain multiple threads as follows

```python
#!/usr/bin/env python
import logging
import threading
import time


def thread_function(name, colour):
    logging.info(f"{colour}{name}: starting")
    time.sleep(2)
    logging.info(f"{colour}{name}: finishing")


if __name__ == "__main__":

    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

    num_threads = 4
    threads = list()
    colour = ["red", "green", "yellow", "blue"]
    for i in range(num_threads):
        logging.info(f"creating thread")
        thread = threading.Thread(
            target=thread_function,
            args=(f"Thread_{i}", f"\u001b[{i+30}m"),
        )
        threads.append(thread)
        thread.start()

    for i, thread in enumerate(threads):
        logging.info(f"\u001b[{i+30}mmain joining thread {i}")
        thread.join()
        logging.info(f"\u001b[{i+30}mmain thread {i} done")


```

--

## context managers

- ```with``` statement in Python will manage the context of a resource (open / close, lock unlock etc)
- creates a runtime context that allows you to run a group of statements under the control of a [context manager](https://docs.python.org/3/library/stdtypes.html#context-manager-types)
- We can use this with threading and locks as show in the next example

--

## [concurrent.futures](https://docs.python.org/3/library/concurrent.futures.html)

- Introduced in python 3.2
- asynchronous execution can be performed with threads, using ```ThreadPoolExecutor```
- separate processes can  use ```ProcessPoolExecutor```
- Both implement the same interface, which is defined by the abstract Executor class.

--

## futures.py

```python
#!/usr/bin/env python

import concurrent.futures
import logging
import time


def thread_function(message):
    logging.info(f"starting")
    time.sleep(2)
    logging.info(f"finishing")

if __name__ == "__main__":
    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
    num_threads = 12
    with concurrent.futures.ThreadPoolExecutor(max_workers=num_threads) as executor:
        executor.map(thread_function, range(num_threads))

```

--

## racehazard.py

- this example uses a shared resource to create a race hazard

```python
#!/usr/bin/env python

import concurrent.futures
import logging
import random
import time


class SharedResource:
    def __init__(self):
        self.value = 0

    def update_resource(self, name, value):
        logging.info(f"Thread {name} starting update")
        # simulate work with local variables to the class
        local_value = self.value
        local_value += value
        time.sleep(random.uniform(0, 10))  # simulate work
        # now assign after work
        self.value = local_value
        logging.info(f"Thread {name} finishing update")


if __name__ == "__main__":
    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.DEBUG, datefmt="%H:%M:%S")
    num_threads = 12
    resource = SharedResource()
    total = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=num_threads) as executor:
        for index in range(num_threads):
            r = random.randint(10, 200)
            total += r
            logging.info(f"Updating theread {index} with value {r}")
            # note the use of submit to pass values to the function
            executor.submit(resource.update_resource, index, r)
    logging.info(f"Testing update. Ending value is {resource.value} should be {total}")

```

--

## lock.py

- We can use a lock to ensure there is no race hazard

```python
#!/usr/bin/env python

import concurrent.futures
import logging
import random
import threading
import time


class SharedResource:
    def __init__(self):
        self.value = 0
        self._lock = threading.Lock()

    def update_resource(self, name, value):
        logging.info(f"Thread {name} starting update by acquiring lock")
        # simulate work with local variables to the class
        with self._lock:  # RAII
            local_value = self.value
            local_value += value
            time.sleep(random.uniform(0, 1))  # simulate work
            # now assign after work
            self.value = local_value
        logging.info(f"Thread {name} finishing update and releasing lock")


if __name__ == "__main__":
    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.DEBUG, datefmt="%H:%M:%S")
    num_threads = 12
    resource = SharedResource()
    total = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=num_threads) as executor:
        for index in range(num_threads):
            r = random.randint(10, 200)
            total += r
            logging.info(f"Updating theread {index} with value {r}")
            executor.submit(resource.update_resource, index, r)
    logging.info(f"Testing update. Ending value is {resource.value} should be {total}")
```

--

## lock2.py

- we can also use the acquire / release methods instead of a context manager

```python
#!/usr/bin/env python

import concurrent.futures
import logging
import random
import threading
import time

# create a global lock
g_lock = threading.Lock()


class SharedResource:
    def __init__(self):
        self.value = 0

    def update_resource(self, name, value):
        logging.info(f"Thread {name} starting")
        # simulate work with local variables to the class
        g_lock.acquire()  # no RAII
        logging.info(f"Thread {name} aquired lock")
        self.value += value
        time.sleep(random.uniform(0.1, 1))  # simulate work
        g_lock.release()
        logging.info(f"Thread {name} finishing update and releasing lock")


if __name__ == "__main__":
    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.DEBUG, datefmt="%H:%M:%S")
    num_threads = 12
    resource = SharedResource()
    total = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=num_threads) as executor:
        for index in range(num_threads):
            r = random.randint(10, 200)
            total += r
            logging.info(f"Updating theread {index} with value {r}")
            executor.submit(resource.update_resource, index, r)
    logging.info(f"Testing update. Ending value is {resource.value} should be {total}")

```

---

## stopping threads

- In the previous examples we stop using ctrl + c to stop it
- This is not the best way to terminate a program, instead we need to set a flag
- The following examples will show some different methods

--

## [```threading.Event()```](https://docs.python.org/3/library/threading.html#event-objects)

- The ```Event()``` class has a number of methods based about setting, getting and clearing an effective atomic flag
- We also have a ```wait(timeout)``` method which will block until the internal flag is true. 
- This is show in the following example

--

## stop_threads.py

```python
#!/usr/bin/env python
import logging
import random
import signal
import threading
import time


def thread_function(stop_event, name, colour):
    t = threading.currentThread()
    while not stop_event.wait(1):
        logging.info(f"{colour}{name}")
        time.sleep(random.randint(0, 10))
    logging.info(f"{colour}{name} Stopping")


if __name__ == "__main__":
    format = "%(message)s : %(asctime)s "
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

    num_threads = 4
    stop_event = threading.Event()
    threads = []
    for i in range(num_threads):
        logging.info(f"creating thread")
        thread = threading.Thread(
            target=thread_function,
            args=(stop_event, f"Thread_{i}", f"\u001b[{i+31}m"),
        )
        threads.append(thread)
        thread.start()
    logging.info("killing threads")
    time.sleep(40)
    stop_event.set()

    for t in threads:
        t.join()
```




---

## References
- Gerassimos Barlas. 2014. Multicore and GPU Programming: An Integrated Approach. Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.

- Peter Pacheco. 2011. An Introduction to Parallel Programming (1st ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA.
- https://bartoszmilewski.com/2014/02/26/c17-i-see-a-monad-in-your-future/

--

## References

- https://realpython.com/intro-to-python-threading
- https://realpython.com/python-gil/