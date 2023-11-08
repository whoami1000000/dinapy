add_subdirectory(log)
add_subdirectory(lib)

if (App)
    add_subdirectory(app)
endif ()

if (Test)
    add_subdirectory(test)
endif ()

if (Py)
    add_subdirectory(py)
endif ()