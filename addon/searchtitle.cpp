#include "distance.h"
#include <node.h>

using namespace v8;

void Searchtitle(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  v8::String::Utf8Value param1(args[0]->ToString());

  std::string value = std::string(*param1);
  std::string final = run_search(value);
  Local<String> titles= v8::String::NewFromUtf8(isolate, final.c_str());
  args.GetReturnValue().Set(titles);
}

void Init(Handle<Object> exports) {
  populate_stop_words();
  clean_file();
  populate_trie();
  populate_vecs();
  compute_norm();
  populate_db();
  NODE_SET_METHOD(exports, "searchtitle", Searchtitle);
}

NODE_MODULE(booksfinder, Init)
