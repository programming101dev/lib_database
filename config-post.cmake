if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND p101_database_LINK_LIBRARIES gdbm_compat)
endif()
