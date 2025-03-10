#include "myrpccontroller.hpp"

MyRPCController::MyRPCController(){
    failed_ = false;
    errText_ = "";
}

void MyRPCController::Reset(){
    failed_ = false;
    errText_ = "";
}

bool MyRPCController::Failed() const{
    return failed_;
}

std::string MyRPCController::ErrorText() const{
    return errText_;
}

void MyRPCController::SetFailed(const std::string& reason){
    failed_ = true;
    errText_ = reason;
}

//目前未实现的功能
void MyRPCController::StartCancel(){
}

bool MyRPCController::IsCanceled() const{
    return false;
}

void MyRPCController::NotifyOnCancel(google::protobuf::Closure* callback){
}