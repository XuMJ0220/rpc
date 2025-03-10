#ifndef MYRPCCONTROLLER_H_
#define MYRPCCONTROLLER_H_

#include <google/protobuf/service.h>
#include <string>

class MyRPCController:public google::protobuf::RpcController{
    private:
        bool failed_;//RPC方法执行过程中的状态
        std::string errText_;//RPC方法执行过程中的错误信息
    public:
        MyRPCController();
        void Reset();
        bool Failed() const;
        std::string ErrorText() const;
        void SetFailed(const std::string& reason);

        //目前未实现的功能
        void StartCancel();
        bool IsCanceled() const;
        void NotifyOnCancel(google::protobuf::Closure* callback);
};

#endif 
