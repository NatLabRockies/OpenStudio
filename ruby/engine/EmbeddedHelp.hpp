/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef CLI_EMBEDDEDHELP_HPP
#define CLI_EMBEDDEDHELP_HPP

#include <iostream>
#if defined __APPLE__
#  include <mach-o/dyld.h> /* _NSGetExecutablePath */
#  include <limits.h>      /* PATH_MAX */
#elif defined _WIN32
#  include <windows.h>
#endif

#ifdef SWIG
%include <ext-init.hpp>
// Ignore the parser extensions that may not be available in all Ruby builds
%ignore Init_cparse;
%ignore Init_prism;
%ignore embedded_help::init_cparse;
%ignore embedded_help::init_prism;
#else
#  include <ext-init.hpp>

// Forward declarations for Ruby 3.2+ parser extensions that may not be available
// Use weak linkage to prevent linker errors on systems where these don't exist
extern "C"
{
#  if defined(__GNUC__) || defined(__clang__)
  extern void Init_cparse(void) __attribute__((weak));
  extern void Init_prism(void) __attribute__((weak));
#  endif
}

#endif

namespace embedded_help {

// Stub implementations for Ruby 3.2+ parser extensions that may not be available
// These are declared to provide linker symbols even if the extensions don't exist
inline void init_cparse() {
  // This is a no-op - the extension may not be available in all Ruby builds
}

inline void init_prism() {
  // This is a no-op - the extension may not be available in all Ruby builds
}

inline std::string applicationFilePath() {
#ifdef __APPLE__
  char path[PATH_MAX + 1];
  uint32_t size = sizeof(path);
  if (_NSGetExecutablePath(path, &size) == 0) {
    return {path};
  }
#elif defined _WIN32
  TCHAR szPath[MAX_PATH];
  if (!GetModuleFileName(nullptr, szPath, MAX_PATH)) {
    return std::string(szPath);
  }
#endif
  return {};
}

}  // namespace embedded_help

#endif  // CLI_EMBEDDEDHELP_HPP
