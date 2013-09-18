var path = require('path'),
    sophia = require('../'),
    db = new sophia.DatabaseWrap(path.join(__dirname, 'tmp', 'db'));

db.open({ createIfMissing: true }, function () {
  console.dir(arguments);
});
