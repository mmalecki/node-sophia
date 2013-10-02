#include <stdint.h>
#include <stdlib.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>

namespace sophia {
  class GetWorker : public NanAsyncWorker {
    public:
      GetWorker(
        void* db_,
        void* k_,
        size_t ksize_,
        NanCallback* callback
      ) : NanAsyncWorker(callback) {
        db = db_;
        k = k_;
        ksize = ksize_;
      };

      void Execute() {
        r = sp_get(db, k, ksize, &value, &vsize);
        if (r == -1) {
          errmsg = sp_error(db);
        }
        else if (r == 0) {
          value = NULL;
        }
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

      void HandleOKCallback() {
        v8::Local<v8::Value> returnValue;

        if (value == NULL) {
          returnValue = v8::Local<v8::Value>::New(v8::Null());
        }
        else {
          returnValue = NanNewBufferHandle((char*) value, vsize);
        }
        v8::Local<v8::Value> argv[] = {
          v8::Local<v8::Value>::New(v8::Null()),
          returnValue
        };
        callback->Call(2, argv);
      }

    private:
      void* db;
      void* k;
      size_t ksize;

      // Return values
      int r;
      void* value;
      size_t vsize;
  };

  void Get(
    void* db,
    void* k,
    size_t ksize,
    NanCallback* callback
  ) {
    GetWorker* worker = new GetWorker(db, k, ksize, callback);
    NanAsyncQueueWorker(worker);
  }
}
