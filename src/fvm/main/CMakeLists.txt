set(SRC_LIST main.cpp)

include_directories(
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

find_package(gflags REQUIRED)

add_executable(FVM ${SRC_LIST})

target_link_libraries(
        FVM
        gflags
)