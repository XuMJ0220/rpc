#include "myrpcprovider.hpp"
#include <string>
#include <functional>
#include <myrpcapplication.hpp>
#include <google/protobuf/descriptor.h>
void MyRPCProvider::NotifyService(google::protobuf::Service* service){
    //获得传进来的服务的信息描述
    const google::protobuf::ServiceDescriptor* pserviceDesc = service->GetDescriptor();
    //获得服务的名字
    const std::string service_name= pserviceDesc->name();
    std::cout<<"service_name: "<<service_name<<std::endl;
    //获得服务中方法的数量
    int methodCont = pserviceDesc->method_count();

    //for(int i = 0;i<methodCont;i++){
    //    const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);//获得该服务下的每个方法的描述
    //}

    ServiceInfo serviceInfo;//创建记录服务信息的结构体
    serviceInfo.service_  = service;
    for(int i = 0;i<methodCont;i++){//把服务中的方法都装进map中
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);//获得该服务下的每个方法的描述
        std::string method_name = pmethodDesc->name();//服务中方法的名字
        std::cout<<"method_name: "<<method_name<<std::endl;
        serviceInfo.methodMap_.insert({method_name,pmethodDesc});
    }
    //往serviceMap_中装入这个服务
    serviceMap_.insert({service_name,serviceInfo});
}

void MyRPCProvider::Run(){
    //获得ip+port
    std::string ip = MyRPCApplication::getInstance().GetConfig().Load("rpcserverip");
    std::string port = MyRPCApplication::getInstance().GetConfig().Load("rpcserverport");
    //组合ip+port
    muduo::net::InetAddress address(ip,atoi(port.c_str()));

    //创建TCP线程对象
    muduo::net::TcpServer server_(&m_eventLoop_,
            address,
            "RpcProvider");

    server_.setConnectionCallback(std::bind(&MyRPCProvider::onConnect,this,std::placeholders::_1));
    server_.setMessageCallback(std::bind(&MyRPCProvider::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    //设置muduo库的线程数量
    server_.setThreadNum(4);

    std::cout<<"RpcProvider start service at ip: "<<ip<<" port: "<<port<<std::endl;
    //启动
    server_.start();
    m_eventLoop_.loop();
}

//新的socket连接回调
void MyRPCProvider::onConnect(const muduo::net::TcpConnectionPtr&){
    std::cout<<"hello"<<std::endl;
}


//已建立连接用户的读写事件回调
void MyRPCProvider::onMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buf,
                            muduo::Timestamp ts)
{
    std::cout<<"hi"<<std::endl;     
}