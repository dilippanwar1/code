// Note: out-dated since Connect moved all midware to respective packages.
var connect = require('connect');
var app = connect()
      .use(connect.favicon())
      .use(connect.('keyboard cat'))
      .use(connect.session())
      .use(function(req, res, next){
        var sess = req.session;
        if (sess.views) {
          res.setHeader('Content-Type', 'text/html');
          res.write('<p>views: ' + sess.views + '</p>');
          res.end();
          sess.views++;
        } else {
          sess.views = 1;
          res.end('welcome to the session demo. refresh!');
        }
      });
app.listen(3000);
