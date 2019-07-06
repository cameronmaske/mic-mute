#include <napi.h>
// #include "myobject.h"
#include "device.h"

#include <windows.h>
#include <mmdeviceapi.h>

Napi::Object ListDevices(const Napi::CallbackInfo &info)
{
    return Device::NewInstance(info[0]);
}

Napi::Object DefaultDevice(const Napi::CallbackInfo &info)
{
    HRESULT hr;
    IMMDeviceEnumerator *enumerator = NULL;
    // Creates a single uninitalized object by passing in a CLSID (Class ID).
    hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), // Create the MMDevice Enumerator object
        NULL,
        CLSCTX_INPROC_SERVER,          // Execution context, a.k.a that the object run in the same process as the application.
        __uuidof(IMMDeviceEnumerator), // Interface identifier, e.g. IMMDeviceEnumerator (matches pointer below).
        (LPVOID *)&enumerator          // Pointer to recieve the interface.
    );
    if (hr != 0)
    {
        Napi::Env env = info.Env();
        throw Napi::Error::New(env, "Example exception");
    }

    IMMDevice *device = NULL;
    hr = enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &device);
    if (hr != 0)
    {
        Napi::Env env = info.Env();
        throw Napi::Error::New(env, "Example exception");
    }
    return Device::NewInstance(info[0]);
}

Napi::Number ReturnOne(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double count = 1;
    return Napi::Number::New(env, count);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    CoInitialize(NULL);
    Device::Init(env, exports);

    exports.Set(
        Napi::String::New(env, "listDevices"),
        Napi::Function::New(env, ListDevices));

    exports.Set(
        Napi::String::New(env, "defaultDevice"),
        Napi::Function::New(env, DefaultDevice));

    return exports;
}

NODE_API_MODULE(addon, InitAll)
