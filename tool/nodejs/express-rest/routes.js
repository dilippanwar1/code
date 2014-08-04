/**
 *  Configure routes.
 */

var users = require('./modules/users')


exports = module.exports = function(app) {
  // users
  app.get('/restapi/v1/login', users.login);
};
