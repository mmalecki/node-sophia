#include <node.h>
#include "database_wrap.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  sophia::DatabaseWrap::Init(exports);
}

NODE_MODULE(sophia, InitAll)
