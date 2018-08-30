#include <emscripten.h>
#include <pthread.h> 

EMSCRIPTEN_KEEPALIVE
int fib_ww(int n) {
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

EMSCRIPTEN_KEEPALIVE
void nprimes_ww(int N) {

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