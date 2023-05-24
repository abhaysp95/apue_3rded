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

add_executable(fig8-23 fig8-23.c fig8-5.c)
add_dependencies(fig8-23 apue_library)
target_link_libraries(fig8-23 apue_library)

add_executable(fig8-24 fig8-24.c fig8-5.c)
add_dependencies(fig8-24 apue_library)
target_link_libraries(fig8-24 apue_library)

add_executable(fig8-25 fig8-25.c)
add_dependencies(fig8-25 apue_library)
target_link_libraries(fig8-25 apue_library)

add_executable(fig8-28 fig8-28.c)
add_dependencies(fig8-28 apue_library)
target_link_libraries(fig8-28 apue_library)

add_executable(fig8-29 fig8-29.c)
add_dependencies(fig8-29 apue_library)
target_link_libraries(fig8-29 apue_library)

add_executable(nice_test nice_test.c)
add_dependencies(nice_test apue_library)
target_link_libraries(nice_test apue_library)

add_executable(fig8-30 fig8-30.c)
add_dependencies(fig8-30 apue_library)
target_link_libraries(fig8-30 apue_library)

add_executable(clktime_test clktime_test.c)
add_dependencies(clktime_test apue_library)
target_link_libraries(clktime_test apue_library)

add_executable(fig8-31 fig8-31.c fig8-5.c)
add_dependencies(fig8-31 apue_library)
target_link_libraries(fig8-31 apue_library)

add_executable(fig8-30_updated_with_process_time fig8-30_updated_with_process_time.c)
add_dependencies(fig8-30_updated_with_process_time apue_library)
target_link_libraries(fig8-30_updated_with_process_time apue_library)
