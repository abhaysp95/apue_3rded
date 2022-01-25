add_executable(fig1-3 fig1-3.c)
add_dependencies(fig1-3 apue_library)
target_link_libraries(fig1-3 PUBLIC apue_library)

add_executable(fig1-4 fig1-4.c)
add_dependencies(fig1-4 apue_library)
target_link_libraries(fig1-4 PUBLIC apue_library)
