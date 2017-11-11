set(
        SRC_LIST
        vm.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fvm/vm
)

add_library(fvm-vm STATIC ${SRC_LIST})
