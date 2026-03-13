/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLINVERTER_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLINVERTER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorFuelCellInverter_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorFuelCellInverter_Impl() override = default;

      std::vector<std::string> inverterEfficiencyCalculationModeValues() const;

      std::string inverterEfficiencyCalculationMode() const;
      bool setInverterEfficiencyCalculationMode(const std::string& inverterEfficiencyCalculationMode);
      void resetInverterEfficiencyCalculationMode();

      double inverterEfficiency() const;
      bool setInverterEfficiency(double inverterEfficiency);
      void resetInverterEfficiency();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
