
# Some operating systems don't like compiling a library with
# no source files

if(MSVC)
  # MSVC import libraries (and the DLL export ordinal table) are limited to 65,535 exported
  # symbols (LNK1189). model + epmodel together export ~123,000 unique symbols, far beyond
  # that limit, so on Windows the object libraries are split across four DLLs:
  #
  #                    openstudioutilitieslib
  #                      ▲                ▲
  #      openstudiomodellib          openstudioepmodellib
  #                      ▲                ▲
  #                       openstudiolib
  #
  # openstudiolib keeps its name and PUBLIC-links the others so that no consumer
  # (CLI, ruby/python/csharp bindings, tests) needs any change.
  # Each OBJECT library still lands in exactly one DLL, so the per-component
  # openstudio_<name>_EXPORTS / <NAME>_API macros produce correct dllexport/dllimport.
  #
  # openstudio_osversion goes in openstudiomodellib (not the top-level openstudiolib)
  # because model/Model.cpp calls osversion::VersionTranslator directly (Model::load),
  # while osversion links openstudio_model's own dependency chain -- a genuine mutual
  # dependency that only compiles when both land in the same DLL.
  add_library(openstudioutilitieslib SHARED empty.cpp)
  target_link_libraries(
   openstudioutilitieslib
   PRIVATE
   openstudio_utilities
  )

  add_library(openstudiomodellib SHARED empty.cpp)
  target_link_libraries(
   openstudiomodellib
   PRIVATE
   openstudio_model
   openstudio_energyplus
   openstudio_osversion
   PUBLIC
   openstudioutilitieslib
  )

  add_library(openstudioepmodellib SHARED empty.cpp)
  target_link_libraries(
   openstudioepmodellib
   PRIVATE
   openstudio_epmodel
   PUBLIC
   openstudioutilitieslib
  )

  add_library(openstudiolib SHARED empty.cpp)
  target_link_libraries(
   openstudiolib
   PRIVATE
   openstudio_airflow
   openstudio_modelica
   openstudio_epjson
   openstudio_alfalfa
   openstudio_measure
   openstudio_sdd
   openstudio_isomodel
   openstudio_gbxml
   openstudio_gltf
   openstudio_radiance
   PUBLIC
   openstudiomodellib
   openstudioepmodellib
  )

  set(openstudio_lib_targets openstudiolib openstudiomodellib openstudioepmodellib openstudioutilitieslib)
else()
  add_library(openstudiolib SHARED empty.cpp)

  target_link_libraries(
   openstudiolib
   PRIVATE
   openstudio_utilities
   openstudio_airflow
   openstudio_model
   openstudio_modelica
   openstudio_energyplus
   openstudio_epmodel
   openstudio_epjson
   openstudio_alfalfa
   openstudio_measure
   openstudio_osversion
   openstudio_sdd
   openstudio_isomodel
   openstudio_gbxml
   openstudio_gltf
   openstudio_radiance
  )

  set(openstudio_lib_targets openstudiolib)
endif()

target_link_libraries(
 openstudiolib
 INTERFACE
 boost::boost
 JsonCpp::JsonCpp
 cpprestsdk::cpprestsdk
 openssl::openssl
 pugixml::pugixml
 LibXml2::LibXml2
 fmt::fmt
)

foreach(_os_lib IN LISTS openstudio_lib_targets)
  target_compile_definitions(${_os_lib} INTERFACE "-DSHARED_OS_LIBS")
endforeach()

# We cannot make the libs that make up the shared library public dependency at all, if we do
# then we have to export and install them as well, which we probably don't want to do.

# If we try to include directories from the dependent libraries directly, we have to use
# generator expressions to get the specific configuration's INTERFACE_INCLUDE_DIRECTORIES

# This also does not seem to do what we ultimately want, as it would also require
# that we export the .a files.

# So here we are, I'm manually exporting the directories, it's probably a mistake
# TODO reevaluate this.


target_include_directories(
  openstudiolib
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>
  )

install(TARGETS ${openstudio_lib_targets}
        EXPORT openstudio
        DESTINATION ${LIB_DESTINATION_DIR}
        COMPONENT "CLI"  # CLI is no longer self-contained, it needs it
        INCLUDES DESTINATION include
          include/openstudio
        )

install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
                  "${PROJECT_BINARY_DIR}/src/"
        DESTINATION include/openstudio
        COMPONENT "CPPAPI"
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "*.hxx"
        PATTERN "*.i"
        )

set(openstudiolib_test_src
  test/ApplicationPathHelpers_GTest.cpp
)

if(BUILD_TESTING)
  CREATE_TEST_TARGETS(openstudiolib "${openstudiolib_test_src}" openstudiolib openstudio_model_resources openstudio_energyplus_resources)
endif()
