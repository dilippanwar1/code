/**
 * Initialize client for master server.
 *
 * Usage:
 *   client.ping(function(err, response) {
 *     console.log('ping()');
 *   });
 */

var thrift = require('thrift');
var MasterServer = require('./gen-nodejs/MasterServer');
var MasterServerTypes = require('./gen-nodejs/master_types');


transport = thrift.TBufferedTransport();
protocol = thrift.TBinaryProtocol();

var connection = thrift.createConnection("localhost", 9090, {
  transport : transport,
  protocol : protocol
});

connection.on('error', function(err) {
  console.log("Master server connection error: " + err);
});

// Create a client for master server.
var client = thrift.createClient(MasterServer, connection);

// client.getVersionMeta(100, function(err, response) {
//   console.log('getVersionMeta');
//   console.log(response.versionID + 1);
//   connection.end();
// });

client.getProjectMeta('Project1', function(err, response) {
  console.log('getProjectMeta');
  console.log(JSON.stringify(response, null, 2));
  connection.end();
});

// client.getTrackMeta(100, function(err, response) {
//   console.log('getTrackMeta');
//   console.log(response);
//   connection.end();
// });

// client.addone(1, function(err, response) {
//   console.log('addone');
//   console.log(response+1);
//   connection.end();
// });
