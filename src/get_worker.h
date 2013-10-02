#include <node.h>
#include <nan.h>

namespace sophia {
  void Get(
    void* db,
    void* k,
    size_t ksize,
    NanCallback* callback
  );
}
