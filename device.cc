#include <napi.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <comdef.h>
#include <functiondiscoverykeys_devpkey.h>
#include <stdio.h>
#include <system_error>

#include "utils.h"
#include "device.h"

Device::Device(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Device>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
};

Napi::FunctionReference Device::constructor;

void Device::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(
        env,
        "Device",
        {
            InstanceMethod("getName", &Device::GetName),
            InstanceMethod("mute", &Device::Mute),
            InstanceMethod("unmute", &Device::Unmute),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
}

Napi::Value Device::GetName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    IPropertyStore *props;

    CheckOrThrowHR(
        env,
        this->_device->OpenPropertyStore(STGM_READ, &props));

    PROPVARIANT variant;
    PropVariantInit(&variant);

    CheckOrThrowHR(
        env,
        props->GetValue(PKEY_Device_FriendlyName, &variant));

    Napi::String name = Napi::String::New(env, WidestringToString(variant.pwszVal));
    PropVariantClear(&variant);
    return name;
}

Napi::Value Device::Mute(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    IAudioEndpointVolume *volumeEndpoint = NULL;

    CheckOrThrowHR(
        env,
        this->_device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&volumeEndpoint));
    CheckOrThrowHR(
        env, volumeEndpoint->SetMute(1, NULL));
    CheckOrThrowHR(
        env, volumeEndpoint->Release());
    return Napi::Boolean::New(env, 1);
}

Napi::Value Device::Unmute(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    IAudioEndpointVolume *volumeEndpoint = NULL;

    CheckOrThrowHR(
        env,
        this->_device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&volumeEndpoint));
    CheckOrThrowHR(
        env, volumeEndpoint->SetMute(0, NULL));
    CheckOrThrowHR(
        env, volumeEndpoint->Release());
    return Napi::Boolean::New(env, 1);
}

Napi::Object Device::NewInstance(Napi::Value arg, IMMDevice *imm_device)
{
    Napi::Object obj = constructor.New({arg});
    Device *device = Napi::ObjectWrap<Device>::Unwrap(obj);
    device->_device = imm_device;
    return obj;
}