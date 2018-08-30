
self.onmessage = (evt) => {
  let objData = evt.data;
  switch (objData.id) {
    case 'nprimes': {
      _nprimes(objData.Val1);
      self.postMessage('done');
    }
    break;
  }
};

// This loads the wasm generated glue code
importScripts('nprimes.js');