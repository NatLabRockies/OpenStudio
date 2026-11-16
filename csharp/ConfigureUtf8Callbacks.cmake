# SWIG's runtime delegates are emitted as literal C# rather than typemaps.
# Give their arguments borrowed ownership; their return buffers are consumed
# and freed by the UTF-8 marshaler on the outer P/Invoke string return.
set(pinvoke_file "${GENERATED_SOURCES_DIR}/${MODULE}PINVOKE.cs")
file(READ "${pinvoke_file}" source)
set(owned "global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler))")
set(borrowed "global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler), MarshalCookie = \"borrowed\")")

foreach(delegate IN ITEMS
    "public delegate string SWIGStringDelegate(string message);"
    "public delegate void ExceptionDelegate(string message);"
    "public delegate void ExceptionArgumentDelegate(string message, string paramName);")
  string(FIND "${source}" "${delegate}" position)
  if(position EQUAL -1)
    message(FATAL_ERROR "Unknown SWIG callback declaration in ${pinvoke_file}: ${delegate}")
  endif()
  string(REPLACE "string message" "[${borrowed}] string message" replacement "${delegate}")
  string(REPLACE "string paramName" "[${borrowed}] string paramName" replacement "${replacement}")
  if(delegate MATCHES "delegate string")
    set(replacement "[return: ${owned}]\n    ${replacement}")
  endif()
  string(REPLACE "${delegate}" "${replacement}" source "${source}")
endforeach()
file(WRITE "${pinvoke_file}" "${source}")
