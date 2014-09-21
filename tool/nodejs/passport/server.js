// server.js

/**
 - app
 ------ models
 ---------- user.js   <!-- our user model -->
 ------ routes.js     <!-- all the routes for our application -->
 - config
 ------ auth.js       <!-- will hold all our client secret keys (facebook, twitter, google) -->
 ------ database.js   <!-- will hold our database connection settings -->
 ------ passport.js   <!-- configuring the strategies for passport -->
 - views
 ------ index.ejs     <!-- show our home page with login links -->
 ------ login.ejs     <!-- show our login form -->
 ------ signup.ejs    <!-- show our signup form -->
 ------ profile.ejs   <!-- after a user logs in, they will see their profile -->
 - package.json       <!-- handle our npm packages -->
 - server.js          <!-- setup our application -->
 */

// Set up ======================================================================
// get all the tools we need
var express  = require('express');
var mongoose = require('mongoose');
var passport = require('passport');
var flash    = require('connect-flash');

var morgan       = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser   = require('body-parser');
var session      = require('express-session');

var configDB = require('./config/database.js');

var app      = express();
var port     = process.env.PORT || 8000;

// Configuration ===============================================================
// Configuring passport contains:
//   1. Authentification Strategies.
//   2. Application Middleware.
//   3. Sessions. (Optional)
mongoose.connect(configDB.url); // connect to our database

require('./config/passport')(passport); // pass passport for configuration

// set up our express application
app.use(morgan('dev')); // log every request to the console
app.use(cookieParser()); // read cookies (needed for auth)
app.use(bodyParser.json()); // get information from html forms
app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs'); // set up ejs for templating

// required for passport
app.use(session({ secret: 'ilovescotchscotchyscotchscotch' })); // session secret
// 'passport.initialize()' returns a function, which is called on every request
app.use(passport.initialize());
app.use(passport.session()); // persistent login sessions
app.use(flash()); // use connect-flash for flash messages stored in session

// Routes ======================================================================
// load our routes and pass in our app and fully configured passport
require('./app/routes.js')(app, passport);

// Launch ======================================================================
app.listen(port);
console.log('The magic happens on port ' + port);
