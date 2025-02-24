cmake_minimum_required(VERSION 3.10)
project(c2pa_cpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
set(INCLUDES ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDES})

# Source files
set(SOURCES c2pa.cpp)

# Create the static library
add_library(c2pa_cpp STATIC ${SOURCES})

# Add the Rust library
set(RUST_LIB ${CMAKE_SOURCE_DIR}/target/release/libc2pa_c.dylib)
set(RUST_LIB_DEST ${CMAKE_BINARY_DIR}/lib/libc2pa_c.dylib)

# Copy the Rust library from the local path to the target/cmake/src directory
# file(COPY ${RUST_LIB_LOCAL_PATH} DESTINATION ${CMAKE_BINARY_DIR}/lib)

# Ensure the Rust library is built before linking
add_custom_command(
    OUTPUT ${RUST_LIB}
    COMMAND cargo build --release
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building Rust library"
)

# Copy the Rust library to the _deps/bin directory
add_custom_command(
    OUTPUT ${RUST_LIB_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy ${RUST_LIB} ${RUST_LIB_DEST}
    DEPENDS ${RUST_LIB}
    COMMENT "Copying Rust library to lib directory"
)

# Create a custom target for the Rust library
add_custom_target(build_rust_lib ALL DEPENDS ${RUST_LIB} ${RUST_LIB_DEST})
add_dependencies(c2pa_cpp build_rust_lib)

target_link_libraries(c2pa_cpp ${RUST_LIB_DEST})

target_include_directories(c2pa_cpp PUBLIC ${INCLUDES})

# Define the installation rules
install(TARGETS c2pa_cpp
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(FILES ${INCLUDES}/c2pa.hpp
        DESTINATION include)