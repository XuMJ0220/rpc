#ifndef MYRPCPROVIDER_H_
#define MYRPCPROVIDER_H_

#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

class MyRPCProvider{
    private:
        muduo::net::EventLoop m_eventLoop_;
        
        //新的socket连接回调
        void onConnect(const muduo::net::TcpConnectionPtr&);
        //已建立连接用户的读写事件回调
        void onMessage(const muduo::net::TcpConnectionPtr&,
                            muduo::net::Buffer*,
                            muduo::Timestamp);
    public:
        MyRPCProvider() = default;
        ~MyRPCProvider() = default;
        //这里是框架提供给外部使用的,可以发布rpc方法的接口汉书
        void NotifyService(google::protobuf::Service* service);
        //启动rpc服务节点,开始提供rpc远程网络调用服务
        void Run();
};

#endif