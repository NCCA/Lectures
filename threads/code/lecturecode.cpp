//sample(fork1)
#include <cstdlib>
#include <iostream>
#include <unistd.h>


void error()
{
  std::cout<<"Error \n";
}

void child()
{
  std::cout<<"In child\n";
}

void parent()
{
  std::cout<<"In Parent\n";
}

int main()
{

std::cout<<"Started main about to fork\n";

pid_t pid = fork();

switch (pid)
{
  case -1:
    /* an error occurred, i.e. no child process created */
    error();
  case 0:
    /* a return value of 0 means we're in the child process */
    child();
    break;  // or _exit()
  default:
    /* we're in the parent; pid is the child's process id */
    parent();
}
//end-sample

//sample(deamon)
#include <iostream>
#include <cstdlib>
#include <unistd.h>


int daemonInit()
{
// initialise the daemon using the standard fork
// for a good example see Advanced Programming
// in the UNIX Environment by Stevens
  pid_t pid;
  if ((pid = fork()) < 0)
  {
    return -1;
  }
  else if (pid != 0)
  {
    exit(EXIT_SUCCESS);
  }
	// create a new session
  setsid();

  return 0;
}

int main()
{
	daemonInit();
	while(1)
	{
		std::cout<<"ping\n";
    sleep(2);
	}
}
//end-sample

//sample(pthread1)
#include <iostream>
#include <cstdlib>
#include <array>
#include <pthread.h>

void *threadFunc(void *arg)
{
  for(int i=0; i<10; ++i)
  {
    std::cout<<"thread func "<<i<<' ';
    std::cout.flush();
  }
  std::cout<<'\n';
  return 0;
}

int main()
{
  std::array<pthread_t,8> threadID;
  for(auto &t : threadID)
  {
    pthread_create(&t,0,threadFunc,0);
  }

  // now join
  for(auto &t : threadID)
  {
    std::cout<<"*************************\n";
    pthread_join(t,0);
  }
  std::cout<<"###########################\n";
}
//end-sample

//sample(pthread2)
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <array>

struct argStruct
{
  int arg1;
  char arg2;
};


void *threadFunc(void *arg)
{
  struct argStruct *args = (argStruct *)arg;
  /*	std::cout<<"thread func \n";
  std::cout<<"Arg 1 "<<args->arg1<<'\n';
  std::cout<<"Arg 2 "<<args->arg2<<'\n';
  */
  printf("thread function %d %c \n",args->arg1,args->arg2);
  return 0;
}


int main()
{
  std::array<pthread_t,4> threadID;
  struct argStruct args;

  for(int i=0; i<4; ++i)
  {
    args.arg1=i;
    args.arg2='a'+i;
    pthread_create(&threadID[i],0,threadFunc,(void *)&args);
  }
  // now join

  for(auto &t : threadID)
  {
    pthread_join(t,0);
  }
}
//end-sample

//sample(pthread3)
#include <iostream>
#include <cstdlib>
#include <array>
#include <pthread.h>


struct argStruct
{
  int arg1;
  char arg2;
};


void *threadFunc(void *arg)
{
  struct argStruct *args = (argStruct *)arg;
  for(int i=0; i<100000; ++i)
  {
    printf("thread function %d %c \n",args->arg1,args->arg2);
  }
  return 0;
}

int main()
{
  std::array<pthread_t,4> threadID;
  std::array<struct argStruct,4> args;

  for(int i=0; i<4; ++i)
  {
    args[i].arg1=i;
    args[i].arg2='a'+i;
    pthread_create(&threadID[i],0,threadFunc,(void *)&args[i]);
  }
  // now join

  for(auto &t : threadID)
  {
    pthread_join(t,0);
  }
}
//end-sample

//sample(pthread4)
#include <iostream>
#include <cstdlib>
#include <array>
#include <pthread.h>

struct argStruct
{
  int arg1;
  char arg2;
};


void *threadFunc(void *arg)
{
  struct argStruct *args = (argStruct *)arg;
  printf("thread function %d %c \n",args->arg1,args->arg2);
  int ret=args->arg1+10;
  pthread_exit(reinterpret_cast<void *>(ret));
}


int main()
{
  std::array<pthread_t,4> threadID;
  std::array<struct argStruct,4> args;

  for(int i=0; i<4; ++i)
  {
    args[i].arg1=i;
    args[i].arg2='a'+i;
    pthread_create(&threadID[i],0,threadFunc,(void *)&args[i]);
  }
  // now join

  int ret;
  for(auto &t : threadID)
  {
    printf("join\n");
    pthread_join(t,(void **)&ret);
    printf("return %d\n",ret);
  }
}
//end-sample

//sample(racehazard1)
#include <iostream>
#include <cstdlib>
#include <memory>
#include <array>
#include <unistd.h>
#include <pthread.h>

std::unique_ptr<char []>sharedMem;
constexpr int SIZE=20;

void *starFillerThread(void *arg)
{
  while(1)
  {
  printf("Star Filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='*';
  sleep(2);
	}
}

void *hashFillerThread(void *arg)
{
  while(1)
  {
  printf("hash filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='#';
  sleep(2);
  }
}


void *consumerThread(void *arg)
{
  while(1)
  {
  printf("Consumer\n");
  for(int i=0; i<SIZE; ++i)
    printf("%c",sharedMem[i]);
  printf("\n");
  sleep(2);
  }
}

int main()
{
  sharedMem.reset(  new char[SIZE]);
  std::array<pthread_t,3> threadID;

  pthread_create(&threadID[0],0,starFillerThread,0);
  pthread_create(&threadID[1],0,hashFillerThread,0);
  pthread_create(&threadID[2],0,consumerThread,0);

  for(auto &t : threadID)
    pthread_join(t,0);
}

//end-sample

//sample(mutex1)
#include <iostream>
#include <cstdlib>
#include <memory>
#include <array>
#include <unistd.h>
#include <pthread.h>

std::unique_ptr<char []>sharedMem;
constexpr int SIZE=20;


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *starFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  printf("Star Filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='*';
  pthread_mutex_unlock(&mutex);
  sleep(2);
  }
}

void *hashFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  printf("hash filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='#';
  pthread_mutex_unlock (&mutex);
  sleep(2);
  }
}


void *consumerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  printf("Consumer\n");
  for(int i=0; i<SIZE; ++i)
    printf("%c",sharedMem[i]);
  pthread_mutex_unlock (&mutex);
  printf("\n");
  sleep(2);
  }
}

