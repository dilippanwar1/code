/**
 * Hello World example in express.
 */
var express = require('express');

var app = express();

// 'app.use' register a middleware. When request comes in,
// middleware is called in order.
app.use(function(req, res, next) {
  console.log('Log1: %s %s', req.method, req.url);
  next();
});

app.use(function(req, res, next) {
  console.log('Log2: %s %s', req.method, req.url);
  next();
});

// Middleware can take prefix, so that only matching url will be called.
// No prefix will always be called. Note here if we put '/' before
// '/something', then we will never reach '/something' middleware.
app.get('/something', function(req, res) {
  res.send("Something!");
});

app.use('/', function(req, res) {
  res.send('Hello World');
});

app.listen(3000);
