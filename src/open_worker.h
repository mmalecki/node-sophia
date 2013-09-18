#include <node.h>
#include <nan.h>

namespace sophia {
  void Open(
    void* env,
    char* path,
    bool create_if_missing,
    bool read_only,
    void* &db,
    NanCallback* callback
  );
}

