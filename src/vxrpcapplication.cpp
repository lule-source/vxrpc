#include "vxrpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

VxrpcConfig VxrpcApplication::v_config;

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}

void VxrpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件
    v_config.LoadConfigFile(config_file.c_str());
}

VxrpcApplication &VxrpcApplication::GetInstance()
{
    static VxrpcApplication app;
    return app;
}

VxrpcConfig &VxrpcApplication::GetConfig()
{
    return v_config;
}