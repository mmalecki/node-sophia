#include <node.h>
#include <nan.h>
#include <sophia.h>
#include "database_wrap.h"

using namespace v8;

namespace sophia {
  DatabaseWrap::DatabaseWrap() {
  };

  DatabaseWrap::~DatabaseWrap() {
  };

  void DatabaseWrap::Init(v8::Handle<v8::Object> exports) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(NanSymbol("DatabaseWrap"));
    tpl->InstanceTemplate()->SetInternalFieldCount(2);
    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(NanSymbol("DatabaseWrap"), constructor);
  };

  Handle<Value> DatabaseWrap::New(const Arguments& args) {
    NanScope();
    DatabaseWrap* wrap = new DatabaseWrap();

    wrap->env = sp_env();

    wrap->Wrap(args.This());
    return args.This();
  };
}
