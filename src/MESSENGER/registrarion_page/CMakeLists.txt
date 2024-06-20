cmake_minimum_required(VERSION 3.5)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Set paths
set(PROTO_PATH "${CMAKE_SOURCE_DIR}/proto")
set(BINDIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Ensure the generated directory exists
file(MAKE_DIRECTORY ${BINDIR})

# Generate protobuf files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${BINDIR} ${PROTO_PATH}/chat.proto)
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${BINDIR} ${PROTO_PATH}/chat.proto)

# Add executable
add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp  # Add more source files as needed
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${BINDIR}
    ${PROTO_PATH}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    gRPC::grpc++
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

# Install target (if needed)
install(TARGETS ${PROJECT_NAME} DESTINATION ./bin)

