#ifndef UTILITIES_CSHARP_UTF8_I
#define UTILITIES_CSHARP_UTF8_I

%{
#include <utilities/core/csharp/Utf16String.hpp>
%}

// Keep native inputs UTF-8 and let .NET own the UTF-16 return buffers on .NET Framework 4.5.
%typemap(imtype, out="string",
  outattributes="[return: global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPWStr)]",
  directorinattributes="[global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPWStr)]",
  directoroutattributes="[return: global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPWStr)]")
  char *, char *&, char[ANY], char[], std::string, const std::string & "byte[]"

%typemap(csin) char *, char *&, char[ANY], char[], std::string, const std::string &
  "global::OpenStudio.Utf8.ToNative($csinput)"

// A local UTF-16 string keeps director arguments alive until the managed override returns.
%typemap(directorin) std::string (std::u16string utf16)
%{
  utf16 = openstudio::detail::directorStringToUtf16($1);
  $input = reinterpret_cast<const char *>(utf16.c_str());
%}

%typemap(directorin) const std::string & = std::string;

%typemap(directorin) char * (std::u16string utf16)
%{
  if ($1) {
    utf16 = openstudio::detail::directorStringToUtf16($1);
    $input = reinterpret_cast<char *>(const_cast<char16_t *>(utf16.c_str()));
  } else {
    $input = 0;
  }
%}

%typemap(directorin) char *&, char[ANY], char[] = char *;

%typemap(directorout, canthrow=1) std::string
%{
  if (!$input) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "null string", 0);
    return $null;
  }
  $result = openstudio::detail::takeDirectorUtf16String($input);
%}

// Pointer/reference returns need an explicit lifetime contract before they can be supported.
%typemap(directorout) const std::string &, char *, char *&, char[ANY], char[]
%{
#error CSharp UTF8 director string returns must use std::string by value
%}

#endif
