/**
 *  Configure routes.
 */

exports = module.exports = function(app) {
  // front end
  app.get('/', require('./controllers/index').init);

  // sign up
  app.get('/signup', require('./controllers/signup').init);
  app.post('/signup', require('./controllers/signup').signup);
};
