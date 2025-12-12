#ifndef MODELICA_API_HPP
#define MODELICA_API_HPP

#if (_WIN32 || _MSC_VER) && SHARED_OS_LIBS
#  ifdef openstudio_modelica_EXPORTS
#    define MODELICA_API __declspec(dllexport)
#  else
#    define MODELICA_API __declspec(dllimport)
#  endif
#else
#  define MODELICA_API
#endif

#endif  // MODELICA_API_HPP