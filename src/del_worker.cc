#include <stdint.h>
#include <stdlib.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>

namespace sophia {
  class DelWorker : public NanAsyncWorker {
    public:
      DelWorker(
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
        int r = sp_delete(db, k, ksize);
        if (r == -1) {
          errmsg = sp_error(db);
        }
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

    private:
      void* db;
      void* k;
      size_t ksize;
  };

  void Del(
    void* db,
    void* k,
    size_t ksize,
    NanCallback* callback
  ) {
    DelWorker* worker = new DelWorker(db, k, ksize, callback);
    NanAsyncQueueWorker(worker);
  }
}
