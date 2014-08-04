// Node is also huge on streams and streaming. You can think of streams like
// arrays, but instead of having data distributed over space, streams can be
// thought of as data distributed over time . By bringing data in chunk by
// chunk, the developer is given the ability to handle that data as it comes
// in instead of waiting for it all to arrive before acting. Here's how we
// would stream resource.json :
var fs = require('fs')
var stream = fs.createReadStream('./resource.json')

stream.on('data', function (chunk) {
  console.log(chunk)
})
stream.on('end', function () {
  console.log('finished')
})



// This provides an efficient way to write out data as soon as it's ready
// without waiting for the complete resource to be read and then written out.
//
// In this one-liner, the data is read in from the file (fs.createReadStream)
// and being sent out (.pipe) to the client (res) as it comes in. The event
// loop is able to handle other events while data is being streamed.
var http = require('http');
var fs = require('fs');
http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'image/png'});
  // Piping from a readable stream to a writeable stream.
  fs.createReadStream('./image.png').pipe(res);
}).listen(3000);
console.log('Server running at http://localhost:3000/');
