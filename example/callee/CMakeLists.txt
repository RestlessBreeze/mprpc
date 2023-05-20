set(SRC_LIST userservice.cpp ../user.pb.cc)

add_executable(provider ${SRC_LIST})
target_link_libraries(provider mprpc protobuf)


set(SRC_LIST2 friendservice.cpp ../friend.pb.cc)

add_executable(provider2 ${SRC_LIST2})
target_link_libraries(provider2 mprpc protobuf)