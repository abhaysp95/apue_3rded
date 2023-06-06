add_executable(fig10-2 fig10-2.c)
add_dependencies(fig10-2 apue_library)
target_link_libraries(fig10-2 apue_library)

add_executable(fig10-5 fig10-5.c)
add_dependencies(fig10-5 apue_library)
target_link_libraries(fig10-5 apue_library)

add_executable(fig10-6 fig10-6.c)
add_dependencies(fig10-6 apue_library)
target_link_libraries(fig10-6 apue_library)

add_executable(fig10-8 fig10-8.c)
add_dependencies(fig10-8 apue_library)
target_link_libraries(fig10-8 apue_library)

add_executable(fig10-8_updated fig10-8_updated.c)
add_dependencies(fig10-8_updated apue_library)
target_link_libraries(fig10-8_updated apue_library)

add_executable(fig10-9 fig10-9.c fig10-8.c)
add_dependencies(fig10-9 apue_library)
target_link_libraries(fig10-9 apue_library)

add_executable(fig10-10 fig10-10.c)
add_dependencies(fig10-10 apue_library)
target_link_libraries(fig10-10 apue_library)

add_executable(fig10-11 fig10-11.c)
add_dependencies(fig10-11 apue_library)
target_link_libraries(fig10-11 apue_library)

add_executable(fig10-15 fig10-15.c)
add_dependencies(fig10-15 apue_library)
target_link_libraries(fig10-15 apue_library)

add_executable(fig10-15_test fig10-15_test.c)
add_dependencies(fig10-15_test apue_library)
target_link_libraries(fig10-15_test apue_library)

add_executable(fig10-20 fig10-20.c fig10-14.c)
add_dependencies(fig10-20 apue_library)
target_link_libraries(fig10-20 apue_library)

add_executable(fig10-22 fig10-22.c fig10-14.c fig10-18.c)
add_dependencies(fig10-22 apue_library)
target_link_libraries(fig10-22 apue_library)

add_executable(fig10-23 fig10-23.c)
add_dependencies(fig10-23 apue_library)
target_link_libraries(fig10-23 apue_library)
