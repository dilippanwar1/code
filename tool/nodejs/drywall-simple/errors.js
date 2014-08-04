/**
 *  Setup error handlers - 404, development handler, production handler.
 */

exports = module.exports = function(app) {
  app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
  });

  if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
      res.status(err.status || 500);
      res.send({ error: 'Something went wrong.', details: err });
    });
  }

  app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.send({ error: 'Something went wrong.', details: err });
  });
};
