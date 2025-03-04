aux_source_directory(. SRC_LIST)
#add_library(myrpc SHARED ${SRC_LIST})
#在这里，由于muduo网络库都是静态库,而我们要创建的myrpc这个库又依赖于muduo,所以只能创建成静态库
add_library(myrpc ${SRC_LIST})

target_link_libraries(myrpc muduo_net muduo_base pthread)