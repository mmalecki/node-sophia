#include <node.h>
#include <nan.h>
#include "database_wrap.h"

namespace sophia {
  void Open(
    DatabaseWrap* wrap,
    bool create_if_missing,
    bool read_only,
    NanCallback* callback
  );
}

