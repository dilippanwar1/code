var nodes = {};

console.log(nodes["abc"]);

if (nodes["abc"] === undefined) {
  nodes["abc"] = 0;
} else {
  nodes["abc"]++;
}

if (nodes["abcx"] === undefined) {
  nodes["abcx"] = 0;
} else {
  nodes["abcx"]++;
}

console.log(nodes["abc"]);

for (var node in nodes) {
  console.log(nodes[node]);
}

console.log(Object.keys(nodes).length);

var a = 1;
a++;
console.log(a++);
console.log(a);
