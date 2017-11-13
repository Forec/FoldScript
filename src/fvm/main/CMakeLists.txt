set(SRC_LIST main.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fvm/framework
        ${PROJECT_SOURCE_DIR}/include/fvm/utils
        ${PROJECT_SOURCE_DIR}/include/fvm/vm
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

find_package(gflags REQUIRED)

add_executable(FVM ${SRC_LIST})

target_link_libraries(
        FVM
        gflags
        fvm-utils
        fvm-framework
        fvm-vm
)