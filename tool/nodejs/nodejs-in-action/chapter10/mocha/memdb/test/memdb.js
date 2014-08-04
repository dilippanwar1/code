var memdb = require('..');
var assert = require('assert');

describe('memdb', function() {

  before(function() {
    console.log('Call before');
  });

  beforeEach(function() {
    console.log('Call beforeEach');
    memdb.clear();
  });

  describe('.save(doc)', function(){
    it('should save the document', function(done) {
      console.log('1');
      var pet = { name: 'Tobi' };
      memdb.save(pet, function() {
        var ret = memdb.first({ name: 'Tobi' });
        assert(ret == pet);
        done();
      });
    });
    it('see if beforeEach is called', function() {
      console.log('2');
      assert(true);
    });
    it('see the order of it', function() {
      console.log('3');
      assert(true);
    });
  });

  describe('.first(obj)', function() {
    it('should return the first matching doc', function() {
      var tobi = { name: 'Tobi' };
      var loki = { name: 'Loki' };
      memdb.save(tobi);
      memdb.save(loki);
      var ret = memdb.first({ name: 'Tobi' });
      assert(ret == tobi);
      ret = memdb.first({ name: 'Loki' });
      assert(ret == loki);
    });
    it('should return null when no doc matches', function() {
      var ret = memdb.first({ name: 'Manny' });
      assert(ret == null);
    });
  });
});
