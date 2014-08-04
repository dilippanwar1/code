/**
 *  A simple prototype.
 */

// Require all dependencies.
var express = require('express');
var path = require('path');
var favicon = require('static-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var mongoose = require('mongoose');
var swig = require('swig');


// Create and configure express, middleware, database, etc.
var app = express();
app.engine('html', swig.renderFile);
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'html');

app.use(favicon());
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.db = mongoose.createConnection('localhost/drywall-simple');
app.db.on('error', console.error.bind(console, 'mongoose connection error: '));
app.db.once('open', function () {});


// Application level configuration.
require('./models')(app, mongoose);
require('./routes')(app);
require('./errors')(app);


// Start express server.
app.listen(app.get('port'), function() {
  console.log('Express server listening on port ' + app.get('port'));
});
