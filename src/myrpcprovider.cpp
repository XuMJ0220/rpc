#include "myrpcprovider.hpp"
#include <string>
#include <functional>
#include <myrpcapplication.hpp>
#include <google/protobuf/descriptor.h>
#include <rpcheader.pb.h>
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
void MyRPCProvider::onConnect(const muduo::net::TcpConnectionPtr& conn){
    if(!conn->connected()){
        //连接失败时
        conn->shutdown();
    }
}

/*
    在框架内部，RpcProvider和RpcConsummer协商好之间通信的protobuf数据类型
    service_name method_name args 定义proto的message类型，进行数据头的序列化和反序列化
                                  service_name method_name args_size
*/
//已建立连接用户的读写事件回调
void MyRPCProvider::onMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buf,
                            muduo::Timestamp ts)
{
    //网络上接受的远程rpc调用请求的字符流
    std::string recv_buf = buf->retrieveAllAsString();

    //recv_buf例子：16UserServiceLoginzhang san123456

    //这里的recv_buf的前四个字节会是headr的大小
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size,4,0);//把recv_buf前四个字节的内容，从偏移为0的地方开始的内容放入header_size
    
    //根据header_size读取数据头的原始字符流,反序列化数据,得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4,header_size);
    //反序列化
    std::string service_name;
    std::string method_name;
    uint32_t args_size;
    myrpc::RpcHeader rpcHeader;
    if(rpcHeader.ParseFromString(rpc_header_str)){
        //反序列化成功
        service_name=rpcHeader.service_name();
        method_name=rpcHeader.method_name();
        args_size=rpcHeader.args_size();
    }else{
        //序列化失败
        std::cerr<<"反序列化:"<<rpc_header_str<<"失败"<<std::endl;
    }

    //获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4+header_size,args_size);

    //打印调试信息
    std::cout<<"==================================================="<<std::endl;
    std::cout<<"header_size: "<<header_size<<std::endl;
    std::cout<<"service_name: "<<service_name<<std::endl;
    std::cout<<"method_name: "<<method_name<<std::endl;
    std::cout<<"rpc_header_str: "<<rpc_header_str<<std::endl;
    std::cout<<"args_str: "<<args_str<<std::endl;
    std::cout<<"==================================================="<<std::endl;

}