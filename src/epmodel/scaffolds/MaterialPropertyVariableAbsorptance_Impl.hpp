/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYVARIABLEABSORPTANCE_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYVARIABLEABSORPTANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MaterialPropertyVariableAbsorptance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~MaterialPropertyVariableAbsorptance_Impl() override = default;

      std::string controlSignal() const;
      bool isControlSignalDefaulted() const;
      bool setControlSignal(const std::string& controlSignal);
      void resetControlSignal();
      std::vector<std::string> controlSignalValues() const;

      boost::optional<std::string> thermalAbsorptanceFunctionName() const;
      bool setThermalAbsorptanceFunctionName(const std::string& thermalAbsorptanceFunctionName);
      void resetThermalAbsorptanceFunctionName();

      boost::optional<std::string> thermalAbsorptanceScheduleName() const;
      bool setThermalAbsorptanceScheduleName(const std::string& thermalAbsorptanceScheduleName);
      void resetThermalAbsorptanceScheduleName();

      boost::optional<std::string> solarAbsorptanceFunctionName() const;
      bool setSolarAbsorptanceFunctionName(const std::string& solarAbsorptanceFunctionName);
      void resetSolarAbsorptanceFunctionName();

      boost::optional<std::string> solarAbsorptanceScheduleName() const;
      bool setSolarAbsorptanceScheduleName(const std::string& solarAbsorptanceScheduleName);
      void resetSolarAbsorptanceScheduleName();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
