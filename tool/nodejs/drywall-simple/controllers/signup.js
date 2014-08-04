/**
 *  Controller for signup.
 */


/**
 *  Initial signup page, displaying signup form.
 */
exports.init = function(req, res) {

  res.render('signup', {});

  // if (req.isAuthenticated()) {
  //   res.redirect(req.user.defaultReturnUrl());
  // } else {
  //   res.render('signup', {
  //     oauthMessage: '',
  //     oauthTwitter: !!req.app.config.oauth.twitter.key,
  //     oauthGitHub: !!req.app.config.oauth.github.key,
  //     oauthFacebook: !!req.app.config.oauth.facebook.key,
  //     oauthGoogle: !!req.app.config.oauth.google.key,
  //     oauthTumblr: !!req.app.config.oauth.tumblr.key
  //   });
  // }
};


/**
 *  Hanlder for posting signup form.
 */
exports.signup = function(req, res) {
  res.render('signup', {});
};
