var fs = require('fs');

function example1() {
  fs.writeFile('Hangout', '...', function() {
    console.log("can't wait to hear back from her!");
  });

  fs.readFile('Hangout', function(err, data) {
    console.log("oh, look at all my money: " + data);
  });
}

function example2() {
  // 'readdirSync' reads directory synchronously, and return an array
  // of file/directory names.  'map' is a method on array, takes each
  // element of the array, then return the modified element.
  data = fs.readdirSync('.').map(
    function(file) {
      return file.slice(1);
    }
  );
  console.log(data);
}


//example1();
example2();
