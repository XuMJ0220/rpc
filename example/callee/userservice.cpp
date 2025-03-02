#include "user.pb.h"
#include <string>

/*UserService是一个本地服务，提供了两个进程内的本地方法,Login和GetFriendLists*/
class UserService:public fixbug::UserServiceRpc{//使用在rpc服务发布端口(rpc服务提供者)
    private:
    public:
        bool Login(std::string name,std::string pwd){
            std::cout<<"Doing local service Login"<<std::endl;
            std::cout<<"name: "<<name<<" pwd: "<<pwd<<std::endl;
            return true;
        }

        //重写基类UserServiceRpc的虚函数,这面这些方法都是框架自动调用的
        //流程：
        //1.caller那边通过框架会发布一个Login(LoginRequest),经过muduo给到了callee
        //2.callee通过框架自动收到Login(LoginRequest),交到下面重写的这个Login方法上
        void Login(::google::protobuf::RpcController* controller,
                         const ::fixbug::LoginRequest* loginrequest,
                         ::fixbug::LoginResponse* loginresponse,
                         ::google::protobuf::Closure* done)
        {
            //框架给业务上报了请求参数LoginRequest,应用获取相应数据做本地服务
            std::string name = loginrequest->name();
            std::string pwd = loginrequest->pwd();

            //做本地业务
            bool login_result = Login(name,pwd);

            //把响应写入 包括错误码,错误消息,返回值
            fixbug::LoginResponse rsp;
            fixbug::ResultCode* rc = rsp.mutable_result();
            rc->set_errcode(0);
            rc->set_errmsg("");
            rsp.set_success(login_result);
            
            //执行回调操作 执行响应对象数据的序列化和网络发送(都是由框架完成)
            done->Run();
        }
};