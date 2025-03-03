#include "myrpcapplication.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
void ShowArgsHelp(){
    std::cerr<<"format: command -i <configfile>"<<std::endl;
}

MyRPCApplication MyRPCApplication::instance;

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
            std::cout<<argv[0]<<" "<<"-i "<<getopt<<std::endl;
            config_file = optarg;
            break;
        case '?':
            std::cout<<"Invalid args!"<<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            std::cout<<"Need <configfile>"<<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
}

MyRPCApplication& MyRPCApplication::getInstance(){
    return instance;
}