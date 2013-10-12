#include <stdint.h>
#include <stdlib.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>
#include "database_wrap.h"

namespace sophia {
  class CloseWorker : public NanAsyncWorker {
    public:
      CloseWorker(
        DatabaseWrap* wrap_,
        NanCallback* callback
      ) : NanAsyncWorker(callback) {
        wrap = wrap_;
      };

      void Execute() {
        int r = sp_destroy(wrap->db);
        if (r == -1) {
          errmsg = sp_error(wrap->db);
          return;
        }

        r = sp_destroy(wrap->env);
        if (r == -1) {
          errmsg = sp_error(wrap->env);
        }
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

    private:
      DatabaseWrap* wrap;
  };

  void Close(
    DatabaseWrap* wrap,
    NanCallback* callback
  ) {
    CloseWorker* worker = new CloseWorker(wrap, callback);
    NanAsyncQueueWorker(worker);
  }
}
