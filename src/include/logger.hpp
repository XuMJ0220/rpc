#ifndef LOGGER_H_
#define LOGGER_H_

#include "lockqueue.hpp"

enum LogLevel{
    INFO,//普通信息
    ERROR,//错误信息
};

//设置成单例模式
class Logger{
    private:
        int loglevel_;//记录日志级别
        LockQueue<std::string> lckQue_;//日志缓存队列

        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    public:
        //获取日志的单例
        static Logger& GetInstance();
        //设置日志级别
        void SetLogLevel(LogLevel level);
        //写日志
        void Log(std::string msg);
};

//定义宏
#define LOG_INFO(logmsgarg,...)\
    do\
    {\
        Logger& logger = Logger::GetInstance();  \
        logger.SetLogLevel(LogLevel::INFO);    \
        char c[1024] = {0}; \
        snprintf(c,1024,logmsgarg,##__VA_ARGS__);\
        logger.Log(std::string(c));\
    } while(0);

#define LOG_ERR(logmsgarg,...)\
    do \
    {\
        Logger& logger = Logger::GetInstance();   \
        logger.SetLogLevel(LogLevel::ERROR);\
        char c[1024] = {0};\
        snprintf(c,1024,logmsgarg,##__VA_ARGS__);\
        logger.Log(std::string(c));\
    }while(0);
#endif