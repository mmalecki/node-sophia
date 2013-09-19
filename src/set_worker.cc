#include <stdint.h>
#include <stdlib.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>

namespace sophia {
  class SetWorker : public NanAsyncWorker {
    public:
      SetWorker(
        void* db_,
        void* k_,
        size_t ksize_,
        void* v_,
        size_t vsize_,
        NanCallback* callback
      ) : NanAsyncWorker(callback) {
        db = db_;
        k = k_;
        ksize = ksize_;
        v = v_;
        vsize = vsize_;
      };

      void Execute() {
        sp_set(db, k, ksize, v, vsize);
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

    private:
      void* db;
      void* k;
      void* v;
      size_t ksize, vsize;
  };

  void Set(
    void* db,
    void* k,
    size_t ksize,
    void* v,
    size_t vsize,
    NanCallback* callback
  ) {
    SetWorker* worker = new SetWorker(db, k, ksize, v, vsize, callback);
    NanAsyncQueueWorker(worker);
  }
}
