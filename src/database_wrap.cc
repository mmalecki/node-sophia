#include <node.h>
#include <nan.h>
#include <sophia.h>
#include "database_wrap.h"
#include "open_worker.h"
#include "set_worker.h"
#include "get_worker.h"
#include "del_worker.h"
#include "close_worker.h"
#include "sophia.h"

using namespace v8;

namespace sophia {
  DatabaseWrap::DatabaseWrap() {
  };

  DatabaseWrap::~DatabaseWrap() {
  };

  void DatabaseWrap::Init(Handle<Object> exports) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(NanSymbol("DatabaseWrap"));
    tpl->InstanceTemplate()->SetInternalFieldCount(2);

    tpl->PrototypeTemplate()->Set(
      NanSymbol("open"),
      FunctionTemplate::New(Open)->GetFunction()
    );
    tpl->PrototypeTemplate()->Set(
      NanSymbol("put"),
      FunctionTemplate::New(Put)->GetFunction()
    );
    tpl->PrototypeTemplate()->Set(
      NanSymbol("get"),
      FunctionTemplate::New(Get)->GetFunction()
    );
    tpl->PrototypeTemplate()->Set(
      NanSymbol("del"),
      FunctionTemplate::New(Del)->GetFunction()
    );
    tpl->PrototypeTemplate()->Set(
      NanSymbol("close"),
      FunctionTemplate::New(Close)->GetFunction()
    );

    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(NanSymbol("DatabaseWrap"), constructor);
  };

  NAN_METHOD(DatabaseWrap::New) {
    NanScope();
    DatabaseWrap* wrap = new DatabaseWrap();

    wrap->env = sp_env();
    wrap->location = NanFromV8String(args[0]);

    wrap->Wrap(args.This());
    return args.This();
  };

  NAN_METHOD(DatabaseWrap::Open) {
    NanScope();

    DatabaseWrap* wrap = ObjectWrap::Unwrap<DatabaseWrap>(args.This());

    LD_METHOD_SETUP_COMMON(open, 0, 1)

    bool create_if_missing = NanBooleanOptionValue(optionsObj, NanSymbol("createIfMissing"), true);
    bool read_only = NanBooleanOptionValue(optionsObj, NanSymbol("readOnly"), false);
    // TODO: add rest of flags

    sophia::Open(
      wrap,
      create_if_missing,
      read_only,
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };

  NAN_METHOD(DatabaseWrap::Put) {
    NanScope();
    DatabaseWrap* wrap = ObjectWrap::Unwrap<DatabaseWrap>(args.This());
    LD_METHOD_SETUP_COMMON(put, 2, 3)

    char* key = NanFromV8String(args[0]);
    char* value = NanFromV8String(args[1]);

    sophia::Set(
      wrap->db,
      key,
      strlen(key),
      value,
      strlen(value),
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };

  NAN_METHOD(DatabaseWrap::Get) {
    NanScope();
    DatabaseWrap* wrap = ObjectWrap::Unwrap<DatabaseWrap>(args.This());
    LD_METHOD_SETUP_COMMON(get, 1, 2);

    char* key = NanFromV8String(args[0]);

    sophia::Get(
      wrap->db,
      key,
      strlen(key),
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };

  NAN_METHOD(DatabaseWrap::Del) {
    NanScope();

    DatabaseWrap* wrap = ObjectWrap::Unwrap<DatabaseWrap>(args.This());
    LD_METHOD_SETUP_COMMON(get, 1, 2);

    char* key = NanFromV8String(args[0]);

    sophia::Del(
      wrap->db,
      key,
      strlen(key),
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };

  NAN_METHOD(DatabaseWrap::Close) {
    NanScope();
    Local<Function> callback = args[0].As<Function>();
    DatabaseWrap* wrap = ObjectWrap::Unwrap<DatabaseWrap>(args.This());

    sophia::Close(
      wrap,
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };

}
