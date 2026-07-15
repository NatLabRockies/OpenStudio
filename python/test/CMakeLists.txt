if(BUILD_TESTING)
  set(PY_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  # Glob the files instead of running pytest --collect-only which requires bindings to be built
  file(GLOB_RECURSE TEST_FILES RELATIVE "${PY_TEST_DIR}" "test_*.py")

  foreach(test_file ${TEST_FILES})
    # Create a unique test name based on the file path
    string(REPLACE "/" "." test_name_clean ${test_file})
    string(REPLACE ".py" "" test_name_clean ${test_name_clean})

    add_test(NAME "PyTest.${test_name_clean}"
             COMMAND ${Python_EXECUTABLE} -m pytest ${test_file}
             WORKING_DIRECTORY "${PY_TEST_DIR}")

    # Ensure PYTHONPATH is set so bindings are found at RUNTIME
    set_tests_properties("PyTest.${test_name_clean}" PROPERTIES
      ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}/Products/python")
  endforeach()
endif()

