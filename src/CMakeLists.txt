# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/_include)
include_directories(${PROJECT_SOURCE_DIR}/src/misc/log/include)
include_directories(${PROJECT_SOURCE_DIR}/src/misc/readconf/include)
include_directories(${PROJECT_SOURCE_DIR}/src/cmd_parse/include)
include_directories(${PROJECT_SOURCE_DIR}/src/threadpool/include)

add_subdirectory(threadpool)
add_subdirectory(app)
#add_subdirectory(logs)
#add_subdirectory(misc)