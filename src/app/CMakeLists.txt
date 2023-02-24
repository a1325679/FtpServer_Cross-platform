# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(FtpServer ${SRC_LIST} 
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_factory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_task.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_user.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_server_cmd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_pwd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_port.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_list.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_cudp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_cwd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_mkd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_rmd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_retr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_stor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_dele.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_rnfr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../cmd_parse/ftp_rnto.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../misc/log/log.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../misc/readconf/read_conf.cpp
)
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(FtpServer event pthread threadpool)
if(WIN32)
	target_link_libraries(FtpServer Iphlpapi.lib event_extra event_core ws2_32)
endif()