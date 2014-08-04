// Modules can either be single files or directories containing one or more
// files.  If a module is a directory, the file in the module directory that
// will be evaluated is normally named "index.js" (although this can be
// overridden).
// 
// To create a typical module, you create a file that defines properties on
// the exports object with any kind of data, such as strings, objects, and
// functions.



// To create a module that will return anything other than an object you
// might guess that you simply need to set exports to whatever you want to
// return. This, however, won't work as Node expects exports to remain an
// object.


// var Currency = require('./currency');  // error
// var Currency = require('./currency2')
var Currency = require('./currency3')
  , canadianDollar = 0.91;

console.log('In module.js ' + __dirname);
currency = new Currency(canadianDollar);
console.log(currency.canadianToUS(50));
