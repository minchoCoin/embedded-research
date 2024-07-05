idf_component_register(SRCS  "minmaxscaler.cc" "pitchroll.cc" "task_function.cc" "model.cc" "bluetooth.cc"  "icm20948.cc" "memory_log.cc" "main.cc" 
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)