var path = require('path'),
    test = require('tap').test,
    sophia = require('../');

test('sophia/open-close', function (t) {
  var db = new sophia.DatabaseWrap(path.join(__dirname, 'tmp', 'db-1'));
  db.open({ createIfMissing: true }, function (err) {
    t.ok(!err);
    db.close(function (err) {
      t.ok(!err);
      t.end();
    });
  });
});
