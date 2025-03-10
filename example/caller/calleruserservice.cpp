#include "user.pb.h"
#include "myrpcapplication.hpp"
#include "google/protobuf/service.h"
#include "user.pb.h"
#include "myrpcchannel.hpp"
#include <string>
#include "myrpccontroller.hpp"
void setLoginRequest(fixbug::LoginRequest* request,std::string name,std::string pwd);

int main(int argc,char** argv){
    //char* argvv[] = {"./consumer","-i","/home/xumj/项目/rpc/bin/test.txt"};
    //初始化框架，一定要先调用框架的初始化函数(只需要调用一次)
    MyRPCApplication::Init(argc,argv);
    //演示调用远程发布的rpc方法的Login
    //UserServiceRpc_Stub需要传入一个RpcChannel*,当调用stub.Login的时候，其实本质
    //失去调用RpcChannel*的CallMethod
    fixbug::UserServiceRpc_Stub stub(new MyRPCChannel());

    fixbug::LoginRequest request;
    //setLoginRequest(request,"zhang san","123456");
    request.set_name("zhang san");
    request.set_pwd("123456");
    fixbug::LoginResponse response;

    //加入PRCController
    MyRPCController controller;
    //stub.Login(nullptr,&request,&response,nullptr);    
    stub.Login(&controller,&request,&response,nullptr);    

    if(controller.Failed()){
        std::cout<<controller.ErrorText()<<std::endl;
    }else{
         //来到了这里就是得到了response
        if(0==response.mutable_result()->errcode()){
            std::cout<<"rpc login response success: "<<response.success()<<std::endl;
            std::cout<<"msg: "<<response.mutable_result()->errmsg()<<std::endl;
        }else{
            std::cerr<<"rpc login response error: "<<response.result().errmsg()<<std::endl;
        }
    }  
    return 0;
}

void setLoginRequest(fixbug::LoginRequest* request,std::string name,std::string pwd){
    request->set_name(name);
    request->set_pwd(pwd);
}