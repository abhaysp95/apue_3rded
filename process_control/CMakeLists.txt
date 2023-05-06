add_executable(fig8-1 fig8-1.c)
add_dependencies(fig8-1 apue_library)
target_link_libraries(fig8-1 apue_library)

add_executable(fig8-3 fig8-3.c)
add_dependencies(fig8-3 apue_library)
target_link_libraries(fig8-3 apue_library)
