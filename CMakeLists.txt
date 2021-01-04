# cmake版本
cmake_minimum_required(VERSION 3.17)
# 工程名字
project(h3d)
# c++标准版本
set(CMAKE_CXX_STANDARD 11)

####################
# Build on MacOSX #
####################
if (APPLE)
    #    set(GLFW_INCLUDE_DIR ./include)
    set(GLFW_LIB_DIR ./lib_mac)
endif (APPLE)

####################
# Build on Windows #
####################
if (WIN32)
    #    set(GLFW_INCLUDE_DIR ./include)
    set(GLFW_LIB_DIR ./lib_win)
endif (WIN32)


# 头文件搜索目录
include_directories(
        include
        src
        src/math
)

# 保存目录变量
aux_source_directory(. DIR_root)
aux_source_directory(./src DIR_src)

# 链接库目录
link_directories(${GLFW_LIB_DIR})

# 指定生成目标
add_executable(demo ${DIR_root} ${DIR_src})

# 链接目标库
target_link_libraries(demo glfw)