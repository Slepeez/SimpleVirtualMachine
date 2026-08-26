
add_executable(SimpleVM
    main.c
    vm.c
)


target_include_directories(SimpleVM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

