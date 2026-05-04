macro(make_epmodel_swig_bindings NAME SIMPLENAME KEY_I_FILE I_FILES PARENT_TARGET PARENT_SWIG_TARGETS)
  include(UseSWIG)

  set(UseSWIG_MODULE_VERSION 2)

  set(SWIG_DEFINES "")
  set(SWIG_COMMON "")
  if(WIN32)
    set(SWIG_DEFINES "_WINDOWS")
    set(SWIG_COMMON "-Fmicrosoft")
  endif()

  get_target_property(target_files ${PARENT_TARGET} SOURCES)

  foreach(f ${target_files})
    get_source_file_property(p "${f}" LOCATION)
    get_filename_component(extension "${p}" EXT)

    if("${extension}" MATCHES "\\.h.*")
      if("${extension}" MATCHES "\\..xx" OR "${p}" MATCHES "ui_.*\\.h")
        list(APPEND GeneratedHeaders "${p}")
      else()
        list(APPEND RequiredHeaders "${p}")
      endif()
    endif()
  endforeach()

  foreach(i ${I_FILES} ${KEY_I_FILE})
    get_source_file_property(p "${i}" LOCATION)
    get_filename_component(extension "${p}" EXT)
    if("${extension}" MATCHES "\\..xx")
      list(APPEND GeneratedHeaders "${p}")
    else()
      list(APPEND RequiredHeaders "${p}")
    endif()
  endforeach()

  foreach(p ${PARENT_SWIG_TARGETS})
    list(APPEND ParentSWIGWrappers ${${p}_SWIG_Depends})
  endforeach()

  list(REMOVE_DUPLICATES RequiredHeaders)
  if(GeneratedHeaders)
    list(REMOVE_DUPLICATES GeneratedHeaders)
  endif()

  if(NOT TARGET ${PARENT_TARGET}_GeneratedHeaders)
    add_custom_command(
      OUTPUT "${PROJECT_BINARY_DIR}/${PARENT_TARGET}_HeadersGenerated_done.stamp"
      COMMAND ${CMAKE_COMMAND} -E touch "${PROJECT_BINARY_DIR}/${PARENT_TARGET}_HeadersGenerated_done.stamp"
      DEPENDS ${GeneratedHeaders}
    )

    add_custom_target(${PARENT_TARGET}_GeneratedHeaders
      SOURCES "${PROJECT_BINARY_DIR}/${PARENT_TARGET}_HeadersGenerated_done.stamp"
    )

    add_dependencies(${PARENT_TARGET} ${PARENT_TARGET}_GeneratedHeaders)
  endif()

  set(this_depends ${ParentSWIGWrappers})
  list(APPEND this_depends ${PARENT_TARGET}_GeneratedHeaders)
  list(APPEND this_depends ${RequiredHeaders})
  list(REMOVE_DUPLICATES this_depends)
  set(${NAME}_SWIG_Depends "${this_depends}" PARENT_SCOPE)

  string(TOLOWER "${NAME}" LOWER_NAME)
  string(REGEX MATCH "OpenStudioUtilities" IS_UTILTIES "${NAME}")
  if(IS_UTILTIES)
    set(RUBY_MODULE "OpenStudio")
  else()
    set(RUBY_MODULE "OpenStudio::${SIMPLENAME}")
  endif()

  set_property(SOURCE "${KEY_I_FILE}" PROPERTY CPLUSPLUS ON)
  set_property(SOURCE "${KEY_I_FILE}" PROPERTY DEPENDS "${this_depends}")
  set_property(SOURCE "${KEY_I_FILE}" PROPERTY USE_SWIG_DEPENDENCIES TRUE)

  set(common_swig_include_dirs
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_BINARY_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}"
  )
  get_target_property(parent_include_dirs ${PARENT_TARGET} INCLUDE_DIRECTORIES)
  if(parent_include_dirs)
    list(APPEND common_swig_include_dirs ${parent_include_dirs})
    list(REMOVE_DUPLICATES common_swig_include_dirs)
  endif()
  if(DEFINED OpenStudioCore_SWIG_INCLUDE_DIR)
    list(APPEND common_swig_include_dirs "${OpenStudioCore_SWIG_INCLUDE_DIR}")
  endif()
  if(DEFINED OpenStudioCore_DIR)
    list(APPEND common_swig_include_dirs "${OpenStudioCore_DIR}/src")
  endif()

  if(BUILD_RUBY_BINDINGS)
    set(ruby_target "ruby_${NAME}")
    swig_add_library(${ruby_target}
      TYPE OBJECT
      LANGUAGE ruby
      OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/swig/ruby/${LOWER_NAME}"
      OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/swig/ruby/${LOWER_NAME}"
      SOURCES "${KEY_I_FILE}"
    )

    set_target_properties(${ruby_target} PROPERTIES
      POSITION_INDEPENDENT_CODE ON
      SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
      SWIG_COMPILE_OPTIONS "-fvirtual;-module;${RUBY_MODULE};-initname;${LOWER_NAME};-I${PROJECT_SOURCE_DIR}/ruby;${SWIG_COMMON}"
      SWIG_COMPILE_DEFINITIONS "${SWIG_DEFINES}"
    )
    target_include_directories(${ruby_target} PRIVATE ${common_swig_include_dirs} "${PROJECT_SOURCE_DIR}/ruby")
    target_include_directories(${ruby_target} SYSTEM PRIVATE ${Ruby_INCLUDE_DIRS})
    target_compile_definitions(${ruby_target} PRIVATE SHARED_OS_LIBS RUBY_DONT_SUBST)
    # Keep these wrapper archives small: openstudio_rb links the parent library
    # once, so per-submodule Ruby wrappers should not embed it repeatedly.
    target_link_libraries(${ruby_target} PRIVATE ${${PARENT_TARGET}_depends})
    add_dependencies(${ruby_target} ${PARENT_TARGET})

    if(MSVC)
      target_compile_options(${ruby_target} PRIVATE /bigobj /wd4996 /wd5033 /wd4244)
    elseif(UNIX)
      if("${CMAKE_CXX_COMPILER_ID}" MATCHES "^(Apple)?Clang$")
        target_compile_options(${ruby_target} PRIVATE -Wno-dynamic-class-memaccess -Wno-deprecated-declarations -Wno-sign-compare -Wno-register -Wno-sometimes-uninitialized)
      else()
        target_compile_options(${ruby_target} PRIVATE -Wno-deprecated-declarations -Wno-sign-compare -Wno-register -Wno-conversion-null -Wno-misleading-indentation -fno-gnu-unique)
      endif()
    endif()

    list(APPEND ALL_RUBY_BINDING_TARGETS "${ruby_target}")
    set(ALL_RUBY_BINDING_TARGETS "${ALL_RUBY_BINDING_TARGETS}" PARENT_SCOPE)
  endif()

  if(BUILD_PYTHON_BINDINGS)
    set(python_target "python_${NAME}")
    set(PYTHON_GENERATED_SRC_DIR "${PROJECT_BINARY_DIR}/python_wrapper/generated_sources/")
    file(MAKE_DIRECTORY "${PYTHON_GENERATED_SRC_DIR}")
    set(PYTHON_GENERATED_SRC "${PYTHON_GENERATED_SRC_DIR}/${LOWER_NAME}.py")

    swig_add_library(${python_target}
      TYPE MODULE
      LANGUAGE python
      OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/swig/python/${LOWER_NAME}"
      OUTPUT_DIR "${PYTHON_GENERATED_SRC_DIR}"
      SOURCES "${KEY_I_FILE}"
    )

    set_target_properties(${python_target} PROPERTIES
      OUTPUT_NAME "_${LOWER_NAME}"
      PREFIX ""
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/python/"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/python/"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/python/"
      SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
      SWIG_COMPILE_OPTIONS "-relativeimport;${SWIG_COMMON}"
      SWIG_COMPILE_DEFINITIONS "${SWIG_DEFINES}"
    )
    target_include_directories(${python_target} PRIVATE ${common_swig_include_dirs})
    target_include_directories(${python_target} SYSTEM PRIVATE ${Python_INCLUDE_DIRS})
    target_compile_definitions(${python_target} PRIVATE SHARED_OS_LIBS SWIG_PYTHON_SILENT_MEMLEAK)
    target_link_libraries(${python_target} PUBLIC ${PARENT_TARGET} ${${PARENT_TARGET}_depends})
    add_dependencies(${python_target} ${PARENT_TARGET})

    if(MSVC)
      target_compile_options(${python_target} PRIVATE /bigobj /wd4996 /wd4005)
      set_target_properties(${python_target} PROPERTIES SUFFIX ".pyd")
      target_link_libraries(${python_target} PRIVATE Python::Module)
    elseif(UNIX)
      if(APPLE AND NOT CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(${python_target} PRIVATE -Wno-dynamic-class-memaccess -Wno-deprecated-declarations -Wno-sign-compare -Wno-sometimes-uninitialized)
        set_target_properties(${python_target} PROPERTIES LINK_FLAGS "-flat_namespace -undefined suppress")
      else()
        target_compile_options(${python_target} PRIVATE -Wno-deprecated-declarations -Wno-sign-compare -Wno-misleading-indentation -fno-gnu-unique)
      endif()
    endif()

    set(COPY_PYTHON_GENERATED_SRC "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/python/${LOWER_NAME}.py")
    add_custom_command(TARGET ${python_target}
      POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PYTHON_GENERATED_SRC}" "${COPY_PYTHON_GENERATED_SRC}"
    )
    add_custom_command(
      OUTPUT "${COPY_PYTHON_GENERATED_SRC}"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PYTHON_GENERATED_SRC}" "${COPY_PYTHON_GENERATED_SRC}"
      DEPENDS ${python_target} "${PYTHON_GENERATED_SRC}"
      VERBATIM
    )
    add_custom_target(${python_target}_python_source ALL DEPENDS "${COPY_PYTHON_GENERATED_SRC}")

    if(APPLE)
      set_target_properties(${python_target}
        PROPERTIES
          SUFFIX ".so"
          BUILD_RPATH "@loader_path;@loader_path/.."
          INSTALL_RPATH "@loader_path;@loader_path/../lib"
      )
    elseif(UNIX)
      set_target_properties(${python_target}
        PROPERTIES
          BUILD_RPATH "$ORIGIN:$ORIGIN/../"
          INSTALL_RPATH "$ORIGIN:$ORIGIN/../lib:$ORIGIN/../EnergyPlus"
      )
    endif()

    install(FILES "${PYTHON_GENERATED_SRC}" DESTINATION Python COMPONENT "Python")
    install(TARGETS ${python_target} DESTINATION Python COMPONENT "Python")

    list(APPEND ALL_PYTHON_BINDING_TARGETS "${python_target}")
    set(ALL_PYTHON_BINDING_TARGETS "${ALL_PYTHON_BINDING_TARGETS}" PARENT_SCOPE)
    list(APPEND ALL_PYTHON_BINDING_DEPENDS "${${PARENT_TARGET}_depends}")
    set(ALL_PYTHON_BINDING_DEPENDS "${ALL_PYTHON_BINDING_DEPENDS}" PARENT_SCOPE)
    list(APPEND ALL_PYTHON_GENERATED_SRCS "${PYTHON_GENERATED_SRC}")
    set(ALL_PYTHON_GENERATED_SRCS "${ALL_PYTHON_GENERATED_SRCS}" PARENT_SCOPE)
  endif()
endmacro()
