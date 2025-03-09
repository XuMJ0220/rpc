#include "myrpcchannel.hpp"
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "rpcheader.pb.h"
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

}