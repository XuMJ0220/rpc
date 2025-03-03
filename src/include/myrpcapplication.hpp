#ifndef MYRPCAPPLICATION_H_
#define MYRPCAPPLICATION_H_

#include <myrpcconfig.hpp>
//这里主要是为了进行初始化,所以可以设置成单例模式
class MyRPCApplication{
    private:
        static MyRPCApplication instance;

        MyRPCApplication() = default;
        ~MyRPCApplication() = default;
        MyRPCApplication(const MyRPCApplication&) = delete;
        MyRPCApplication& operator=(const MyRPCApplication&) = delete;
        MyRPCApplication(MyRPCApplication&&){}

        static MyRPCConfig myRPCConfig_;
    public:
        static void Init(int argc,char** argv);
        static MyRPCApplication& getInstance();
};

#endif