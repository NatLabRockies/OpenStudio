find_package(antlr4-runtime REQUIRED CONFIG)

add_library( rubybindings OBJECT
  InitRubyBindings.hpp
  InitRubyBindings.cpp
  InitEPModelRubyBindings.cpp
  ModelicaAntlrCleanup.hpp
  ModelicaAntlrCleanup.cpp
)

target_include_directories(rubybindings PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(rubybindings PRIVATE ${ALL_RUBY_BINDING_TARGETS} rubyinterpreter-declarations)

if(MINIMAL_BUILD)
  target_compile_definitions(rubybindings PRIVATE MINIMAL_BUILD)
endif()

# wd4996=no deprecated warnings ; wd5033=register
target_compile_options(rubybindings PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj /wd4996 /wd5033>
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wno-error=register -Wno-register>
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-deprecated-volatile>
  $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations -Wno-volatile>
)
