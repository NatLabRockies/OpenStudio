/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EPMODELAPI_HPP
#define EPMODEL_EPMODELAPI_HPP

#if (_WIN32 || _MSC_VER) && SHARED_OS_LIBS
#  if defined(openstudio_epmodel_EXPORTS) || defined(openstudio_EXPORTS)
#    define EPMODEL_API __declspec(dllexport)
#  else
#    define EPMODEL_API __declspec(dllimport)
#  endif
#else
#  define EPMODEL_API
#endif

#endif
