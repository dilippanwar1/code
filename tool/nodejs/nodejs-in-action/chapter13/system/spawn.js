var cp = require('child_process');
var fs = require('fs');
var child = cp.spawn('ls', ['-l']);

child.stdout.pipe(fs.createWriteStream('ls-result.txt'));

child.on('exit', function(code, signal) {
  console.log(code);
});

