# Basic setups
cmake_minimum_required(VERSION 3.5)
project(FourierDepthOfField)

# Basic flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")

# Include GLM
add_subdirectory(include/glm EXCLUDE_FROM_ALL)
include_directories(include/glm/)

# =========================================================================== #

# Generate single header file using the script
execute_process(
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/script/generate_header.py fdof ${CMAKE_CURRENT_LIST_DIR}/src/extern/
)

# Set Include Directory to Extern and Include
include_directories(src/extern)

# Compile all the cpp files and link to `animator` library along with NanoGui
file(GLOB fdof_sources src/intern/*.cpp src/intern/*/*.cpp src/intern/*/*/*.cpp src/extern/*.h src/extern/*/*.h src/extern/*/*/*.h)
set(fdof ${fdof_sources})
add_library(fdof ${fdof})
target_link_libraries(fdof glm)

# Compile all the test files
file(GLOB test_sources test/*.cpp test/*/*.cpp test/*/*/*.cpp)
foreach(test_source ${test_sources})
    string(REPLACE ".cpp" "" temp_path ${test_source})
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" temp_path ${temp_path})
    get_filename_component(temp_dir ${temp_path} DIRECTORY)
    get_filename_component(temp_name ${temp_path} NAME)
    add_executable(${temp_name} ${test_source})
    set_target_properties(${temp_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${temp_dir})
    target_link_libraries(${temp_name} fdof)
    include("${temp_dir}/CMakeLists.txt" OPTIONAL)
endforeach(test_source ${test_sources})
