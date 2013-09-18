#include <stdint.h>
#include <node.h>
#include <nan.h>
#include <sophia.h>

namespace sophia {
  class OpenWorker : public NanAsyncWorker {
    public:
      void* db;

      OpenWorker(
        void* env_,
        char* path_,
        bool create_if_missing_,
        bool read_only_,
        NanCallback* callback
      ) : NanAsyncWorker(callback) {
        env = env_;
        path = path_;
        create_if_missing = create_if_missing_;
        read_only = read_only_;
      };

      void Execute() {
        uint32_t flags = 0;

        if (create_if_missing)
          flags &= SPO_CREAT;

        if (read_only)
          flags &= SPO_RDONLY;

        sp_ctl(env, SPDIR, flags, path);
        db = sp_open(env);
      };

      void WorkComplete() {
        NanScope();
        HandleOKCallback();
      }

    private:
      void* env;
      char* path;
      bool create_if_missing;
      bool read_only;
  };

  void Open(
    void* env,
    char* path,
    bool create_if_missing,
    bool read_only,
    void* &db,
    NanCallback* callback
  ) {
    OpenWorker* worker = new OpenWorker(
      env,
      path,
      create_if_missing,
      read_only,
      callback
    );
    NanAsyncQueueWorker(worker);
    db = worker->db;
  }
}
