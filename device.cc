#include <napi.h>
// #include <uv.h>
#include "device.h"

Device::Device(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Device>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    // this->val_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::FunctionReference Device::constructor;

void Device::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Device", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Device", func);
}

Napi::Object Device::NewInstance(Napi::Value arg)
{
    Napi::Object obj = constructor.New({arg});
    return obj;
}