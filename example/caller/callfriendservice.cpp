#include <iostream>
#include "mprpcapplication.hpp"
#include "friend.pb.h"


int main(int argc, char** argv)
{
    // 整个程序启动以后，想使用框架，一定要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    diliu::FriendServiceRpc_Stub stub(new MprpcChannel());
    
    diliu::GetFriendsListRequest request;
    request.set_userid(1000);
    diliu::GetFriendsListResponse response;
    // 发起rpc方法的调用
    MprpcController controller;
    stub.GetFriendList(&controller, &request, &response, nullptr);

    // 一次rpc调用完成，读调用结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (response.result().errcode() == 0)
        {
            std::cout << "rpc getfriendlist response success: " << std::endl;
            int size = response.friends_size();
            for (int i = 0; i < size; i++)
            {
                std::cout << "index: " << (i + 1) << " name: " << response.friends(i) << std::endl;
            }
        }
        else
        {
            std::cout << "rpc getfriendlist response error: " << response.result().errmsg() << std::endl;
        }
    }
    return 0;
}