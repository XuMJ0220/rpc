set(SRC_LIST calleruserservice.cpp ../user.pb.cc)

add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer myrpc protobuf)