#ifndef MYRPCPROVIDER_H_
#define MYRPCPROVIDER_H_
#include "google/protobuf/service.h"
class MyRPCProvider{
    private:
        
    public:
        MyRPCProvider() = default;
        ~MyRPCProvider() = default;
        //这里是框架提供给外部使用的,可以发布rpc方法的接口汉书
        void NotifyService(google::protobuf::Service* service);
        //启动rpc服务节点,开始提供rpc远程网络调用服务
        void Run();
};

#endif