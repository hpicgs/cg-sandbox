
# Generate meta-header
configure_file(cg-sandbox-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/cg-sandbox-version.h)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Libraries
set(IDE_FOLDER "Applications")
add_subdirectory(cg-sandbox)
