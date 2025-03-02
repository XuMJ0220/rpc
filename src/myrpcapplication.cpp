#include "myrpcapplication.hpp"

MyRPCApplication MyRPCApplication::instance;

void MyRPCApplication::Init(int argc,char** argv){

}

MyRPCApplication& MyRPCApplication::getInstance(){
    return instance;
}