# macro for adding executable examples
macro(package_add_example EXAMPLENAME)
  # create an exectuable in which the tests will be stored
  add_executable(${EXAMPLENAME} ${ARGN})
  target_compile_features(${EXAMPLENAME} PRIVATE cxx_std_14)
  set_target_properties(${EXAMPLENAME} PROPERTIES CXX_EXTENSIONS OFF)
  target_compile_options(${EXAMPLENAME} PRIVATE "-Wall")

  # link graphs_lib
  target_link_libraries(${EXAMPLENAME} PRIVATE graphlib)
endmacro()

package_add_example(core_test core_test.cpp)

package_add_example(graph_2d_test geometry/graph_2d_test.cpp)

package_add_example(bfs_test algo/bfs_test.cpp)
package_add_example(dfs_test algo/dfs_test.cpp)
package_add_example(mst_test algo/mst_test.cpp)
package_add_example(weighted_paths_test algo/weighted_paths_test.cpp)
# ^^^ ADD MORE EXAMPLE EXECUTABLES HERE ^^^
