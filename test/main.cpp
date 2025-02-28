#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;
using namespace std;

int main(){
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");
    //进行字符串序列化
    string send_str;
    if(req.SerializeToString(&send_str)){
        cout<<send_str<<endl;
    }

    //进行反序列化
    LoginRequest rreq;
    if(rreq.ParseFromString(send_str)){
        cout<<rreq.name()<<endl;
        cout<<rreq.pwd()<<endl;
    }
    return 0;
}