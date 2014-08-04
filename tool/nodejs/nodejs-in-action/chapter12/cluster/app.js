var cluster = require('cluster'),
    http = require('http'),
    numCPUs = require('os').cpus().length;

if (cluster.isMaster) {
  for (var i = 0; i < numCPUs; i++){
    cluster.fork();
  }
  cluster.on('exit', function(worker, code, signal) {
    console.log('Worker' + worker.process.id + ' died.');
  });
} else {
  http.Server(function(req, res) {
    res.writeHead(200);
    res.end('I am a worker running in process ' + process.pid);
  }).listen(8000);
}