int main()
{
  sharedMem.reset(  new char[SIZE]);
  std::array<pthread_t,3> threadID;

  pthread_mutex_init(&mutex, 0);
  pthread_create(&threadID[0],0,starFillerThread,0);
  pthread_create(&threadID[1],0,hashFillerThread,0);
  pthread_create(&threadID[2],0,consumerThread,0);

  for(auto &t : threadID)
    pthread_join(t,0);

}
//end-sample

//sample(conwait)
#include <iostream>
#include <cstdlib>
#include <memory>
#include <array>
#include <pthread.h>
#include <unistd.h>

std::unique_ptr<char []>sharedMem;
constexpr int SIZE=20;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitConsume=PTHREAD_COND_INITIALIZER;


void *starFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  pthread_cond_wait(&waitConsume,&mutex);
  printf("Star Filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='*';
  pthread_mutex_unlock(&mutex);
  sleep(2);
  }
}

void *hashFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  pthread_cond_wait(&waitConsume,&mutex);
  printf("hash filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='#';
  pthread_mutex_unlock (&mutex);
  sleep(2);
  }
}


void *consumerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  printf("Consumer\n");
  for(int i=0; i<SIZE; ++i)
    printf("%c",sharedMem[i]);
  pthread_mutex_unlock (&mutex);
  pthread_cond_signal(&waitConsume);
  printf("\n");
  sleep(2);
  }
}

int main()
{
  sharedMem.reset(  new char[SIZE]);
  std::array<pthread_t,3> threadID;

  pthread_mutex_init(&mutex, 0);
  pthread_cond_init(&waitConsume,0);

  pthread_create(&threadID[0],0,starFillerThread,0);
  pthread_create(&threadID[1],0,hashFillerThread,0);
  pthread_create(&threadID[2],0,consumerThread,0);

  for(auto &t : threadID)
    pthread_join(t,0);

}
//end-sample

