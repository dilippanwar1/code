var cp = require('child_process');

cp.exec('ls', ['-l', process.cwd()], function(err, stdout, stderr) {
  if (err) throw err;
  console.log(stdout);
});
