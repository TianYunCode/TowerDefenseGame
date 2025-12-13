# cJSON库配置
add_library(cJSON STATIC 
    cJSON.c
)

target_include_directories(cJSON PUBLIC 
    include
)

# 设置cJSON输出位置
set_target_properties(cJSON PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    OUTPUT_NAME "cJSON"
)