#include "user.pb.h"
#include "myrpcapplication.hpp"
#include "google/protobuf/service.h"
#include "user.pb.h"
#include "myrpcchannel.hpp"
#include <string>

fixbug::LoginRequest* setLoginRequest(std::string name,std::string pwd);

int main(int argc,char** argv){
    //初始化框架，一定要先调用框架的初始化函数(只需要调用一次)
    MyRPCApplication::Init(argc,argv);
    //演示调用远程发布的rpc方法的Login
    //UserServiceRpc_Stub需要传入一个RpcChannel*,当调用stub.Login的时候，其实本质
    //失去调用RpcChannel*的CallMethod
    fixbug::UserServiceRpc_Stub stub(new MyRPCChannel());

    fixbug::LoginRequest* request = setLoginRequest("zhang san","123456");
    fixbug::LoginResponse* response;

    stub.Login(nullptr,request,response,nullptr);    

    //来到了这里就是得到了response
    if(0==response->result().errcode()){
        std::cout<<"rpc login response success: "<<response->success()<<std::endl;
    }else{
        std::cerr<<"rpc login response error: "<<response->result().errmsg()<<std::endl;
    }
    return 0;
}

fixbug::LoginRequest* setLoginRequest(std::string name,std::string pwd){
    fixbug::LoginRequest* request;
    request->set_name(name);
    request->set_pwd(pwd);
    return request;
}