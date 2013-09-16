#ifndef DATABASE_WRAP_H
#define DATABASE_WRAP_H

#include <node.h>
#include <sophia.h>

namespace sophia {
  class DatabaseWrap : public node::ObjectWrap {
    public:
      static void Init(v8::Handle<v8::Object> exports);

    private:
      DatabaseWrap();
      ~DatabaseWrap();

      static v8::Handle<v8::Value> New(const v8::Arguments& args);
      void* env;
      void* db;
  };
}

#endif
