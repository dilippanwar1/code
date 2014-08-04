var canadianDollar = 0.91;

function roundTwoDecimals(amount) {
  return Math.round(amount * 100) / 100;
}

// The canadianToUS function is set in the exports module so it can be
// used by code requiring this module.
exports.canadianToUS = function(canadian) {
  return roundTwoDecimals(canadian * canadianDollar);
};

exports.USToCanadian = function(us) {
  return roundTwoDecimals(us / canadianDollar);
};


// To utilize your new module, you can use Node's require function, which
// takes as an argument a path to the module you wish to use. Node performs
// a synchronous lookup in order to locate, and load the file's contents.
// Because require is synchronous, unlike most functions in the node API, 
// you do not need to supply require with a callback function.

// After node has located and evaluated your module, the require function
// returns the contents of "exports" defined in the module. You're then
// able to use the two functions returned by the module to do currency
// conversion.
`
