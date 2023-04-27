add_executable(fig4-3 fig4-3.c)
add_dependencies(fig4-3 apue_library)
target_link_libraries(fig4-3 apue_library)


add_executable(fig4-8 fig4-8.c)
add_dependencies(fig4-8 apue_library)
target_link_libraries(fig4-8 apue_library)

add_executable(fig4-9 fig4-9.c)
add_dependencies(fig4-9 apue_library)
target_link_libraries(fig4-9 apue_library)

add_executable(fig4-16 fig4-16.c)
add_dependencies(fig4-16 apue_library)
target_link_libraries(fig4-16 apue_library)

add_executable(fig4-21 fig4-21.c)
add_dependencies(fig4-21 apue_library)
target_link_libraries(fig4-21 apue_library)

add_executable(fig4-22 fig4-22.c ../standardization_implementation/fig2-16.c)
add_dependencies(fig4-22 apue_library)
target_link_libraries(fig4-22 apue_library)

add_executable(fig4-23 fig4-23.c)
add_dependencies(fig4-23 apue_library)
target_link_libraries(fig4-23 apue_library)
