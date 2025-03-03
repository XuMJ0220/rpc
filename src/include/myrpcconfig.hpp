#ifndef MYRPCCONFIG_H_
#define MYRPCCONFIG_H_

#include <unordered_map>
#include <string>
class MyRPCConfig{
    private:
        //用来存放 rpcserver_ip rpcserver_port zookeeper_ip zookeeper_port 
        std::unordered_map<std::string,std::string> configMap_;
    public:
        //加载配置文件
        void LoadConfigFile(const char* config_file);
        //查询配置项信息
        std::string Load(const std::string &key);
};

#endif 