#pragma once

#include "vxrpcconfig.h"

class VxrpcApplication
{
public:
    static void Init(int agrc, char **argv);
    static VxrpcApplication &GetInstance();
    static VxrpcConfig &GetConfig();

private:
    static VxrpcConfig v_config;

    VxrpcApplication() {}
    VxrpcApplication(const VxrpcApplication &) = delete;
    VxrpcApplication(VxrpcApplication &&) = delete;
};