var badfibonacci = function (n) {
  return n < 2 ? n : badfibonacci(n-1) + badfibonacci(n-2);
};

console.log(badfibonacci(42));


var fastfibonacci = (function(n) {
  var memo = [0,1];
  var fib = function(n) {
    var result = memo[n];
    if (typeof result !== 'number') {
      result = fib(n-1) + fib(n-2);
      memo[n] = result;
    }
    return result;
  }
  return fib;
}());

console.log(fastfibonacci(42));


// Generalize memoize
var memoizer = function (memo, formula) {
  var recur = function (n) {
    var result = memo[n];
    if (typeof result !== 'number') {
      result = formula(recur, n);
      memo[n] = result;
    }
    return result;
  }
  return recur;
};

var fib = memoizer([0,1], function (recur, n) {
  return recur(n-1) + recur(n-2);
});

console.log(fib(42));
