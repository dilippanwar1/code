//
//  Create Readable Stream
//

// Readable streams produce data that can be fed into a writable, transform,
// or duplex stream by calling .pipe(): readableStream.pipe(dst)

/*
var Readable = require('stream').Readable;
var rs = new Readable;

rs.push('beep ');
rs.push('boop\n');
rs.push(null);         // tell consumer rs is done with outputing data
rs.pipe(process.stdout);
*/



// It would be even better in many circumstances if we could avoid buffering
// data altogether and only generate the data when the consumer asks for it.
// We can push chunks on-demand by defining a ._read function:
//
// Here we push the letters 'a' through 'z', inclusive, but only when the
// consumer is ready to read them. The _read function will also get a provisional
// size parameter as its first argument that specifies how many bytes the
// consumer wants to read, but your readable stream can ignore the size if it
// wants.

/*
var Readable = require('stream').Readable;
var rs = new Readable;
var c = 97;

rs._read = function () {
  rs.push(String.fromCharCode(c++));
  if (c > 'z'.charCodeAt(0)) {
    rs.push('\n');
    rs.push(null);
  }
}

rs.pipe(process.stdout);
*/

/*
var Readable = require('stream').Readable;
var rs = Readable();
var c = 97 - 1;

rs._read = function () {
  if (c >= 'z'.charCodeAt(0)) return rs.push(null);

  setTimeout(function () {
    rs.push(String.fromCharCode(++c));
  }, 100);
};

rs.pipe(process.stdout);

process.on('exit', function () {
  console.error('\n_read() called ' + (c - 97) + ' times');
});
process.stdout.on('error', process.exit);
*/



//
//  Consume Readable Stream
//
process.stdin.on('readable', function () {
  var buf = process.stdin.read();
  console.dir(buf);
});

2
