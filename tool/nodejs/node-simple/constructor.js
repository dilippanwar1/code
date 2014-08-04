// Create a constructor function called Quo.
var Quo = function (string) {
  this.status = string;
  console.log(this);
};

// Give all instance of Quo a public method.
Quo.prototype.get_status = function () {
  return this.status;
}


// Call Quo without new, then `this` will be bound to global object,
// and `myQuoUndefined` is undefined, since Quo return nothing.
var myQuoUndefined = Quo('confused');
console.log(myQuoUndefined);


// Create a new object `myQuoObj`.  In function Quo, `this` will be
// bound to the new object.  Nothing is returned, but javascript will
// automatically return `this` instead.
var myQuoObj = new Quo('confused');
console.log(myQuoObj);
console.log(myQuoObj.get_status());

