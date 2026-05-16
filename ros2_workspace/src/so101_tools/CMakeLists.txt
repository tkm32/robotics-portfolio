cmake_minimum_required(VERSION 3.16)
project(so101_tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# feetech_driverをサブディレクトリとして追加（ヘッダーとライブラリを直接利用）
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../feetech_ros2_driver/feetech_driver
                 ${CMAKE_CURRENT_BINARY_DIR}/feetech_driver)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_executable(calibration src/calibration.cpp)
target_link_libraries(calibration serial_port communication_protocol fmt::fmt spdlog::spdlog)

add_executable(demo_motion src/demo_motion.cpp)
target_link_libraries(demo_motion serial_port communication_protocol fmt::fmt spdlog::spdlog)
