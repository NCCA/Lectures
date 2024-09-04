# Systems Programming
Jon Macey 
jmacey@bournemouth.ac.uk

---

## What is systems programming?

- In the context of these lectures I will use "systems programming" to mean programmign elements of the OS and more low level programming
- In particular I will focus on Linux programming
  - using elements of the standard C library
- We will also look at using python 

--

### [Advanced Programming in the UNIX Environment](https://en.wikipedia.org/wiki/Advanced_Programming_in_the_Unix_Environment)

- This is the classic text on the subject
  - now in the 3rd edition
- Covers many topics 
  - I/O (files, directories)
  - Processes and Users
  - Threads, Signals and IPC
  - Networking

--

## System calls

<image src="images/arch.png" width=30%>

- allow us to interact with the OS / Kernel usually from the standard C library 
- pthreads for thereading
- An executing instance of a program is called a process and has an id

--


## Programs and Processes

- Program is an executable stored on the disk
- A program is read into memory and is executed by the kernel as a result of one of the seven exec functions (usually invoked from the terminal or double click)

--

## [Simple Process](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture6Systems/Processes/process.cpp)

```c++
#include <cstdlib>
#include <unistd.h>
#include <iostream>
int main()
{
  std::cout << "Process id is " << getpid() << '\n';
  std::cout << "User ID " << getuid() << '\n';
  std::cout << "Group ID " << getgid() << '\n';
  return EXIT_SUCCESS;
}
```
- This program prints out the process id as well as the user and group ids.

--

## [Process 2](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture6Systems/Processes/procloop.cpp)

```c++
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <cmath>
int main()
{
  while (true)
  {
    std::cout << "Process id is " << getpid() << '\n';
    // do some work so it shows in top
    int sum;
    for (size_t i = 1; i < 100000; ++i)
      sum += sqrt(i);
    sleep(10);
  }
  return EXIT_SUCCESS;
}
```

- we can use the linux kill program with the pid to kill our process

--

## [Signals](https://man7.org/linux/man-pages/man7/signal.7.html) 

- The kill program sends signals to a process

| Signal Number | Signal Name |
|---------------|-------------|
|   1 |      HUP (hang up) |
|   2 |      INT (interrupt) |
|   3 |      QUIT (quit)     |
|   6 |      ABRT (abort)    |
|   9 |      KILL (non-catchable, non-ignorable kill) |
|  14 |     ALRM (alarm clock) |
|  15 |     TERM (software termination signal) |

--

## [signal.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture6Systems/Processes/signal.cpp)

```c++
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <cmath>

int g_count = 0;
void sig_handler(int signum)
{
  std::cout << "Got Signal " << signum << '\n';
  if (signum == SIGHUP)
  {
    std::cout << "here is my number" << g_count << '\n';
    exit(EXIT_SUCCESS);
  }
  else if (signum == SIGINT)
  {
    std::cout << "stop interupting!\n";
  }
}
int main()
{
  signal(SIGHUP, sig_handler); // Register signal handler
  signal(SIGINT, sig_handler); // Register signal handler

  while (true)
  {
    std::cout << "Process id is " << getpid() << '\n';
    // do some work so it shows in top
    g_count++;
    sleep(10);
  }
  return EXIT_SUCCESS;
}
```

--

## [signal_test.py](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture6Systems/Processes/signal_test.py)

- we can capture signals in python in a similar way as C/C++

```python
#!/usr/bin/env python

import os
import signal
import time


def sig_handler(signum, frame):
    print(f"got signal {signum} {frame}")


if __name__ == "__main__":
    signal.signal(signal.SIGHUP, sig_handler)
    signal.signal(signal.SIGINT, sig_handler)
    print(f"Running program pid is {os.getpid()}")
    while True:
        time.sleep(10)
        print(".")

```

---

## [std::gentenv](https://en.cppreference.com/w/cpp/utility/program/getenv) 

- when a program starts the system envrionment is passed to it
- we can use the function ```std::getenv``` to query the values
- the following program demonstrates this

--

## [env.cpp](https://github.com/NCCA/PipelineAndTD/blob/main/Lecture6Systems/Env/env.cpp)

```c++
#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
  std::cout << "Program starting \n";
  auto env = std::getenv("ENV_STARTUP");
  if (env == nullptr)
  {
    std::cout << "You need to set ENV_STARTUP\n";
    exit(EXIT_FAILURE);
  }
  else
  {
    std::cout << "Working dir is " << env << '\n';
  }
  return EXIT_SUCCESS;
}
```

```
export ENV_STARTUP=$PWD
```

--

## char **environ

- On linux systems we can use the **environ global variable from unistd.h
- There is also the option to have a 3rd parameter to main 

```
int main(int arc, char **argv, char **environ)
```
- These values contain KEY=VALUE and need to be parsed

--

## [os.environ](https://docs.python.org/3/library/os.html)

