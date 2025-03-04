#include <myrpcconfig.hpp>
#include <iostream>

//加载配置文件
void MyRPCConfig::LoadConfigFile(const char* config_file){

    FILE* pf = fopen(config_file,"r");//以只读的方式打开文件

    if(pf == nullptr){
        std::cerr<<config_file<<" is not exist"<<std::endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(pf)){//循环读完文件
        int idx;
        char buf[512] = {0};
        fgets(buf,512,pf);//读取一行,最多读取512个字节

        //处理读取到的字符串
        //对buf转为string类型，因为string有很多方法
        std::string buf_str(buf);

        //找到第一个不是空格的索引
        idx = buf_str.find_first_not_of(' ');
        if(idx!=-1){
            buf_str = buf_str.substr(idx,buf_str.size()-idx-1);//最后的-1是去掉了最后的\n还行
        }

        //找到倒数第一个不是空格的索引
        idx = buf_str.find_last_not_of(' ');
        if(idx!=-1){
            buf_str = buf_str.substr(0,idx+1);
        }
        //如果是注释，空行，舍去
        if(buf_str[0]=='#'||buf_str.empty()){
            continue;
        }

        idx = buf_str.find('=');

        //不合法
        if(idx==-1){
            continue;
        }
        //此时的sub_str就是我们要的了
        std::string key;
        std::string value;
        key = buf_str.substr(0,idx);
        value = buf_str.substr(idx+1,buf_str.size()-idx-1);
        configMap_.insert({key,value});
    }
}

//查询配置项信息
std::string MyRPCConfig::Load(const std::string &key){
    if(configMap_.find(key)!=configMap_.end()){
        return configMap_.find(key)->second;
    }
    return " 1";
}