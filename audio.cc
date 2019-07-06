#include <napi.h>
#include <windows.h>
#include <mmdeviceapi.h>

#include "device.h"
#include "utils.h"

Napi::Object ListDevices(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    IMMDeviceEnumerator *enumerator = NULL;

    CheckOrThrowHR(
        env,
        CoCreateInstance(
            __uuidof(MMDeviceEnumerator), // Create the MMDevice Enumerator object
            NULL,
            CLSCTX_INPROC_SERVER,          // Execution context, a.k.a that the object run in the same process as the application.
            __uuidof(IMMDeviceEnumerator), // Interface identifier, e.g. IMMDeviceEnumerator (matches pointer below).
            (LPVOID *)&enumerator          // Pointer to recieve the interface.
            ));

    IMMDeviceCollection *collection;

    CheckOrThrowHR(
        env,
        enumerator->EnumAudioEndpoints(
            eCapture,
            DEVICE_STATE_ACTIVE,
            &collection));

    UINT count;
    CheckOrThrowHR(
        env, collection->GetCount(&count));

    Napi::Array devices = Napi::Array::New(info.Env(), count);
    for (int i = 0; i < count; i++)
    {
        IMMDevice *device;
        CheckOrThrowHR(env, collection->Item(i, &device));
        devices[i] = Device::NewInstance(info[0], device);
    }

    return devices;
}

Napi::Object DefaultDevice(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    IMMDeviceEnumerator *enumerator = NULL;

    CheckOrThrowHR(
        env,
        CoCreateInstance(
            __uuidof(MMDeviceEnumerator), // Create the MMDevice Enumerator object
            NULL,
            CLSCTX_INPROC_SERVER,          // Execution context, a.k.a that the object run in the same process as the application.
            __uuidof(IMMDeviceEnumerator), // Interface identifier, e.g. IMMDeviceEnumerator (matches pointer below).
            (LPVOID *)&enumerator          // Pointer to recieve the interface.
            ));

    IMMDevice *device = NULL;

    CheckOrThrowHR(
        env,
        enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &device));
    return Device::NewInstance(info[0], device);
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
