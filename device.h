#ifndef DEVICE_H
#define DEVICE_H

#include <napi.h>
#include <mmdeviceapi.h>

class Device : public Napi::ObjectWrap<Device>
{
public:
    Device(const Napi::CallbackInfo &info); // constructor
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Value arg, IMMDevice *device);

private:
    static Napi::FunctionReference constructor;
    Napi::Value GetName(const Napi::CallbackInfo &info);
    Napi::Value Mute(const Napi::CallbackInfo &info);
    Napi::Value Unmute(const Napi::CallbackInfo &info);

    IMMDevice *_device;
};

#endif