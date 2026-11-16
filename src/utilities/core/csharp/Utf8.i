#ifndef UTILITIES_CSHARP_UTF8_I
#define UTILITIES_CSHARP_UTF8_I

// OpenStudio narrow strings are UTF-8 on every platform. Custom marshaling
// retains .NET Framework 4.5 support without requiring LPUTF8Str.
%typemap(imtype,
  inattributes="[global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler))]",
  outattributes="[return: global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler))]",
  directorinattributes="[global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler), MarshalCookie = \"borrowed\")]",
  directoroutattributes="[return: global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(global::OpenStudio.Utf8Marshaler))]")
  char *, char *&, char[ANY], char[], std::string, const std::string & "string"

#endif
