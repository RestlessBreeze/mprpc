#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.hpp"
#include "rpcprovider.hpp"
#include "logger.hpp"

class FriendService : public diliu::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        std::cout << "do GetFriendsList service!";
        std::vector<std::string> vec;
        vec.push_back("zhang san");
        vec.push_back("li si");
        vec.push_back("wang wu");
        return vec;
    }

    void GetFriendList(::google::protobuf::RpcController* controller,
                       const ::diliu::GetFriendsListRequest* request,
                       ::diliu::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest, 应用获取相应数据做本地业务
        uint32_t userid = request->userid();

        // 本地业务
        std::vector<std::string> friendList = GetFriendsList(userid);

        // 把响应写入
        diliu::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        for (std::string& name : friendList)
        {
            std::string* p = response->add_friends();
            *p = name;
        }

        // 执行回调函数 执行响应对象数据的序列化和网络发送
        done->Run();
    }
};

int main(int argc, char** argv)
{
    LOG_INFO("first log message!");
    LOG_ERROR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个rpc服务发布节点 Run以后进入阻塞状态 等待远程的rpc调用请求
    provider.Run();

    return 0;
}