- presented as a dictionary for easy lookup

```python
#!/usr/bin/env python

import os
import sys

if __name__ == "__main__":

    if os.environ.get("ENV_STARTUP") is None:
        print("Environment ENV_STARTUP not set")
        sys.exit(os.EX_CONFIG)
    else:
        print(f" working dir {os.environ['ENV_STARTUP']} ")
```

---

## Filesystems

- file systems are complex and there are many different filesystem types
  - ext4,FAT,NTFS,exFAT,HFS(+),XFS
- Each of these have their own interface / API's
- however to the programmer we need transparent access
- The C standard libraries have low level interfaces to file systems
- Using extra libraries we can extend this.

--

## [```import os```](https://docs.python.org/3.6/library/os.html#files-and-directories)

- The os module has a number of filesystem functions
- many of these allow us to interact with the filesystem similar to the commands we use in the shell

```python
#!/usr/bin/env python

import os
import random
import string

# grab our current directory
pwd = os.getcwd()
# first make a director called tmp and change into it
try:
    os.mkdir("tmp")
except FileExistsError:
    print("directory already exists")
os.chdir("tmp")

# make some random files note using the os.open method
# for demonstration purposes
for i in range(0, 10):
    file = os.open(f"tmpfile{i}.txt", os.O_RDWR | os.O_CREAT)
    rand_text = "".join(
        random.choices(
            string.ascii_uppercase + string.digits, k=random.randint(10, 200)
        )
    )
    os.write(file, rand_text.encode())
    os.close(file)
# change back to original directory and walk the subdirs
os.chdir(pwd)
# listdir gets a list
for file in os.listdir("tmp"):
    print(f"files {file}")

# scandir can be better as it returns a DirEntry
for file in os.scandir("tmp"):
    print(f"{file.name} {file.path}")
    print(f"{file.stat()}")
# Now tidy up
for file in os.scandir("tmp"):
    os.remove(file.path)
os.removedirs("tmp")

```

--

## [pathlib](https://docs.python.org/3/library/pathlib.html)

- One of the main issues with low level file system operations is the different OS have different commands
- To overcome this there are different libraries to help with this

```python
#!/usr/bin/env python
import pathlib

path = pathlib.Path.cwd()
print(path)
print(f"name is {path.name}")
Windows = pathlib.PureWindowsPath(r"C:\Users\jmacey/test.py")
print(Windows, type(Windows))
for p in pathlib.PurePosixPath(Windows).parts:
    print(p)

print(f"name is {Windows.name}")
print(f"suffixes {Windows.suffixes}")

# Join is useful

folder = pathlib.Path.home().joinpath("scripts", "test.py")
print(folder)

```


--

## [shutil](https://docs.python.org/3/library/shutil.html)

- high level operations on files and collections of files. 
- functions are provided which support file copying and removal. 
- Some meta-data is not copied (depending on FS)

```python
#!/usr/bin/env python

import os
import shutil

os.system("tar vfxz BaseMayaProject.tgz")

shutil.copytree("BaseMayaProject", "NewMayaProject")
shutil.rmtree("BaseMayaProject")
```

---

# [```os.system()```](https://docs.python.org/3/library/os.html#os.system)

- this function executes a command in a subshell. 
- This is implemented by calling the Standard C function system(), and has the same limitations.
- This includes inheriting environments and having no control over ```stdin``` and ```stdout```
- Whilst easy to use for simple examples like the previous version it's use is discouraged

--

## [```subprocess```](https://docs.python.org/3/library/subprocess.html)

- The subprocess module allows you to spawn new processes, connect to their input/output/error pipes, and obtain their return codes.
- It should be preferred over the ```os.system``` call

```python
#!/usr/bin/env python

import subprocess

subprocess.run("./run.py")

subprocess.run(["./run.py", "11"])

output = subprocess.run(["./run.py", "2"], capture_output=True)
print("Captured output ")
print(output)
```

--

## [```popen```](https://man7.org/linux/man-pages/man3/popen.3.html)

- The popen() function opens a process by creating a pipe, forking, and invoking the shell.  
- This allows us to then read and write data to the process as if it were a file
- This is the standard way of communicating with a process and used extensively in both C/C++ and python

--

## [ffmpeg](https://ffmpeg.org/)

- ffmpeg can read input from stdin using the flag ```-i -``` 
- In this example I open a process and write to it to generate video frames for encoding

