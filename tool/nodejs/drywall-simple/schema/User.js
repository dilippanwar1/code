/**
 *  'User' schema in mongoose.
 */

exports = module.exports = function(app, mongoose) {
  var userSchema = new mongoose.Schema({
    username: { type: String, unique: true },
    password: String,
    email: {type: String, unique: true }
  });
  app.db.model('User', userSchema);
};
