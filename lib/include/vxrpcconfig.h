#pragma once

#include <unordered_map>
#include <string>

class VxrpcConfig
{
public:
    void LoadConfigFile(const char *config_file);
    std::string Load(const std::string &key);

private:
    std::unordered_map<std::string, std::string> v_configMap;

    void Trim(std::string &src_buf);
};
