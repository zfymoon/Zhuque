cmake_minimum_required(VERSION 3.10)
project(zhuque)
set(CMAKE_CXX_STANDARD 11)
# include_directories(.)
aux_source_directory(. DIR_SRCS)

find_package( Threads )
add_executable( zhuque ${DIR_SRCS})
target_link_libraries( zhuque ${CMAKE_THREAD_LIBS_INIT} )
