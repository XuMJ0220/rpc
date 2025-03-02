cmake_minimum_required(VERSION 3.0)

project(rpc)

#可执行文件输出地址
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#库文件输出地址
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thridparty)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
#库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

#添加子文件
add_subdirectory(example)
#add_subdirectory(src)