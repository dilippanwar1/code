var Currency = function(canadianDollar) {
  this.canadianDollar = canadianDollar;
};

Currency.prototype.roundTwoDecimals = function(amount) {
  return Math.round(amount * 100) / 100;
};

Currency.prototype.canadianToUS = function(canadian) {
  return this.roundTwoDecimals(canadian * this.canadianDollar);
};

Currency.prototype.USToCanadian = function(us) {
  return this.roundTwoDecimals(us / this.canadianDollar);
};


console.log('In currency.js ' + __dirname);

// In order to get the module code to work as expected, you'd need to replace
// exports with module.exports. The module.exports mechanism is provided as
// a way to work around Node's inabiliy to set exports to something other than
// an object. If you create a module that populates both exports and
// module.exports, module.exports will be returned and exports will be ignored.
module.exports = Currency;
