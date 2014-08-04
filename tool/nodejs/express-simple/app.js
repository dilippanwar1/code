var express = require('express');
var app = express();

app.use(function(req, res, next) {
    console.log('Log1: %s %s', req.method, req.url);
    next();
});

app.use(function(req, res, next) {
    console.log('Log2: %s %s', req.method, req.url);
    next();
});

app.use('/', function(req, res) {
    res.send('Hello World');
});

app.get('/something', function(req, res) {
    res.send("Something!");
});

app.listen(3000);