//sample(conwait2)
#include <iostream>
#include <cstdlib>
#include <memory>
#include <array>
#include <pthread.h>

std::unique_ptr<char []>sharedMem;
constexpr int SIZE=20;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitFill=PTHREAD_COND_INITIALIZER;
pthread_cond_t waitConsume=PTHREAD_COND_INITIALIZER;


void *starFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  pthread_cond_wait(&waitConsume,&mutex);
  printf("Star Filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='*';
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&waitFill);

  }
}

void *hashFillerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  pthread_cond_wait(&waitConsume,&mutex);
  printf("hash filler\n");
  for(int i=0; i<SIZE; ++i)
    sharedMem[i]='#';
  pthread_mutex_unlock (&mutex);
  pthread_cond_signal(&waitFill);
  }
}


void *consumerThread(void *arg)
{
  while(1)
  {
  pthread_mutex_lock (&mutex);
  pthread_cond_signal(&waitConsume);
  pthread_cond_wait(&waitFill,&mutex);

  printf("Consumer\n");
  for(int i=0; i<SIZE; ++i)
    printf("%c",sharedMem[i]);
  pthread_mutex_unlock (&mutex);
  printf("\n");
  }
}

int main()
{
  sharedMem.reset(  new char[SIZE]);
  std::array<pthread_t,3> threadID;
  pthread_mutex_init(&mutex, 0);
  pthread_cond_init(&waitConsume,0);
  pthread_cond_init(&waitFill,0);

  pthread_create(&threadID[0],0,starFillerThread,0);
  pthread_create(&threadID[1],0,hashFillerThread,0);
  pthread_create(&threadID[2],0,consumerThread,0);

  for(auto &t : threadID)
    pthread_join(t,0);
}

//end-sample

//sample(qthread1)
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore/QThread>

class MyThread : public QThread
{
  Q_OBJECT
public:
  explicit MyThread(QObject *parent = 0,int _v=0);

protected :
  void run();
  int data;
  
signals:
  
public slots:
  
};

#endif // MYTHREAD_H
//end-sample

//sample(qthread2)
#include "MyThread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent, int _v) :
  QThread(parent)
{
  data=_v;
}


void MyThread::run()
{
  while(1)
  {
    data++;
    qDebug()<<"running thread "<<data;
    sleep(2);
  }
}

//end-sample

//sample(qthread3)
#include <QApplication>
#include "MyThread.h"
int main(int argc, char **argv)
{
  QApplication a(argc, argv);
  MyThread t;
  t.start();
  MyThread v(NULL,99);
  v.start();
  return a.exec();
}
//end-sample

//sample(cpp11thread1)
#include <iostream>
#include <thread>
#include <cstdlib>

void hello()
{
  std::cout<<"hello from thread\n";
}

int main()
{
  auto nThreads=std::thread::hardware_concurrency();
  std::cout<<"num threads "<<nThreads<<'\n';
  std::thread t(hello);
  t.join();

  return EXIT_SUCCESS;
}

//end-sample

//sample(cpp11thread2)
#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>

std::mutex g_print;
void task()
{
    g_print.lock();
    std::cout << "task id=" << std::this_thread::get_id() << '\n';
    g_print.unlock();
}

int main()
{
    std::vector<std::thread> threads(5);

    for(auto &t : threads)
    {
        t=std::thread(task);
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    return EXIT_SUCCESS;
}
//end-sample

//sample(race)
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int g_counter=0;

void run(int runs)
{
  std::cout<<"Thread " << std::this_thread::get_id()<<" is running\n";
  for(int i=0; i<runs; ++i)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%4));
    g_counter++;
  }
}


int main(int argc, char **argv)
{
  int N = atoi(argv[1]);
  int runs= atoi(argv[2]);
  std::thread *t[N];
  for(int i=0; i<N; ++i)
  {
    t[i]=new std::thread(run,runs);
  }
  for(int i=0; i<N; ++i)
  {
    t[i]->join();
  }
  std::cout<<g_counter<<'\n';

}
//end-sample

