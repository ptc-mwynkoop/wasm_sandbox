

# WASM Exploration for Chalk
This project is a toy used to explore WASM as it relates to a 'Chalk in a web browser'
application.

One of the things of concern is Chalk's use of threads and WEBASM's lack of support for them. 
This project uses [Web Workers](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API) because they
are a way of making additional threads available to the browser.

We use [Emscripten](http://kripken.github.io/emscripten-site/) to produce the .wasm files.
# Build Instructions

These instructions assume you have Emscripten and Python 2.7 installed.
 
1. Build the .wasm and 'glue' files by running either *build.bat* or *build.sh*.
 
# Running Instructions
1. Launch a local web server to serve up the project files. Loading them directly from the filesystem wont work. I use python to run a local web server like this:
  ```python server.py```
 
2. Open a browser and load http://localhost:9000
 
3. Then open the developer tools so you can see the browser console as that is where all the program output appears.
 
4. Now click the ‘Go’ button and watch the console: you can see the Fibonacci calc runs more than once during the time the prime calculation completes.

 

# Pthread support

This project now supports pthreads, in order to use them, you must download [Firefox Nightly](https://www.mozilla.org/en-US/firefox/channel/desktop/#nightly) and enable the following option in `about:config`

```
javascript.options.shared_memory = true
```

Note that Pthreads are VERY FAST and are limited to 1000 iterations.  If you click the button twice very fast
to stop the threads, you should be able to stop one of them before it has completed all 1000 runs.  If we let
this go unbounded, it tends to crash the browser...

You can still use this app without Pthread support, but you will be limited to the Web Worker flow.

# STD Thread / Async support

Once Pthreads are enabled, we can run w/ STD thread support as well.  This project is not currently set up to
run them concurrently.  By default the project is set up for STD Threads, but to enable Pthreads, just swap the
javascript webassembly wrapper in index.html.
```html
  <!-- <script type="text/javascript" src="number_ops_pthread.js"></script> -->
  <script type="text/javascript" src="number_ops_stdthread.js"></script>
```

# Interesting Emscripten links / Additional Information

 [Browser Execution Environment](http://kripken.github.io/emscripten-site/docs/api_reference/emscripten.h.html#browser-execution-environment) talks about how a long-running 'thread' can
 be created. 
 
 So does this section about [Implementing an async main loop in C++](https://kripken.github.io/emscripten-site/docs/porting/emscripten-runtime-environment.html#implementing-an-asynchronous-main-loop-in-c-c)

 [Worker API](http://kripken.github.io/emscripten-site/docs/api_reference/emscripten.h.html?highlight=call_worker#worker-api) may be useful if we want to try to emulate threading.

 [WebAssembly Explorer](https://mbebenita.github.io/WasmExplorer/) allows you to experiment with running C++ code in the browser without setting up Emscripten.