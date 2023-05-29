add_executable(fig10-2 fig10-2.c)
add_dependencies(fig10-2 apue_library)
target_link_libraries(fig10-2 apue_library)

add_executable(fig10-5 fig10-5.c)
add_dependencies(fig10-5 apue_library)
target_link_libraries(fig10-5 apue_library)

add_executable(fig10-6 fig10-6.c)
add_dependencies(fig10-6 apue_library)
target_link_libraries(fig10-6 apue_library)

add_executable(fig10-9 fig10-9.c fig10-8.c)
add_dependencies(fig10-9 apue_library)
target_link_libraries(fig10-9 apue_library)
