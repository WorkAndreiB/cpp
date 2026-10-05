#!/bin/bash

# define build function
build(){
    component=$1

    echo "Building component: $component"

    # check if build directory exists
    if [ -d "$component/build/" ]; then
        echo "Build directory exists."
    else
        echo "Build directory does not exist. Creating it."
        mkdir -p "$component/build/"
    fi

    # build components
    cmake -S "$component" -B "$component/build/"
    cmake --build "$component/build/"
}

# define help function
help(){
    echo "Usage: $0 <component> [-e <executable_name>]"
    echo "  <component>   The component to build."
    echo "  -e <executable_name>   Optional. Execute the specified executable after building."
}

if [ $# -eq 1 ]; then
    # calling build with "$1" and not $1 because I want to preserve any spaces in the component name
    build "$1"
elif [ $# -eq 3 ]; then
    echo "build $1 and execute"
    build "$1"
    echo "Executing component: $1"
    ./"$1/build/$3"
else
    help "$1" "$3"
    exit 1
fi

