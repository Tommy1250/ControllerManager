#include <napi.h>

bool DisconnectBT(const std::string& mac);

Napi::Boolean DisconnectWrapped(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString())
        return Napi::Boolean::New(env, false);

    std::string mac = info[0].As<Napi::String>();
    bool result = DisconnectBT(mac);

    return Napi::Boolean::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        "disconnectBT",
        Napi::Function::New(env, DisconnectWrapped)
    );
    return exports;
}

NODE_API_MODULE(btaddon, Init)
