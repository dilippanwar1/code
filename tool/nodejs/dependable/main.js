/**
 * A minimalist dependency injection framework for node.js
 */


/**
 * Register dependencies.
 */
// Create a new container.
var dependable = require('dependable'),
    container = dependable.container();

// Registry a string dependency for later use.
container.register('occupation', 'tax attorney');

// Registry an object dependency for later use.
container.register('transport', {
  type: 'station wagon',
  material: 'wood-paneled'
});

// When the argument is a function, the function's arguments are automatically
// populated with the correct dependencies, and the return value of the function
// is registered as the dependency:
container.register('song', function (occupation, transport, legalStatus) {
  // Below log won't be printed unless it is actually used.
  console.log('Executing song dependency function.');
  var song = {};
  song.chorus = function chorus() {
    return [
      'I\'m a ' + occupation,
      'On a ' + transport.material + ' ' + transport.type + ' I ride',
      'And I\'m ' + legalStatus.message
    ].join('\n');
  };
  return song;
});

// song depends on a legalStatus, which hasn't been registered yet. Dependable
// resolves dependencies lazily, so we can define this dependency after-the-fact.
container.register('legalStatus', {
  warrants: [],
  message: 'without outstanding warrants'
});


/**
 * Resolve dependencies.
 */
// Resolve a dependency and use it. Like with container.register, the function
// arguments are automatically resolved, along with their dependencies.
container.resolve(function (song) {
  /*
   * I'm a tax attorney
   * On a wood-paneled station wagon I ride
   * And I'm without outstanding warrants
   */
  console.log("----------------------");
  console.log(song.chorus());
});


/**
 * Re-register dependencies.
 */
// As it stands, song returns boring, non-catchy lyrics. One way to change its
// behavior is to re-register its dependencies:
container.register('occupation', 'cowboy');
container.register('legalStatus', {
  warrants: [
    {
      for: 'shooting the sheriff',
      notes: 'did not shoot the deputy'
    }
  ],
  message: 'wanted: dead or alive'
});

// For the new dependency to take effect, we need to pass {} as first parameter.
container.resolve({}, function (song) {
  console.log("----------------------");
  console.log(song.chorus());
});

/**
 * Override dependencies at resolve time
 */
// It's also possible to override dependencies at resolve time:
var horse = {
  type: 'horse',
  material: 'steel'
};

container.resolve({ transport: horse }, function (song) {
  /*
   * I'm a cowboy
   * On a steel horse I ride
   * And I'm wanted: dead or alive
   */
  console.log("----------------------");
  console.log(song.chorus());
});
