#include <emscripten.h>
#include <thread> 
#include <stdio.h>
#include <stdbool.h>

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

  printf("Started std threads.\n");
}

EMSCRIPTEN_KEEPALIVE
void stopThreads()
{
  g_quit = true;
  g_fib_thread.join();
  g_prime_thread.join();

  printf("Joined std Threads\n");
}

}