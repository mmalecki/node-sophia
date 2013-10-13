var path = require('path'),
    levelup = require('levelup'),
    Sophia = require('../'),
    test = require('tap').test,
    factory = function () { return new Sophia(path.join(__dirname, 'tmp', 'db-2')) };

test('sophia/levelup', function (t) {
  levelup('', { db: factory }, function (err, db) {
    db.put('levelup', 'yes', function (err) {
      t.ok(!err);

      db.get('levelup', function (err, val) {
        t.ok(!err);
        t.equal(val.toString('utf8'), 'yes');

        db.del('levelup', function (err) {
          t.ok(!err);

          db.get('levelup', function (err, val) {
            t.ok(!err);
            t.equal(val, null);
            t.end();
          });
        });
      });
    });
  });
});
