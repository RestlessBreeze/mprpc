#pragma once
#include "mprpcconfig.hpp"
#include "mprpccontroller.hpp"
#include "mprpcchannel.hpp"

// mprpc框架的初始化类
class MprpcApplication
{
public:
    static void Init(int argc, char** argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& GetConfig();

private:
    static MprpcConfig m_config;
    MprpcApplication() {}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};