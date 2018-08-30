
# Instructions

I’m on windows, so you may have to make mods to some of this stuff to use it.
 
1. Build the c files
  `./build.sh` or `build.bat`
 
2. Use python to run a local web server like this:
  `python server.py`
 
3. Then open a browser and load http://localhost:9000
 
4. Then open the developer tools so you can see the browser console
 
5. Now click the ‘Go (Webworker)’ or 'Go (Pthread)' button and watch the console: you can see the Fibonacci calc runs more than once during the time the prime calculation completes.
 

# Pthread support

This project now supports pthreads, in order to use them, you must download [Firefox Nightly](https://www.mozilla.org/en-US/firefox/channel/desktop/#nightly) and enable the following option in `about:config`

```
javascript.options.shared_memory = true
```

Note that Pthreads are VERY FAST and are limited to 1000 iterations.  If you click the button twice very fast
to stop the threads, you should be able to stop one of them before it has completed all 1000 runs.  If we let
this go unbounded, it tends to crash the browser...

You can still use this app without Pthread support, but you will be limited to the Web Worker flow.

# STD Thread support

Once Pthreads are enabled, we can run w/ STD thread support as well.  This project is not currently set up to
run them concurrently.  By default the project is set up for STD Threads, but to enable Pthreads, just swap the
javascript webassembly wrapper in index.html.
```html
  <!-- <script type="text/javascript" src="number_ops_pthread.js"></script> -->
  <script type="text/javascript" src="number_ops_stdthread.js"></script>
```