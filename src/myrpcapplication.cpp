#include "myrpcapplication.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
void ShowArgsHelp(){
    std::cerr<<"format: command -i <configfile>"<<std::endl;
}

MyRPCApplication MyRPCApplication::instance;
MyRPCConfig MyRPCApplication::myRPCConfig_;

void MyRPCApplication::Init(int argc,char** argv){
    //command -i <config_file>

    if(argc<2){
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    std::string config_file;
    int c = 0;
    while((c = getopt(argc,argv,"i:"))!=-1){
        switch (c)
        {
        case 'i':
            //std::cout<<argv[0]<<" "<<"-i "<<getopt<<std::endl;
            config_file = optarg;
            break;
        case '?':
            //std::cout<<"Invalid args!"<<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            //std::cout<<"Need <configfile>"<<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    myRPCConfig_.LoadConfigFile(config_file.c_str());

    std::cout<<"rpcserverip:"<<myRPCConfig_.Load("rpcserverip")<<std::endl;
    std::cout<<"rpcserverport:"<<myRPCConfig_.Load("rpcserverport")<<std::endl;
    std::cout<<"zookeeperip:"<<myRPCConfig_.Load("zookeeperip")<<std::endl;
    std::cout<<"zookeeperport:"<<myRPCConfig_.Load("zookeeperport")<<std::endl;
}

MyRPCApplication& MyRPCApplication::getInstance(){
    return instance;
}