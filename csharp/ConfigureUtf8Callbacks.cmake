# SWIG emits these runtime delegates literally rather than through typemaps.
# Borrow their UTF-8 inputs and let the CLR allocate UTF-16 callback results.
set(pinvoke_file "${GENERATED_SOURCES_DIR}/${MODULE}PINVOKE.cs")
file(READ "${pinvoke_file}" source)

macro(replace_callback expected replacement)
  string(FIND "${source}" "${expected}" position)
  if(position EQUAL -1)
    message(FATAL_ERROR "Unknown SWIG callback code in ${pinvoke_file}: ${expected}")
  endif()
  string(REPLACE "${expected}" "${replacement}" source "${source}")
endmacro()

replace_callback(
  "public delegate string SWIGStringDelegate(string message);"
  "[return: global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPWStr)]\n    public delegate string SWIGStringDelegate(global::System.IntPtr message);")
replace_callback(
  "static string CreateString(string cString) {\n      return cString;\n    }"
  "static string CreateString(global::System.IntPtr cString) {\n      return global::OpenStudio.Utf8.FromNative(cString);\n    }")
replace_callback(
  "public delegate void ExceptionDelegate(string message);"
  "public delegate void ExceptionDelegate(global::System.IntPtr message);")
replace_callback(
  "public delegate void ExceptionArgumentDelegate(string message, string paramName);"
  "public delegate void ExceptionArgumentDelegate(global::System.IntPtr message, global::System.IntPtr paramName);")

foreach(exception IN ITEMS Application Arithmetic DivideByZero IndexOutOfRange
    InvalidCast InvalidOperation IO NullReference OutOfMemory Overflow System)
  replace_callback(
    "new ExceptionDelegate(SetPending${exception}Exception)"
    "new ExceptionDelegate(message => SetPending${exception}Exception(global::OpenStudio.Utf8.FromNative(message)))")
endforeach()
foreach(exception IN ITEMS Argument ArgumentNull ArgumentOutOfRange)
  replace_callback(
    "new ExceptionArgumentDelegate(SetPending${exception}Exception)"
    "new ExceptionArgumentDelegate((message, paramName) => SetPending${exception}Exception(global::OpenStudio.Utf8.FromNative(message), global::OpenStudio.Utf8.FromNative(paramName)))")
endforeach()
if(source MATCHES "new Exception(Argument)?Delegate\\(SetPending")
  message(FATAL_ERROR "Unknown SWIG exception callback in ${pinvoke_file}")
endif()

file(WRITE "${pinvoke_file}" "${source}")
