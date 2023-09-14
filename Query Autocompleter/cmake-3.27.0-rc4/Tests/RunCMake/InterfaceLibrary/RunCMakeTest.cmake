include(RunCMake)

run_cmake(invalid_name)
run_cmake(target_commands)
run_cmake(no_shared_libs)
run_cmake(invalid_signature)
run_cmake(global-interface)
run_cmake(genex_link)
run_cmake(add_custom_command-TARGET)
run_cmake(IMPORTED_LIBNAME-bad-value)
run_cmake(IMPORTED_LIBNAME-non-iface)
run_cmake(IMPORTED_LIBNAME-non-imported)

function(run_WithSources CASE)
  if(NOT RunCMake_GENERATOR_IS_MULTI_CONFIG)
    set(RunCMake_TEST_OPTIONS -DCMAKE_BUILD_TYPE=Debug)
  endif()
  set(RunCMake_TEST_BINARY_DIR ${RunCMake_BINARY_DIR}/${CASE}-build)
  run_cmake(${CASE})
  set(RunCMake_TEST_NO_CLEAN 1)
  foreach(build IN LISTS ARGN)
    if(build MATCHES "^([^:]+)$")
      run_cmake_command(${CASE}-${CMAKE_MATCH_1} ${CMAKE_COMMAND} --build . --config Debug)
    elseif(build MATCHES "^([^:]+):([^:,]+)(,merge)?$")
      if(CMAKE_MATCH_3 STREQUAL ",merge")
        set(RunCMake_TEST_OUTPUT_MERGE 1)
      endif()
      run_cmake_command(${CASE}-${CMAKE_MATCH_1} ${CMAKE_COMMAND} --build . --config Debug --target ${CMAKE_MATCH_2})
    endif()
  endforeach()
endfunction()

run_WithSources(ConfigSources "build1:iface")
run_WithSources(EmptySources "build1:iface" "build2:iface2,merge")
run_WithSources(ExcludeFromAll "build1" "build2:iface" "build3:iface2,merge")
run_WithSources(PublicSources "build1" "build2:iface" "build3:iface2,merge")
run_WithSources(IncludeDirectories "build1:iface")