// Stolen from rvagg/leveldown
/* LD_METHOD_SETUP_COMMON setup the following objects:
 *  - Database* database
 *  - v8::Local<v8::Object> optionsObj (may be empty)
 *  - v8::Persistent<v8::Function> callback (won't be empty)
 * Will throw/return if there isn't a callback in arg 0 or 1
 */
#define LD_METHOD_SETUP_COMMON(name, optionPos, callbackPos)                   \
  if (args.Length() == 0)                                                      \
    return NanThrowError(#name "() requires a callback argument");             \
  v8::Local<v8::Object> optionsObj;                                            \
  v8::Local<v8::Function> callback;                                            \
  if (optionPos == -1 && args[callbackPos]->IsFunction()) {                    \
    callback = args[callbackPos].As<v8::Function>();                           \
  } else if (optionPos != -1 && args[callbackPos - 1]->IsFunction()) {         \
    callback = args[callbackPos - 1].As<v8::Function>();                       \
  } else if (optionPos != -1                                                   \
        && args[optionPos]->IsObject()                                         \
        && args[callbackPos]->IsFunction()) {                                  \
    optionsObj = args[optionPos].As<v8::Object>();                             \
    callback = args[callbackPos].As<v8::Function>();                           \
  } else {                                                                     \
    return NanThrowError(#name "() requires a callback argument");             \
  }
