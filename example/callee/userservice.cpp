#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"

class UserService : public diliu::UserServiceRpc  // 使用在RPC服务提供方
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std:: endl;
        std::cout << "name: " << name << " pwd:" << pwd << std:: endl;
        return true;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register" << std:: endl;
        std::cout << "id: " << id << " name: " << name << " pwd:" << pwd << std:: endl;
        return true;
    }

    /*
        1. caller ===> Login(LoginRequest) => muduo => callee
        2. callee ===> Login(LoginRequest) => 交到重写的Login方法
    */
    void Login(::google::protobuf::RpcController* controller,
                       const ::diliu::LoginRequest* request,
                       ::diliu::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest, 应用获取相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 本地业务
        bool login_result = Login(name, pwd);

        // 把响应写入
        diliu::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调函数 执行响应对象数据的序列化和网络发送
        done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                       const ::diliu::RegisterRequest* request,
                       ::diliu::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest, 应用获取相应数据做本地业务
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 本地业务
        bool ret = Register(id, name, pwd);

        // 把响应写入
        diliu::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(ret);

        // 执行回调函数 执行响应对象数据的序列化和网络发送
        done->Run();
    }                   
};

int main(int argc, char** argv)
{
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点
    RpcProvider provider;
    provider.NotifyService(new UserService());

    // 启动一个rpc服务发布节点 Run以后进入阻塞状态 等待远程的rpc调用请求
    provider.Run();

    return 0;
}