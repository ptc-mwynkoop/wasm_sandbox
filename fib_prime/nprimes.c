#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE

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