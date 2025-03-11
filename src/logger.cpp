#include "logger.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
Logger& Logger::GetInstance(){
    static Logger logger;
    return logger;
}

Logger::Logger(){
    std::thread t([&]()->void{
        //启动专门的写日志线程
        for(;;){
            //获取当前年月日以及具体时间
            //获取但前时间点
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            //转换为本地时间结构体(localtime)
            std::tm* local_tm = std::localtime(&now_time);
            //转为字符串
            std::stringstream ss;
            ss<<std::put_time(local_tm,"%Y-%m-%d");
            std::string file_name = ss.str();
            //清除ss缓冲区
            ss.str(std::string());
            ss.clear();
            ss<<std::put_time(local_tm,"%H:%M:%S");
            std::string time_now = ss.str();
            //清除ss缓冲区
            ss.str(std::string());
            ss.clear();

            FILE* pf = fopen(file_name.c_str(),"a+");//日志文件
            if(pf==nullptr){
                std::cout<<"logger file: "<<file_name<<" open error!"<<std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = time_now+lckQue_.Pop();//格式是当前 时:分:秒 + 队列头部的东西
            msg.append("\n");

            fputs(msg.c_str(),pf);//把msg的内容输出到pf文件中
            fclose(pf);
        }
    });
    //设置分离线程 守护线程
    t.detach();
}

//设置日志级别
void Logger::SetLogLevel(LogLevel level){
    loglevel_ = level;
}

//写日志
void Logger::Log(std::string msg){
    lckQue_.Push(msg);
}