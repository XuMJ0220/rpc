#include "myrpcprovider.hpp"
#include <string>
#include <functional>
#include <myrpcapplication.hpp>
void MyRPCProvider::NotifyService(google::protobuf::Service* service){

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