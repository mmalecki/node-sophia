var path = require('path'),
    test = require('tap').test,
    Sophia = require('../');

test('sophia', function (t) {
  var db = new Sophia(path.join(__dirname, 'tmp', 'db-0'));
  db.open({ createIfMissing: true }, function () {
    t.test('get/put', function (t) {
      db.put('hello', 'world', function (err) {
        t.ok(!err);

        db.get('hello', function (err, val) {
          t.ok(!err);
          t.equal(val.toString('utf8'), 'world');

          db.del('hello', function (err) {
            t.ok(!err);

            db.get('hello', function (err, val) {
              t.ok(!err);
              t.equal(val, null);
              t.end();
            });
          });
        });
      });
    });

    t.test('no such key', function (t) {
      db.get('404', function (err, val) {
        t.ok(!err);
        t.equal(val, null);
        t.end();
      });
    });

    t.test('require strings', function (t) {
      db.put(1, 2, function (err) {
        t.ok(err);
        t.equal(err.message, 'Expecting a string');
        db.get(3, function (err) {
          t.ok(err);
          t.equal(err.message, 'Expecting a string');
          db.del(4, function (err) {
            t.ok(err);
            t.equal(err.message, 'Expecting a string');
            t.end();
          });
        });
      });
    });
  });
});
