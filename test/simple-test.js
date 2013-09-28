var path = require('path'),
    sophia = require('../'),
    db = new sophia.DatabaseWrap(path.join(__dirname, 'tmp', 'db'));

db.open({ createIfMissing: true }, function () {
  console.log('opened');
  db.put('hello', 'world', function () {
    console.log('put');
    db.get('hello', function (err, val) {
      if (err) throw err;
      console.log(val.toString('utf8'));
    });
  });
});
