#include <node.h>
#include <nan.h>
#include <sophia.h>
#include "database_wrap.h"
#include "open_worker.h"
#include "sophia.h"

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

    tpl->PrototypeTemplate()->Set(
      NanSymbol("open"),
      FunctionTemplate::New(Open)->GetFunction()
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
    bool read_only = NanBooleanOptionValue(optionsObj, NanSymbol("readOnly"), true);
    // TODO: add rest of flags

    sophia::Open(
      wrap->env,
      wrap->location,
      create_if_missing,
      read_only,
      wrap->db,
      new NanCallback(callback)
    );
    NanReturnUndefined();
  };
}
