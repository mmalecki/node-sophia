#include <stdint.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>
#include "database_wrap.h"

namespace sophia {
  class OpenWorker : public NanAsyncWorker {
    public:
      OpenWorker(
        DatabaseWrap* wrap_,
        bool create_if_missing_,
        bool read_only_,
        NanCallback* callback
      ) : NanAsyncWorker(callback) {
        wrap = wrap_;
        create_if_missing = create_if_missing_;
        read_only = read_only_;
      };

      void Execute() {
        uint32_t flags = 0;
        void* db;

        if (create_if_missing)
          flags |= SPO_CREAT;

        if (read_only)
          flags |= SPO_RDONLY;

        sp_ctl(wrap->env, SPDIR, flags, wrap->location);
        db = sp_open(wrap->env);
        wrap->db = db;
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

    private:
      bool create_if_missing;
      bool read_only;
      DatabaseWrap* wrap;
  };

  void Open(
    DatabaseWrap* wrap,
    bool create_if_missing,
    bool read_only,
    NanCallback* callback
  ) {
    OpenWorker* worker = new OpenWorker(
      wrap,
      create_if_missing,
      read_only,
      callback
    );
    NanAsyncQueueWorker(worker);
  }
}
