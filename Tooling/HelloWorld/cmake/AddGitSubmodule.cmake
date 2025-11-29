# define a function with name and arguments
function(add_git_submmodule dir)
    # make sure that git is present
    find_package(Git REQUIRED)

    # check if there is a CMakeLists file in directory (in this case, the submodule dir)
    if(NOT EXISTS ${dir}/CMakeLists.txt)
        execute_process(COMMAND ${GIT_EXECUTABLE}
            submodule update --init --recursive -- ${dir}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    endif()

    # can only call add_subdirectory is the ${dir} contains CMakeLists.txt
    if(EXISTS ${dir}/CMakeLists.txt)
        add_subdirectory(${dir})
    endif()
endfunction()