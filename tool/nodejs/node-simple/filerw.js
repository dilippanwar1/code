var fs = require('fs')

fs.writeFile('Hangout', '...', function() {
  console.log("can't wait to hear back from her!");
});

fs.readFile('Hangout', function(err, data) {
  console.log("oh, look at all my money: " + data);
});
