add_executable(fig3-1 fig3-1.c)
add_dependencies(fig3-1 apue_library)
target_link_libraries(fig3-1 apue_library)

add_executable(fig3-2 fig3-2.c)
add_dependencies(fig3-2 apue_library)
target_link_libraries(fig3-2 apue_library)

add_executable(fig3-5 fig3-5.c)
add_dependencies(fig3-5 apue_library)
target_link_libraries(fig3-5 apue_library)

add_executable(fig3-11 fig3-11.c)
add_dependencies(fig3-11 apue_library)
target_link_libraries(fig3-11 apue_library)
