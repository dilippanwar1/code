var logger = require('./logger');
var router = require('./router');
var connect = require('connect');
var app = connect();

var routes = {
  GET: {
    '/users': function(req, res) {
      res.end('tobi, loki, ferret');
    },
    '/user/:id': function(req, res) {
      res.end('user ' + id);
    }
  },
  DELETE: {
    '/user/:id': function(req, res, id){
      res.end('deleted user ' + id);
    }
  }
};

app.use(logger(':method :url'));
app.use(router(routes));

app.listen(3000);
