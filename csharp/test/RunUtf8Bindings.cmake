file(MAKE_DIRECTORY "${TEST_DIRECTORY}")
file(COPY "${MANAGED_DLL}" DESTINATION "${TEST_DIRECTORY}")
set(test_exe "${TEST_DIRECTORY}/Utf8Bindings.exe")
file(TO_NATIVE_PATH "${TEST_SOURCE}" test_source_native)
file(TO_NATIVE_PATH "${MANAGED_DLL}" managed_dll_native)
file(TO_NATIVE_PATH "${test_exe}" test_exe_native)
execute_process(
  COMMAND "${CSHARP_COMPILER}" /nologo "/platform:${PLATFORM}"
          "/reference:${managed_dll_native}" "/out:${test_exe_native}" "${test_source_native}"
  RESULT_VARIABLE compile_result
)
if(NOT compile_result EQUAL 0)
  message(FATAL_ERROR "Failed to compile the C# UTF-8 regression executable")
endif()

set(ENV{PATH} "${NATIVE_DIRECTORY};$ENV{PATH}")
execute_process(COMMAND "${test_exe}" RESULT_VARIABLE test_result)
if(NOT test_result EQUAL 0)
  message(FATAL_ERROR "C# UTF-8 regression failed: ${test_result}")
endif()
