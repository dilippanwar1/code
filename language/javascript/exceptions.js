var add = function (a, b) {
  if (typeof a !== 'Number' || typeof b !== 'Number') {
    throw {
      name: 'TypeError',
      message: 'add() function needs numbers'
    };
  }

  return a + b;
}


var try_it = function () {
  try {
    add('seven', 2);
  } catch (e) {                 // javascript will catch all exceptions
    console.log(e.name + ': ' + e.message);
  }
}

try_it()

