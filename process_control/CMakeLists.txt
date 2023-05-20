add_executable(fig8-1 fig8-1.c)
add_dependencies(fig8-1 apue_library)
target_link_libraries(fig8-1 apue_library)

add_executable(fig8-3 fig8-3.c)
add_dependencies(fig8-3 apue_library)
target_link_libraries(fig8-3 apue_library)

add_executable(fig8-6 fig8-6.c)
add_dependencies(fig8-6 apue_library)
target_link_libraries(fig8-6 apue_library)

add_executable(fig8-8 fig8-8.c)
add_dependencies(fig8-8 apue_library)
target_link_libraries(fig8-8 apue_library)

add_executable(fig8-12 fig8-12.c)
add_dependencies(fig8-12 apue_library)
target_link_libraries(fig8-12 apue_library)

# until TELL_WAIT() and such are not defined
# add_executable(fig8-13 fig8-13.c)
# add_dependencies(fig8-13 apue_library)
# target_link_libraries(fig8-13 apue_library)

add_executable(fig8-16 fig8-16.c)
add_dependencies(fig8-16 apue_library)
target_link_libraries(fig8-16 apue_library)

add_executable(fig8-17 fig8-17.c)
add_dependencies(fig8-17 apue_library)
target_link_libraries(fig8-17 apue_library)

add_executable(fig8-20 fig8-20.c)
add_dependencies(fig8-20 apue_library)
target_link_libraries(fig8-20 apue_library)
