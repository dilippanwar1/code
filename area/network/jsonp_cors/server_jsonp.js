// http://api_test_server.proudlygeek.c9.io/?callback=cb

var http = require("http"),
    url  = require("url");

var server = http.createServer(function(req, res) {

  var callback = url.parse(req.url, true).query.callback || "myCallback";
  console.log(url.parse(req.url, true).query.callback);

  var data = {
    'name': "Gianpiero",
    'last': "Fiorelli",
    'age': 37
  };

  data = callback + '(' + JSON.stringify(data) + ');';

  res.writeHead(200, {'Content-Type': 'application/json'});
  res.end(data);
});

server.listen(process.env.PORT, process.env.IP);

console.log('Server running at '  + process.env.PORT + ':' + process.env.IP);
