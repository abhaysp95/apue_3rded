add_library(lib_apue STATIC
  src/error.c
  inc/apue.h
  )

target_include_directories(lib_apue PUBLIC inc)

# target_compile_features(lib_apue PUBLIC c_std_99)