//sample(lockguard)
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>

int g_counter=0;
std::mutex gcountermutex;  // protects counter
void run(int runs)
{
  std::lock_guard<std::mutex> lock(gcountermutex);
  std::cout<<"Thread " << std::this_thread::get_id()<<" is running\n";
  for(int i=0; i<runs; ++i)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%4));
    g_counter++;
  }
}


int main(int argc, char **argv)
{
  int N = atoi(argv[1]);
  int runs= atoi(argv[2]);
  std::thread *t[N];
  for(int i=0; i<N; ++i)
  {
    t[i]=new std::thread(run,runs);
  }
  for(int i=0; i<N; ++i)
  {
    t[i]->join();
  }
  std::cout<<g_counter<<'\n';
}
//end-sample

//sample(logger1)
#ifndef LOGGER_H_
#define LOGGER_H_
#include <memory>
#include <cstdarg>
#include <iostream>
#include <ostream>
#include <fstream>

/// @brief logger class for writing to stream and file.
namespace nccalog
{
  enum class Colours{NORMAL,RED,GREEN ,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};
  enum class TimeFormat{TIME,TIMEDATE,TIMEDATEDAY};
  class NCCALogger
  {
    private:
      NCCALogger();
      ~NCCALogger();
      NCCALogger(const NCCALogger &)=delete;
      NCCALogger & operator=(const NCCALogger &)=delete;
    public :
      static NCCALogger &instance();
      void logMessage(const char* fmt, ...);
      void logError(const char* fmt, ...);
      void logWarning(const char* fmt, ...);
      void enableLogToFile();
      void disableLogToFile();
      void enableLogToConsole();
      void disableLogToConsole();
      void enableLogToFileAndConsole();
      void disableLogToFileAndConsole();
      void setLogFile(const std::string &_fname);
      void setColour(Colours _c);
      void enableLineNumbers();
      void disableLineNumbers();
      void enableTimeStamp();
      void disableTimeStamp();
      void disableColours();
      void enableColours();
      void setLineNumberPad(unsigned int i);
      void setTimeFormat(TimeFormat _f);

    private :
      class Impl;
      std::unique_ptr<Impl> m_impl;


  };

} // end namespace

#endif
//end-sample

//sample(logexample)
#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Logger.h"


void task()
{
  nccalog::NCCALogger::instance().setColour(nccalog::Colours::RED);
  for(int i=0; i<4; ++i)
  nccalog::NCCALogger::instance().logMessage(  "task %x\n" ,std::this_thread::get_id() );
}

int main()
{
  std::vector<std::thread> threads;

  for(int i = 0; i < 5; ++i)
  {
    nccalog::NCCALogger::instance().setColour(nccalog::Colours::CYAN);
    nccalog::NCCALogger::instance().logWarning("creating thread %d\n",i);
    threads.push_back(std::thread(task));
  }
  int i=0;
  for(auto& thread : threads)
  {
    nccalog::NCCALogger::instance().setColour(nccalog::Colours::YELLOW);
    nccalog::NCCALogger::instance().logWarning("Joining thread %d\n",i++);
    thread.join();
  }

  return EXIT_SUCCESS;
}
//end-sample

//sample(build)
#!/bin/bash
clang++ -std=c++11 $1  -g -I../LoggerC++11 -L../LoggerC++11 -lNCCALogger -I/usr/local/include
//end-sample

//sample(functional)
#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <chrono>
#include <functional>

#include "Logger.h"

void foo(const std::string  &a, const std::string &b)
{
  while(1)
  {
    nccalog::NCCALogger::instance().setColour(nccalog::Colours::RED);

    nccalog::NCCALogger::instance().
    logMessage("foo(str,str) ID %d value %s %s \n"
    ,std::this_thread::get_id(),a.c_str(),b.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
void foo(int a)
{
  while(1)
  {
    nccalog::NCCALogger::instance().setColour(nccalog::Colours::YELLOW);		
    nccalog::NCCALogger::instance().logMessage("foo(int) ID %d value %d \n"
    ,std::this_thread::get_id(),a);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));		
  }
}

void foo(double a)
{
  while(1)
  {
    nccalog::NCCALogger::instance().setColour(nccalog::Colours::BLUE);

    nccalog::NCCALogger::instance().logMessage("foo(double) ID %d value %f\n"
    ,std::this_thread::get_id(),a);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));		
  }
}


