// You have the choice between using arrays or objects for storing your data
// in Javascript.
function example1() {
  var numbers = ['zero', 'one', 'two'];
  var numbers_object = {
    '0': 'zero', '1': 'one', '2': 'two'
  };

  console.log(numbers[1]);
  console.log(numbers['1']);
  console.log(numbers_object[1]);
  console.log(numbers_object['1']);
}

// In javascript, arrays can be used as stacks.
// push/pop works on the last element.
function example2() {
  var arr = ['a', 'b', 'c'];
  arr.push('d');                // In place push to last
  console.log(arr);
  console.log(arr.pop());
  console.log(arr.pop());       // Remove the last element
  console.log(arr);
}

// unshift/shift work on the front of the array.
function example3() {
  var arr = ['a', 'b', 'c'];
  arr.unshift('1');             // In place add to front
  console.log(arr);
  console.log(arr.shift());     // Remove the front element
  console.log(arr.shift());
  console.log(arr);
}


// example1();
// example2();
example3();
