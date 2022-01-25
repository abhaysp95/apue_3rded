add_executable(fig1-3 fig1-3.c)
add_dependencies(fig1-3 apue_library)
target_link_libraries(fig1-3 PUBLIC apue_library)
