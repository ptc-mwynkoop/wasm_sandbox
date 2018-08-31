
class CanvasSketch {

  constructor(canvasid, clearbtnid) {
    let self = this;

    self._canvas = document.getElementById(canvasid);
    self._ctx = this._canvas.getContext('2d');

    document.getElementById(clearbtnid)
      .addEventListener('click', (e) => {
        self.clearCanvas();
      });

    // something to hold stroke point data while it is happening
    this._points = [];

    // get the style of the canvas element in order to make the dimensions
    // of the canvas match so that there is no scaling of the drawing
    var paint_style = getComputedStyle(self._canvas);
    self._canvas.width = parseInt(paint_style.getPropertyValue('width'));
    self._canvas.height = parseInt(paint_style.getPropertyValue('height'));
    
    // styling for the stroke
    self._ctx.lineWidth = 3;
    self._ctx.lineJoin = 'round';
    self._ctx.lineCap = 'round';
    self._ctx.strokeStyle = '#00CC99';        

    // convert mouse coordinates to canvas space
    self._localizeMouseCoords = (e) => {
      return {
        x: e.pageX - self._canvas.offsetLeft,
        y: e.pageY - self._canvas.offsetTop 
      }
    }

    // listen for mousedown. when you get it, create an additional mousemove handler
    // to record the points and do the drawing
    self._canvas.addEventListener('mousedown', (e) => {
      self._points = [];
      self._ctx.beginPath();
      const mousepoint = self._localizeMouseCoords(e);
      self._ctx.moveTo(mousepoint.x, mousepoint.y);
      self._points.push( {x: mousepoint.x, y: mousepoint.y});
      self._canvas.addEventListener('mousemove', self._onMouseMove, false);
    }, false);

    // listen for mouseup. this event signifies the end of a stroke, fire the
    // onstroke handler
    self._canvas.addEventListener('mouseup', () => {
      if( self._points.length > 0)
        self._endStroke();
    }, false); 

    self._endStroke = () => {
      self._canvas.removeEventListener('mousemove', self._onMouseMove, false);

      // We are done with the stroke, send it
      self._emitStroke();
      self._points = [];
    }
    
    // inform the client the stoke is complete
    self._emitStroke = () => {
      if( self._strokeCallback )
        self._strokeCallback(self._points);
    } 
    
    // paint the path of the mouse on the canvas
    self._onMouseMove = (e) => {
      const mousepoint = self._localizeMouseCoords(e);
      // if you go out of bounds, end the stroke
      if( mousepoint.x >= self._canvas.width || 
        mousepoint.y >= self._canvas.height ) {
        self._endStroke();
      } else {
        self._ctx.lineTo(mousepoint.x, mousepoint.y);
        self._ctx.stroke();
        self._points.push( {x: mousepoint.x, y: mousepoint.y});
      }
    };     

  }

  // erase the canvas
  clearCanvas() {
    this._ctx.clearRect(0, 0, this._canvas.width, this._canvas.height);
  } 
  
  // let client register a callback for stoke event
  onStroke(callback) {
    this._strokeCallback = callback;
  }

}