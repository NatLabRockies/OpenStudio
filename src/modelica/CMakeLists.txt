set(openstudio_modelica_depends
  antlr4_static
)
set(openstudio_modelica_depends ${openstudio_modelica_depends} PARENT_SCOPE)

add_library(openstudio_modelica
  OBJECT
  antlr/modelicaBaseListener.cpp
  antlr/modelicaBaseListener.h
  antlr/modelicaBaseVisitor.cpp
  antlr/modelicaBaseVisitor.h
  antlr/modelicaLexer.cpp
  antlr/modelicaLexer.h
  antlr/modelicaListener.cpp
  antlr/modelicaListener.h
  antlr/modelicaParser.cpp
  antlr/modelicaParser.h
  antlr/modelicaVisitor.cpp
  antlr/modelicaVisitor.h

  ModelicaAPI.hpp
  ModelicaFile.hpp
  ModelicaFile.cpp
  ModelicaFileImpl.hpp
  ModelicaFileImpl.cpp
)

target_link_libraries(openstudio_modelica 
  PUBLIC 
  ${openstudio_modelica_depends}
  openstudio_utilities
)

target_compile_definitions(openstudio_modelica
  PRIVATE
  openstudio_modelica_EXPORTS
  SHARED_OS_LIBS
)

set(openstudio_modelica_swig_src
  Modelica.i
)

#macro(MAKE_SWIG_TARGET NAME SIMPLENAME KEY_I_FILE I_FILES PARENT_TARGET PARENT_SWIG_TARGETS)
MAKE_SWIG_TARGET(OpenStudioModelica modelica "${CMAKE_CURRENT_SOURCE_DIR}/Modelica.i" "${openstudio_modelica_swig_src}" openstudio_modelica OpenStudioUtilities)

if(TARGET ruby_OpenStudioModelica)
  target_link_libraries(ruby_OpenStudioModelica openstudiolib)
endif()

if(TARGET python_OpenStudioModelica)
  target_link_libraries(python_OpenStudioModelica PUBLIC openstudiolib)
endif()

if(TARGET python_package_OpenStudioModelica)
  target_link_libraries(python_package_OpenStudioModelica PUBLIC openstudiolib)
endif()

add_executable(antdemo
  main.cpp
)

target_link_libraries(antdemo
  PUBLIC
  openstudio_utilities
  openstudio_modelica
)
