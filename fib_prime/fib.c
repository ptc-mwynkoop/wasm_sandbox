#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int fib(int n) {
  int i, t, a = 0, b = 1;
  for (i = 0; i < n; i++) {
    t = a + b;
    a = b;
    b = t;
  }
  // call back into the Javascript layer, just to show how
  EM_ASM({
    Module.fibCallback([$0]);
  }, b);

  return b;
}