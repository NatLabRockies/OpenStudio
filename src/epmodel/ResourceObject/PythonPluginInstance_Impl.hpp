/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGININSTANCE_IMPL_HPP
#define EPMODEL_PYTHONPLUGININSTANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PythonPluginInstance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PythonPluginInstance_Impl() override = default;

      bool runDuringWarmupDays() const;
      bool isRunDuringWarmupDaysDefaulted() const;
      bool setRunDuringWarmupDays(bool runDuringWarmupDays);
      void resetRunDuringWarmupDays();

      std::string pythonModuleName() const;
      bool setPythonModuleName(const std::string& pythonModuleName);

      std::string pluginClassName() const;
      bool setPluginClassName(const std::string& pluginClassName);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
