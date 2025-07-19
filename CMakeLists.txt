# CMake 最小版本号
cmake_minimum_required(VERSION 3.10)

# 项目声明
project(CMakeHomework)

# 设置 C++ 标准,17最现代
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查包
find_package(OpenCV REQUIRED)

# 添加可执行文件
add_executable(main main.cpp
${CMAKE_SOURCE_DIR}/modules/M1/src/M1.cpp 
${CMAKE_SOURCE_DIR}/modules/M2/src/M2.cpp 
${CMAKE_SOURCE_DIR}/modules/A1/src/A11.cpp 
${CMAKE_SOURCE_DIR}/modules/A1/src/A12.cpp 
${CMAKE_SOURCE_DIR}/modules/A1/src/A13.cpp 
${CMAKE_SOURCE_DIR}/modules/A2/src/A2.cpp
)

#连接头文件
target_include_directories(main PRIVATE
${CMAKE_SOURCE_DIR}/modules/A1/include
${CMAKE_SOURCE_DIR}/modules/A2/include
${CMAKE_SOURCE_DIR}/modules/M1/include
${CMAKE_SOURCE_DIR}/modules/M2/include
${CMAKE_SOURCE_DIR}/common/math/include
${CMAKE_SOURCE_DIR}/common/kalman/include
)

# 链接 OpenCV 库
target_link_libraries(main PRIVATE ${OpenCV_LIBS})

