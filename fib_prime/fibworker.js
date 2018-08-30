
self.onmessage = (evt) => {
  let objData = evt.data;
  switch (objData.id) {
    case 'fib': {
      let iResult = _fib(objData.Val1);
      self.postMessage(iResult.toString());
    }
    break;
  }
};

// This loads the wasm generated glue code
importScripts('fib.js');

// define a method in the JS space that can be called from C	
Module.fibCallback = (n) => {
  //console.log("msg is " + n);
}