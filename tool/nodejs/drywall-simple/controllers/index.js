/**
 *  Controller for '/' routes.
 */

exports.init = function(req, res) {
  res.render('index', { title: 'Express' });
};
