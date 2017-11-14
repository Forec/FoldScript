set(SRC_LIST main.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/utils
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
        ${PROJECT_SOURCE_DIR}/include/fasm/component
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

find_package(gflags REQUIRED)

add_executable(fasm ${SRC_LIST})

target_link_libraries(
        fasm
        fasm-utils
        fasm-framework
        fasm-component
        gflags
)