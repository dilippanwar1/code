// http://api_test_server.proudlygeek.c9.io/

var http = require("http"),
    url  = require("url");

var server = http.createServer(function(req, res) {
  console.log(req.headers);

  var data = {
    'name': "Gianpiero",
    'last': "Fiorelli",
    'age': 37
  };

  res.writeHead(200, {
    'Content-Type': 'application/json',
    'Access-Control-Allow-Origin': '*'
  });

  res.end(JSON.stringify(data));
});

server.listen(process.env.PORT, process.env.IP);

console.log('Server running at '  + process.env.PORT + ':' + process.env.IP);
