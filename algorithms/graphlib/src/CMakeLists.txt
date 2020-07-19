list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/graph.cpp")
list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/bfs.cpp")
list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/dfs.cpp")
list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/mst.cpp")
list(APPEND SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/weighted_paths.cpp")
# ^^^ APPEND NEW SOURCE FILES TO THE SOURCE_LIST

# Make an automatic library - will be static or dynamic based on user setting
add_library(graphlib ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(graphlib PUBLIC ${PROJECT_SOURCE_DIR}/src)

# All users of this library will need at least C++11
target_compile_features(graphlib PUBLIC cxx_std_11)
