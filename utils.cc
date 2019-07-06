#include <napi.h>
#include <comdef.h>
#include <stdio.h>
#include <system_error>

std::string WidestringToString(std::wstring wstr)
{
    if (wstr.empty())
    {
        return std::string();
    }
    int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), NULL, 0, NULL, NULL);
    std::string ret = std::string(size, 0);
    WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), &ret[0], size, NULL, NULL);
    return ret;
}

void CheckOrThrowHR(Napi::Env env, HRESULT HR)
{
    if (FAILED(HR))
    {
        throw Napi::Error::New(env, std::system_category().message(HR));
    }
}