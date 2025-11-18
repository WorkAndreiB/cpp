# CMake  

## CMake build commands

### Generate project 
+ cmake -S <path/to/source> -B <path/to/build> 

### Generate project with variable values
+ cmake -S <path/to/source> -B <path/to/build> -D<option_name>=<option_value>

### Generate project with different generator
+ cmake -S <path/to/source> -B <path/to/build> -G "<generator_name>"

### Create executable 
+ cmake --build <path/to/build>

### CMake build target
+ cmake --build <path/to/build> --target <target_name>

or option 2 (only works for system where generator is makefile)

+ cd build
+ make <target_name>

