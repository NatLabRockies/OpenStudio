/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWSCALCULATIONENGINE_IMPL_HPP
#define EPMODEL_WINDOWSCALCULATIONENGINE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API WindowsCalculationEngine_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowsCalculationEngine_Impl() override = default;

      std::string windowsEngine() const;
      bool isWindowsEngineDefaulted() const;

      bool setWindowsEngine(const std::string& windowsEngine);
      void resetWindowsEngine();

      std::vector<std::string> windowsEngineValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
