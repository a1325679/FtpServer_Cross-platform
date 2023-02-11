# 设置cmake的最低版本和项目名称
cmake_minimum_required(VERSION 3.0)
project(ftpserver)


message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME} ")
message("CMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM} ")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} ")
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM} ")
message("CMAKE_HOST_UNIX: ${CMAKE_HOST_UNIX} ")
message("CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32} ")

# 生成debug版本，可以进行gdb调试
set(CMAKE_BUILD_TYPE "Debug")


if(UNIX)
 
	message("current platform: Linux ")
 
elseif(WIN32)
 
	message("current platform: Windows ")
 
else()
 
	message("current platform: unkonw ")
 
endif()



# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/_include)

if(WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/thirdpart/libevent/include)
endif()
# 设置项目库文件搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)
# src包含了mprpc框架所有的相关代码
add_subdirectory(src)
#add_subdirectory(test)