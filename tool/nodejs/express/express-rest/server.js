/**
 *  Entry point of rest api server.
 */

var express = require('express');
var app = express();

require('./routes')(app);

app.listen(3000);
console.log('Listening on port 3000...');
