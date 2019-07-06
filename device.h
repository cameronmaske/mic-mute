#ifndef DEVICE_H
#define DEVICE_H

#include <napi.h>
#include <mmdeviceapi.h>

class Device : public Napi::ObjectWrap<Device>
{
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Value arg);
    // Napi::String name() const { return "Yeti"; }
    // double Val() const { return val_; }

    Device(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;
    // double val_;

    IMMDevice *_device;
};

#endif