# Generate the EPModel class-family page from the existing source-tree organization.
# This complexity is intentional: deriving the browsing page from the source tree avoids
# introducing yet another hierarchy for the model classes through Doxygen groups or metadata.

if(NOT DEFINED OPENSTUDIO_SOURCE_DIR)
  message(FATAL_ERROR "OPENSTUDIO_SOURCE_DIR is required")
endif()

if(NOT DEFINED OUTPUT)
  message(FATAL_ERROR "OUTPUT is required")
endif()

set(EPMODEL_SOURCE_DIR "${OPENSTUDIO_SOURCE_DIR}/src/epmodel")

function(epmodel_family_anchor FAMILY OUTPUT_VARIABLE)
  string(TOLOWER "${FAMILY}" ANCHOR)
  string(REGEX REPLACE "[^a-z0-9]+" "_" ANCHOR "${ANCHOR}")
  string(REGEX REPLACE "^_+" "" ANCHOR "${ANCHOR}")
  string(REGEX REPLACE "_+$" "" ANCHOR "${ANCHOR}")
  set(${OUTPUT_VARIABLE} "epmodel_family_${ANCHOR}" PARENT_SCOPE)
endfunction()

file(GLOB_RECURSE EPMODEL_HEADERS LIST_DIRECTORIES FALSE "${EPMODEL_SOURCE_DIR}/*.hpp")

set(EPMODEL_FAMILIES)
foreach(HEADER IN LISTS EPMODEL_HEADERS)
  file(RELATIVE_PATH RELATIVE_HEADER "${EPMODEL_SOURCE_DIR}" "${HEADER}")

  if(RELATIVE_HEADER MATCHES "_Impl[.]hpp$"
     OR RELATIVE_HEADER MATCHES "(^|/)scaffolds/"
     OR RELATIVE_HEADER MATCHES "(^|/)test/")
    continue()
  endif()

  get_filename_component(RELATIVE_DIRECTORY "${RELATIVE_HEADER}" DIRECTORY)
  if(RELATIVE_DIRECTORY STREQUAL "")
    set(FAMILY "Top level")
  else()
    string(REPLACE "/" ";" DIRECTORY_PARTS "${RELATIVE_DIRECTORY}")
    list(GET DIRECTORY_PARTS 0 FAMILY)
  endif()

  file(READ "${HEADER}" HEADER_CONTENTS)
  string(REGEX MATCHALL
    "(class|struct)[ \t\r\n]+EPMODEL_API[ \t\r\n]+[A-Za-z_][A-Za-z0-9_]*"
    CLASS_DECLARATIONS
    "${HEADER_CONTENTS}"
  )

  if(CLASS_DECLARATIONS)
    list(APPEND EPMODEL_FAMILIES "${FAMILY}")
    string(MAKE_C_IDENTIFIER "${FAMILY}" FAMILY_IDENTIFIER)

    foreach(CLASS_DECLARATION IN LISTS CLASS_DECLARATIONS)
      string(REGEX REPLACE
        ".*EPMODEL_API[ \t\r\n]+([A-Za-z_][A-Za-z0-9_]*).*"
        "\\1"
        CLASS_NAME
        "${CLASS_DECLARATION}"
      )
      list(APPEND EPMODEL_CLASSES_${FAMILY_IDENTIFIER} "${CLASS_NAME}")
    endforeach()
  endif()
endforeach()

list(REMOVE_DUPLICATES EPMODEL_FAMILIES)
list(SORT EPMODEL_FAMILIES CASE INSENSITIVE)
list(REMOVE_ITEM EPMODEL_FAMILIES "Top level")
list(INSERT EPMODEL_FAMILIES 0 "Top level")

set(JUMP_REFERENCES)
foreach(FAMILY IN LISTS EPMODEL_FAMILIES)
  epmodel_family_anchor("${FAMILY}" FAMILY_ANCHOR)
  if(JUMP_REFERENCES)
    string(APPEND JUMP_REFERENCES " &middot; ")
  endif()
  string(APPEND JUMP_REFERENCES "\\ref ${FAMILY_ANCHOR} \"${FAMILY}\"")
endforeach()

get_filename_component(OUTPUT_DIRECTORY "${OUTPUT}" DIRECTORY)
file(MAKE_DIRECTORY "${OUTPUT_DIRECTORY}")
file(WRITE "${OUTPUT}"
  "/** \\page epmodel_class_families EPModel Classes\n"
  " *\n"
  " * The classes below follow the existing EPModel source-tree organization.\n"
  " * Directory names usually identify a shared base class or an established API\n"
  " * family. This is a browsing aid, not a separate type hierarchy; each class\n"
  " * declaration is authoritative about its C++ inheritance.\n"
  " *\n"
  " * **Jump to:** ${JUMP_REFERENCES}\n"
  " *\n"
)

foreach(FAMILY IN LISTS EPMODEL_FAMILIES)
  string(MAKE_C_IDENTIFIER "${FAMILY}" FAMILY_IDENTIFIER)
  set(FAMILY_CLASSES ${EPMODEL_CLASSES_${FAMILY_IDENTIFIER}})
  list(REMOVE_DUPLICATES FAMILY_CLASSES)
  list(SORT FAMILY_CLASSES CASE INSENSITIVE)

  list(FIND FAMILY_CLASSES "${FAMILY}" FAMILY_CLASS_INDEX)
  if(NOT FAMILY_CLASS_INDEX EQUAL -1)
    list(REMOVE_ITEM FAMILY_CLASSES "${FAMILY}")
    list(INSERT FAMILY_CLASSES 0 "${FAMILY}")
  endif()

  epmodel_family_anchor("${FAMILY}" FAMILY_ANCHOR)
  file(APPEND "${OUTPUT}"
    " * \\section ${FAMILY_ANCHOR} ${FAMILY}\n"
    " *\n"
    " * <table class=\"table table-condensed table-striped\">\n"
  )

  list(LENGTH FAMILY_CLASSES FAMILY_CLASS_COUNT)
  set(CLASS_INDEX 0)
  while(CLASS_INDEX LESS FAMILY_CLASS_COUNT)
    list(GET FAMILY_CLASSES ${CLASS_INDEX} LEFT_CLASS)
    set(RIGHT_REFERENCE)

    math(EXPR RIGHT_INDEX "${CLASS_INDEX} + 1")
    if(RIGHT_INDEX LESS FAMILY_CLASS_COUNT)
      list(GET FAMILY_CLASSES ${RIGHT_INDEX} RIGHT_CLASS)
      set(RIGHT_REFERENCE "\\ref openstudio::epmodel::${RIGHT_CLASS} \"${RIGHT_CLASS}\"")
    endif()

    file(APPEND "${OUTPUT}"
      " * <tr><td>\\ref openstudio::epmodel::${LEFT_CLASS} \"${LEFT_CLASS}\"</td><td>${RIGHT_REFERENCE}</td></tr>\n"
    )
    math(EXPR CLASS_INDEX "${CLASS_INDEX} + 2")
  endwhile()

  file(APPEND "${OUTPUT}" " * </table>\n *\n")
endforeach()

file(APPEND "${OUTPUT}" " */\n")
