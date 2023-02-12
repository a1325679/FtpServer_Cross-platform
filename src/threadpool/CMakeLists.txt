# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)
add_library(threadpool ${SRC_LIST})
target_link_libraries(threadpool pthread event)