int main()
{
  std::vector<std::thread> threads;
  threads.reserve(4);
  nccalog::NCCALogger::instance().setColour(nccalog::Colours::CYAN);
  nccalog::NCCALogger::instance().logWarning("creating thread String Function\n");


  auto funca = std::bind<void(int)>(foo,1);
  threads.emplace_back(funca);

  auto funcb = std::bind<void(double)>(foo,0.002);
  threads.emplace_back(funcb);

  std::string a="hello";
  std::string b=" c++ 11 threads";
  auto funcs = std::bind<void(const std::string &,const std::string &)>(foo,a,b);
  threads.emplace_back(funcs);

  using namespace std::placeholders;  // for _1, _2, _3...
  auto funcs2 = std::bind<void(const std::string &,const std::string &)>(foo,_1,_2);
  threads.emplace_back(funcs2,"placeholders","are cool");
  std::for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));
  return EXIT_SUCCESS;
}
//end-sample

//sample(method)
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <string>
#include <functional>

#include "Logger.h"


class Foo
{
  public :
    Foo(int id):m_id(id){}
    void foo(const std::string  &a, const std::string &b)
    {
    while(1)
      nccalog::NCCALogger::instance().logMessage("foo(str,str) %d ID %d value %s %s \n"
      ,m_id,std::this_thread::get_id(),a.c_str(),b.c_str());
    }

  void foo(int a)
  {
    while(1)
      nccalog::NCCALogger::instance().logMessage("foo(int) %d ID %d value %d \n"
      ,m_id,std::this_thread::get_id(),a);
  }

  void foo(double a)
  {
    while(1)
      nccalog::NCCALogger::instance().logMessage("foo(double) %d ID %d value %f\n"
      ,m_id,std::this_thread::get_id(),a);
  }
  private :
    int m_id;

};

int main()
{
  std::vector<std::thread> threads;
  threads.reserve(6);
  nccalog::NCCALogger::instance().setColour(nccalog::Colours::CYAN);
  nccalog::NCCALogger::instance().logWarning("creating thread String Function\n");
  std::shared_ptr<Foo> pFoo(new Foo(10));
  Foo b(20);


  auto funca = std::bind( static_cast<void (Foo::*)( int )>(&Foo::foo),b,2);
  threads.emplace_back(funca);

  auto funcb = std::bind( static_cast<void (Foo::*)( int )>(&Foo::foo),pFoo.get(),99);
  threads.emplace_back(funcb);

  auto funcc = std::bind( static_cast<void (Foo::*)( double )>(&Foo::foo),b,2.23);
  threads.emplace_back(funcc);

  auto funcd = std::bind( static_cast<void (Foo::*)( double )>(&Foo::foo),pFoo,9.9);
  threads.emplace_back(funcd);

  std::string sa="hello";
  std::string sb=" c++ 11 threads";
  auto funce = std::bind( static_cast<void (Foo::*)( const std::string &,const std::string & )>
  (&Foo::foo),b,sa,sb);
  threads.emplace_back(funce);
  auto funcf = std::bind( static_cast<void (Foo::*)( const std::string &,const std::string & )>
  (&Foo::foo),pFoo.get(),sa,sb);
  threads.emplace_back(funcf);

  std::for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));

  return EXIT_SUCCESS;
}
//end-sample

//sample(reference)
#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <functional>

#include "Logger.h"

class Foo
{
public :
  Foo(int id):m_id(id){}

  void mutate(int &io_b)
  {
    io_b+=m_id;
  }

private :
  int m_id;

};

