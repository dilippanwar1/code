// partially function: prefill arguments to a function before it's executed.


// 'partial' is a function that returns a function.
Function.prototype.partial = function() {

  var fn = this;                // record original function
  var args = Array.prototype.slice.call(arguments); // record original function

  return function() {
    var arg = 0;
    for (var i = 0; i < args.length && arguments.length; i++) {
      if (args[i] === undefined) {
        args[i] = arguments[arg++];
      }
    }
    return fn.apply(this, args);
  };
};


var timeOutTwoSec = setTimeout.partial(undefined, 2000);


timeOutTwoSec(function() {
  console.log('It works!');
});
