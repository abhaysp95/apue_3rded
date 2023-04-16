unset(s)

add_executable(fig2-16 fig2-16.c)
add_dependencies(fig2-16 apue_library)
target_link_libraries(fig2-16 apue_library)

add_executable(fig2-17 fig2-17.c)
add_dependencies(fig2-17 apue_library)
target_link_libraries(fig2-17 apue_library)
