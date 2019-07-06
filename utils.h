#include <napi.h>
#include <comdef.h>
#include <stdio.h>
#include <system_error>

std::string WidestringToString(std::wstring wstr);
void CheckOrThrowHR(Napi::Env env, HRESULT HR);
