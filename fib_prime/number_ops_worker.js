
self.onmessage = (evt) => {
  let objData = evt.data;
  switch (objData.id) {
    case 'fib': {
      let iResult = _fib(objData.Val1);
      self.postMessage(iResult.toString());
    }
    break;

    case 'nprimes': {
      _nprimes(objData.Val1);
      self.postMessage('done');
    }
    break;
  }
};

// This loads the wasm generated glue code
importScripts('number_ops.js');

// define a method in the JS space that can be called from C	
Module.fibCallback = (n) => {
  console.log("Got mesage back from fib " + n);
}