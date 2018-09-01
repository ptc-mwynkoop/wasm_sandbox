#include <emscripten.h>
#include <thread> 
#include <future>
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <type_traits>

int fib(int n) {
  int i, t, a = 0, b = 1;
  for (i = 0; i < n; i++) {
    t = a + b;
    a = b;
    b = t;
  }
  // call back into the Javascript layer, just to show how
  // EM_ASM({
  //   Module.fibCallback([$0]);
  // }, b);

  return b;
}

void nprimes(int N) {

  for (int i = 2; N > 0; ++i) {
    int isPrime = 1;
    for (int j = 2; j < i; ++j) {
      if (i % j == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime > 0) {
      --N;
    }
  }
}

std::thread g_fib_thread;
std::thread g_prime_thread;
std::future<int> g_fib_future;
std::future<int> g_prime_future;
bool g_quit = false;

void fib_thread_main(int n)
{
  printf("started fib thread\n");
  int run = 0;
  while(!g_quit && run++ < 1000)
  {
    int out = fib(n);
    EM_ASM({
      console.log('feedback from fib thread ' + [$0]);
    }, out);
  }

  printf("Exited fib calc at run %d\n", run);
}

void prime_thread_main(int n)
{
  printf("started prime thread\n");
  int run = 0;
  while(!g_quit && run++ < 1000)
  {
    nprimes(n);
    EM_ASM({
      console.log('prime thread finished a run');
    });
  }

  printf("Exited prime calc at run %d\n", run);
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
void startThreads(int n)
{
  g_quit = false;

  g_fib_thread = std::thread(fib_thread_main, n);
  g_prime_thread = std::thread(prime_thread_main, n);

  g_prime_future = std::async(std::launch::async, [n]{
    nprimes(n);
    return 1;
  });
  g_fib_future = std::async(std::launch::async, [n]{
    return fib(n);
  });

  printf("Started std threads.\n");

  std::cout << std::boolalpha
            << "Test C++14, check is_null_ptr : " 
            << std::is_null_pointer< decltype(nullptr) >::value 
            << std::endl;
}

EMSCRIPTEN_KEEPALIVE
void stopThreads()
{
  g_quit = true;
  g_fib_thread.join();
  g_prime_thread.join();

  printf("Joined std Threads\n");

  printf("Result of asyncs... %d, %d\n", g_fib_future.get(), g_prime_future.get());
}


EMSCRIPTEN_KEEPALIVE
void throwException()
{
  try {
    throw std::runtime_error("Test");
  }
  catch (std::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
}



}