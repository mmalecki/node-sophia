#include <node.h>
#include <nan.h>

namespace sophia {
  void Set(
    void* db,
    void* k,
    size_t ksize,
    void* v,
    size_t vsize,
    NanCallback* callback
  );
}
