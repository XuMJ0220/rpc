#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;
using namespace std;

int main(){
    // LoginRequest req;
    // req.set_name("zhang san");
    // req.set_pwd("123456");
    // //进行字符串序列化
    // string send_str;
    // if(req.SerializeToString(&send_str)){
    //     cout<<send_str<<endl;
    // }

    // //进行反序列化
    // LoginRequest rreq;
    // if(rreq.ParseFromString(send_str)){
    //     cout<<rreq.name()<<endl;
    //     cout<<rreq.pwd()<<endl;
    // }

    // LoginResponse rsp;
    // ResultCode* rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登陆处理失败了");
    // rsp.set_success("否");

    GetFriendListsResponse rsp;
    ResultCode* rc = rsp.mutable_result();
    rc->set_errcode(0);

    User* user1 = rsp.add_friend_list();
    user1->set_name("zhang san");
    user1->set_sex(User::MAN);
    user1->set_age(18);
    std::cout<<rsp.friend_list_size()<<std::endl;
    

    return 0;
}