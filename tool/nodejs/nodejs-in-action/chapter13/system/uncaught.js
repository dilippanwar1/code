process.on('uncaughtException', function(err) {
  console.error('got uncaughtException: ', err.message);
  process.exit(1);
});

throw new Error('an uncaughtException exception');
