# macro for adding executable examples
macro(package_add_example EXAMPLENAME)
  # create an exectuable in which the tests will be stored
  add_executable(${EXAMPLENAME} ${ARGN})
  target_compile_features(${EXAMPLENAME} PRIVATE cxx_std_17)

  # link graphs_lib
  target_link_libraries(${EXAMPLENAME} PRIVATE graphlib)
endmacro()

package_add_example(init_test init_test.cpp)
package_add_example(bfs_test bfs_test.cpp)
# ^^^ ADD MORE EXAMPLE EXECUTABLES HERE ^^^
