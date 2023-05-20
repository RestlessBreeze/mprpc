#include <iostream>
#include "mprpcapplication.hpp"
#include "mprpcchannel.hpp"
#include "user.pb.h"

int main(int argc, char** argv)
{
    // 整个程序启动以后，想使用框架，一定要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    diliu::UserServiceRpc_Stub stub(new MprpcChannel());
    
    diliu::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    diliu::LoginResponse response;
    // 发起rpc方法的调用
    MprpcController controller;
    stub.Login(&controller, &request, &response, nullptr);

    // 一次rpc调用完成，读调用结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (response.result().errcode() == 0)
        {
            std::cout << "rpc login response success: " << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
        }
    }

    // 演示调用远程发布的rpc方法Register
    diliu::RegisterRequest req;
    req.set_id(2000);
    req.set_name("zhang san");
    req.set_pwd("123456");
    diliu::RegisterResponse rsp;
    // 发起rpc方法的调用
    controller.Reset();
    stub.Register(&controller, &req, &rsp, nullptr);

    // 一次rpc调用完成，读调用结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (rsp.result().errcode() == 0)
        {
            std::cout << "rpc register response success: " << rsp.success() << std::endl;
        }
        else
        {
            std::cout << "rpc register response error: " << rsp.result().errmsg() << std::endl;
        }
    }

    return 0;
}