add_executable(util util.cpp )
target_link_libraries (util PUBLIC Terminal)
add_executable(codeline codeline.cpp)
target_link_libraries(codeline PUBLIC CodeLine)

add_executable(iline iline.cpp)
target_link_libraries(iline PUBLIC Iline)
