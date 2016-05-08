var s = "application"

console.log(s.toUpperCase());

var miliCPUtoFloat_ = function(core) {
  if (core.indexOf('m') > -1) {
    var cpu = core.substring(0, core.length - 1);
    return parseInt(cpu) / 1000.0;
  } else {
    return core;
  }
}

console.log(miliCPUtoFloat_("12"));