```python
#!/usr/bin/env python
import platform
import random
import subprocess
import sys

sys.path.insert(0, "../ByteImage")
import ByteImage


def main():
    if platform.system() == "Darwin":
        ffmpeg = "/Applications/ffmpeg"
    else:
        ffmpeg = "ffmpeg"  # it should be in the path
    # fmt:off
    command = [
        ffmpeg,"-f","rawvideo","-pixel_format",
        "rgba", "-video_size", "400x400", "-framerate",
        "24", "-i", "-", "-vcodec", "mpeg4", "-y", "movie.mp4",
    ]
    # fmt:on

    # going to create our pipe / process
    pipe = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        # stdout=subprocess.DEVNULL,
        # stderr=subprocess.DEVNULL,
        bufsize=10**8,
    )

    rx = random.randint
    img = ByteImage.ByteImage(400, 400, 255, 0, 0, 255)

    for i in range(0, 200):
        img.clear(255, 255, 255)
        cx = rx(1, img.width)
        cy = rx(1, img.height)
        for x in range(0, 1000):
            img.line(
                cx,
                cy,
                rx(1, img.width - 1),
                rx(1, img.height - 1),
                rx(0, 255),
                rx(0, 255),
                rx(0, 255),
            )
        pipe.stdin.write(img.pixels)

if __name__ == "__main__":
    main()

```

---

## [FiFo](https://man7.org/linux/man-pages/man7/fifo.7.html)

- first-in first-out special file, named pipe
  - it is accessed as part of the filesystem
  - It can be opened by multiple processes for reading or writing.
- When processes are exchanging data via the FIFO, the kernel passes all data internally without writing it to the filesystem.
- we use the unix mkfifo command to generate one (works for C/C++ as well as python)

--

## [```os.mkfifo()```](https://docs.python.org/3/library/os.html#os.mkfifo)

- here I open a fifo and loop and read from it (server.py)

```python
#!/usr/bin/env python

import errno
import os
import signal
import sys

FIFO = "mypipe"


def sig_handler(signum, frame):
    if signum in [signal.SIGHUP, signal.SIGINT]:
        print("stopping server and removing fifo")
        os.remove(FIFO)
        sys.exit(os.EX_OK)


def main():

    try:
        os.mkfifo(FIFO)
    except OSError as oe:
        if oe.errno != errno.EEXIST:
            raise
    print(f"use ctrl + c to stop {os.getpid()}")

    signal.signal(signal.SIGHUP, sig_handler)
    signal.signal(signal.SIGINT, sig_handler)
    while True:
        print("start while")
        with open(FIFO) as fifo:
            print("Open")
            while True:
                print("reading")
                data = fifo.read()
                print(f"read {len(data)} {type(data)}")
                if len(data) == 0:
                    print("break")
                    break
                print(f"out")


if __name__ == "__main__":

    main()

```

--

## client.py

- This code writes to the FIFO, we can also cat or echo into the named pipe

```python
#!/usr/bin/env python

import errno
import os

FIFO = "mypipe"

try:
    os.mkfifo(FIFO)
except OSError as oe:
    if oe.errno != errno.EEXIST:
        raise

with open(FIFO, "w") as fifo:
    for i in range(0, 100):
        fifo.write(f"{i}\n")

```

--

## [ImageFIFIO](https://github.com/NCCA/PipelineAndTD/tree/main/Lecture6Systems/ImageFIFO)

- This demo uses the same process but uses a thread in PyQt to process the pipe

<image src="images/gui.png" width=60%>

---

# [Shared Memory](https://en.wikipedia.org/wiki/Shared_memory)

- Most operating systems have API's for shared memory
- POSIX operating systems use the ```shm_open``` functions 
- Python wraps this into a library using the ```multiprocessing``` module

--

### [multiprocessing.shared_memory](https://docs.python.org/3/library/multiprocessing.shared_memory.html#module-multiprocessing.shared_memory)

- The typical process is to allocate a block of memory with a name
- Other process will map to this using the same name
  - Note synchornisation is not automatic and the user needs to do this

```python
from multiprocessing import shared_memory
shm = shared_memory.SharedMemory(
            create=True, size=100, name="imageMap")
```

```python
shm = shared_memory.SharedMemory(name="imageMap")

```

---

## Sockets

- As demonstrated in the previous example multiple connections to a fifo can cause issues
- Also the fifo must be on the same file system as both programs
- Sockets allow us to overcome this problem by using the network

--

## [python sockets](https://docs.python.org/3/library/socket.html)

- the  socket module provides an interface to the [Berkeley sockets API](https://en.wikipedia.org/wiki/Berkeley_sockets) or BSD Sockets
- again this will be similar to the C API (note C++ still doesn't have a network module)
- This is not the most secure system but good for local networking

--

## TCP vs UDP

- TCP is a connection-oriented protocol
- UDP is a connectionless protocol 
- UDP is a much faster, simpler / efficient protocol
- retransmission of lost data packets is only possible with TCP

--

## TCP

- Is reliable: Packets dropped in the network are detected and retransmitted by the sender.
-  Has in-order data delivery: Data is read by your application in the order it was written by the sender.

--



---


# References


- https://learning.oreilly.com/library/view/programming-python-4th/9781449398712/pt02.html
- https://realpython.com/python-sockets/
- 
