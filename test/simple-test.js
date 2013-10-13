var path = require('path'),
    test = require('tap').test,
    sophia = require('../');

test('sophia', function (t) {
  var db = new sophia.DatabaseWrap(path.join(__dirname, 'tmp', 'db-0'));
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
  });
});
