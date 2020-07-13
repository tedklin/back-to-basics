list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/graph.cpp")
# ^^^ APPEND NEW SOURCE FILES TO THE SOURCE_LIST

# Make an automatic library - will be static or dynamic based on user setting
add_library(graphs_lib ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(graphs_lib PUBLIC ${PROJECT_SOURCE_DIR}/src)

# All users of this library will need at least C++11
target_compile_features(graphs_lib PUBLIC cxx_std_11)
