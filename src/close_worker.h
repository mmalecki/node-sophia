#include <node.h>
#include <nan.h>
#include "database_wrap.h"

namespace sophia {
  void Close(
    DatabaseWrap* wrap,
    NanCallback* callback
  );
}
