set(SRC_LIST main.cpp)

include_directories(
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

add_executable(FASM ${SRC_LIST})
#target_link_libraries(ferry config ${Boost_LIBRARIES})