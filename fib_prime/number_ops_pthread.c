#include <emscripten.h>
#include <pthread.h> 
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

pthread_t g_fib_thread;
pthread_t g_prime_thread;
bool g_quit = false;
int g_n;

void* fib_thread_main(void* userData)
{
  printf("started fib thread\n");
  int n = *(int*)userData;
  int run = 0;
  while(!g_quit && run++ < 1000)
  {
    int out = fib(n);
    EM_ASM({
      console.log('feedback from fib thread ' + [$0]);
    }, out);
  }

  printf("Exited fib calc at run %d\n", run);
  return NULL;
}

void* prime_thread_main(void* userData)
{
  printf("started prime thread\n");
  int n = *(int*)userData;
  int run = 0;
  while(!g_quit && run++ < 1000)
  {
    nprimes(n);
    EM_ASM({
      console.log('prime thread finished a run');
    });
  }

  printf("Exited prime calc at run %d\n", run);
  return NULL;
}

EMSCRIPTEN_KEEPALIVE
void startThreads(int n)
{
  g_n = n;
  g_quit = false;

  int errno = pthread_create(&g_fib_thread, NULL, fib_thread_main, &g_n);
  if(errno != 0)
    printf("Unable to start pthread (fib), error %d\n", errno);

  errno = pthread_create(&g_prime_thread, NULL, prime_thread_main, &g_n);
  if(errno != 0)
    printf("Unable to start pthread (prime), error %d\n", errno);

  printf("Started pthreads.\n");
}

EMSCRIPTEN_KEEPALIVE
void stopThreads()
{
  g_quit = true;
  pthread_join(g_fib_thread, NULL);
  pthread_join(g_prime_thread, NULL);
}