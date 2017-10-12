set(SRC_LIST utils.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/utils
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
)

add_library(fasm-utils STATIC ${SRC_LIST})
