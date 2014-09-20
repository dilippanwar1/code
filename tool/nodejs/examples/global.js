function getGlobal(){
  return (function(){
    return this;
  }).call(null);
};

var add = function (a, b) {
  return a + b;
};

var myObject = {
  value: 1,

  multiplyBy2: function () {
    var that = this;              // `that` points to myObject
    var helper = function () {
      that.value = add(that.value, that.value);
      console.log(this);
      console.log(that);
    };
    helper();
  }
};


// console.log(typeof getGlobal());
myObject.multiplyBy2();
console.log(myObject.value);