int main()
{
  std::vector<std::thread> threads;
  threads.reserve(2);
  nccalog::NCCALogger::instance().setColour(nccalog::Colours::CYAN);
  nccalog::NCCALogger::instance().logWarning("creating thread String Function\n");
  Foo *pFoo=new Foo(50);
  Foo b(99);

  int value1=10;
  int value2=20;	
  auto funca = std::bind( static_cast<void (Foo::*)( int &)>(&Foo::mutate),b,std::ref(value1));
  threads.emplace_back(funca);

  auto funcb = std::bind( static_cast<void (Foo::*)( int &)>(&Foo::mutate),pFoo,std::ref(value2));
  threads.emplace_back(funcb);


  nccalog::NCCALogger::instance().setColour(nccalog::Colours::YELLOW);
  nccalog::NCCALogger::instance().logWarning("Joining threads \n");
  std::for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));
  nccalog::NCCALogger::instance().logError("Value a %d Value b %d \n",value1,value2);

return EXIT_SUCCESS;
}
//end-sample

//sample(classoverload)
#include <thread>
#include <iostream>
#include <cstdlib>



class Task
{
public :

  Task(){m_id=99;}
  Task(int _t) : m_id(_t){;}

  void operator()() const
  {
    std::cout<<"class operator called "<<m_id<<'\n';
  }

  private :
    int m_id;
};


int main()
{
  Task t;
  unsigned long const nThreads=std::thread::hardware_concurrency();
  std::cout<<"num threads "<<nThreads<<"\n";
  std::thread thread( (Task(2)));
  thread.join();

  return EXIT_SUCCESS;
}
//end-sample

//sample(future1)
#include <thread>
#include <future>
#include <iostream>

void func(std::promise<int> && p) 
{
  p.set_value(99);
}


int main()
{
  std::promise<int> p;
  auto f = p.get_future();
  std::thread t(&func, std::move(p));
  t.join();
  int i = f.get();
  std::cout<<i<<'\n';
}
//end-sample

//sample(async)
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <numeric>


const static unsigned int size=100000000;

int sumVect(const std::vector<int>& v)
{
  std::cout<<"sumVect\n";
  int sum=0;
  for(auto i : v)
    sum += i;
  return sum;
}

int sumVectLambda(const std::vector<int>& v)
{
  std::cout<<"sumLambda\n";
  int sum=0;
  for_each(std::begin(v),std::end(v), [&sum](int x) {sum += x; });
  return sum;
}
int main()
{
  std::vector <int> data(size);
  std::iota(std::begin(data),std::end(data),0);

  auto res1 = std::async(sumVect,data);
  auto res2 = std::async(sumVectLambda,data);
  std::cout<<"start timer\n";
  auto t0 = std::chrono::high_resolution_clock::now();
  auto a=res1.get();
  auto b=res2.get();
  auto t1 = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds totalMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  std::cout<<"using standard vector "<<a<<" "<<b<<" took "<<totalMs.count()<<" Ms \n";
  return EXIT_SUCCESS;
}
//end-sample

//sample(atomic)
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

class Counter 
{
  public :

    Counter() =default;

    void increment(){ ++m_value;}

    void decrement(){ --m_value;}

    int get()
    {
      return m_value.load();
    }

  public :
    std::atomic<int> m_value={0};

};

int main()
{
  Counter counter;

  std::vector<std::thread> threads;
  for(int i = 0; i < 10; ++i)
  {
    threads.push_back(std::thread([&counter]()
    {
      for(int i = 0; i < 500; ++i)
      {
      counter.increment();
      }
    }
    ));
  }

  std::for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));

  std::cout << counter.get() << '\n';

  return 0;
}
//end-sample

//sample(threadLocal1)
#include <thread>
#include <iostream>
#include <cstdlib>

thread_local int i=0;

void foo(int*p)
{
  *p=42;
}

int main()
{
  i=9;
  std::thread t(foo,&i);
  t.join();
  std::cout<<i<<'\n';
}
//end-sample

//sample(threadLocal2)
#include <thread>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Logger.h"

class Counter
{
  public :
    void increment() { ++m_count; }
    ~Counter()
    {
      nccalog::NCCALogger::instance().logWarning("Thread %d called %d times \n",std::this_thread::get_id() ,m_count	);
    }
  private :
    unsigned int m_count = 0;
};

thread_local Counter c;

void threadTask()
{
  c.increment();
}

int main()
{
  std::vector<std::thread> threads;
  for(int i=0; i<10; ++i)
    threads.push_back(std::thread(threadTask));

  for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));
}	
//end-sample