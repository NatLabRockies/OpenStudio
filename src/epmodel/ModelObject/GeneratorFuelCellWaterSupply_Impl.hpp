/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLWATERSUPPLY_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLWATERSUPPLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorFuelCellWaterSupply_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorFuelCellWaterSupply_Impl() override = default;

      double pumpHeatLossFactor() const;
      bool setPumpHeatLossFactor(double pumpHeatLossFactor);
      void resetPumpHeatLossFactor();

      std::string waterTemperatureModelingMode() const;
      bool setWaterTemperatureModelingMode(const std::string& waterTemperatureModelingMode);
      void resetWaterTemperatureModelingMode();

      std::vector<std::string> waterTemperatureModelingModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
