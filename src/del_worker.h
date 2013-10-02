#include <node.h>
#include <nan.h>

namespace sophia {
  void Del(
    void* db,
    void* k,
    size_t ksize,
    NanCallback* callback
  );
}
