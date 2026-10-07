#!/bin/bash

# usecases 
# ./build_cpp.sh [-e] components
# ./build_cpp.sh -h 

build(){
    component=$1

    # check if build directory exists
    if [ ! -d "$component/build/" ]; then
        echo "Build directory does not exist. Creating it."
        # create the build directory if it doesn't exist. use || exit $? to stop the script if mkdir fails
        mkdir -p "$component/build/" || exit $?
    fi

    # request the CMake file API codemodel so the evaluated executable path can be read after configuring
    mkdir -p "$component/build/.cmake/api/v1/query" || exit $?
    touch "$component/build/.cmake/api/v1/query/codemodel-v2" || exit $?

    # build components
    cmake -S "$component" -B "$component/build/"
    cmake --build "$component/build/"
}

get_executable_name(){
    path=$1

    # Extract the executable name from the CMake file
    # ^ This indicates the start of the line in the CMake file
    # [[:space:]]* This means zero or more whitespace characters. This allows indentation
    # \( ... \) is used to create a capture group in the regular expression
    # Optional double quotes around the target name are excluded from the capture.
    # .* Match the rest of the line
    # \1 refers to the first capture group, which is the executable name
    exec_name=$(sed -n 's/^[[:space:]]*add_executable[[:space:]]*("\?\([^"[:space:])]*\)"\?.*/\1/p' "$path")
    echo "$exec_name"
}

execute(){
    component=$1
    if [ -f "$component/CMakeLists.txt" ]; then
        exec_name=$(get_executable_name "$component/CMakeLists.txt")
        ./"$component/build/$exec_name"
    else
        echo "CMakeLists.txt not found for component: $component"
    fi
}

help(){
    echo "Usage: [option] <component>
            -b      Build component without executing
            -e      Run executable after building
            -h      Display this help message."
}

check_for_component(){
    if [ -z "$1" ]; then
        echo "Error: No component specified."
        exit 1
    fi
}


main() {
    # print help if no arguments are provided
    if [ $# -eq 0 ]; then
        help
        exit 1
    fi

    case "$1" in
        -h|--help) 
            help
            exit 0
            ;;
        -e)
            check_for_component "$2"
            echo "building and executing component: $2"
            build "$2"
            execute "$2"
            ;;
        -b)
            check_for_component "$2"
            echo "building component: $2"
            build "$2"
            ;;
        *)
            echo "Error: Unknown option $1"
            help
            exit 1
            ;;
    esac
}

# use "$@" to pass all script arguments to the main function
main "$@"
