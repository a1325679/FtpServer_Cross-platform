# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(FtpServer ${SRC_LIST} 
${CMAKE_CURRENT_SOURCE_DIR}/../misc/log/log.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../misc/readconf/func.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../misc/readconf/read_conf.cpp
)
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(FtpServer event pthread)
if(WIN32)
	target_link_libraries(FtpServer Iphlpapi.lib event_extra event_core ws2_32)
endif()