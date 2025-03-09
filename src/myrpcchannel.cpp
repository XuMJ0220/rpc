#include "myrpcchannel.hpp"
#include "myrpcapplication.hpp"
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "rpcheader.pb.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
//header_size+service_name+method_name+args_size+args
void MyRPCChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                        google::protobuf::RpcController* controller,
                        const google::protobuf::Message* request,
                        google::protobuf::Message* response,
                        google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* pservicedescriptor = method->service();

    //service_name
    std::string service_name = pservicedescriptor->name();
    //method_name
    std::string method_name = method->name();
    //args_size
    uint32_t args_size = 0;
    std::string args_str;
    if(request->SerializeToString(&args_str)){
        args_size = args_str.size();
    }else{
        std::cerr<<"serialize request error"<<std::endl;
    }
    //header_size
    uint32_t header_size = 0;
    myrpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);
    //进行序列化
    std::string rpc_header_str;
    if(rpcHeader.SerializeToString(&rpc_header_str)){
        header_size = rpc_header_str.size();
    }else{
        std::cerr<<"serialize rpc header error"<<std::endl;
    }

    //组织代发送的rpc请求
    std::string send_rpc_str;
    send_rpc_str.insert(0,std::string((char*)&header_size,4));//header_size
    send_rpc_str+=rpc_header_str;//rpcheader
    send_rpc_str+=args_str;//args

    //打印调试信息
    std::cout<<"==========================================================="<<std::endl;
    std::cout<<"header_size: "<<header_size<<std::endl;
    std::cout<<"rpc_header_str: "<<rpc_header_str<<std::endl;
    std::cout<<"service_name: "<<service_name<<std::endl;
    std::cout<<"method_name: "<<method_name<<std::endl;
    std::cout<<"args_str: "<<args_str<<std::endl;
    std::cout<<"==========================================================="<<std::endl;

    //使用tcp编成，完成rpc方法的远程调用
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1==clientfd){
        std::cerr<<"create socket error! errno: "<<errno<<std::endl;
        exit(EXIT_FAILURE);
    }

    //读取配置文件
    std::string ip = MyRPCApplication::GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MyRPCApplication::GetConfig().Load("rpcserverport").c_str());

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    //连接
    if(-1==connect(clientfd,(sockaddr*)&server_addr,sizeof(server_addr))){
        std::cerr<<"connect error,errno: "<<errno<<std::endl;
        close(clientfd);
        exit(EXIT_FAILURE);
    }

    //发送rpc请求
    if(-1==send(clientfd,send_rpc_str.c_str(),sizeof(send_rpc_str),0)){
        std::cout<<"send error,errno: "<<errno<<std::endl;
        close(clientfd);
        return;
    }

    //接受rpc请求的响应
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1==(recv_size=recv(clientfd,recv_buf,1024,0))){
        std::cerr<<"recv error,errno: "<<errno<<std::endl;
        close(clientfd);
        return;
    }

    //将得到的结果进行反序列化
    std::string response_str(recv_buf,0,recv_size);
    if(!response->ParseFromString(response_str)){
        std::cout<<"parse error! response_str:"<<response_str<<std::endl;
        close(clientfd);
        return;
    }
    close(clientfd);
}