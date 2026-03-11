/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP
#define EPMODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACDehumidifierDX_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACDehumidifierDX_Impl() override = default;

      double ratedWaterRemoval() const;
      bool setRatedWaterRemoval(double ratedWaterRemoval);

      double ratedEnergyFactor() const;
      bool setRatedEnergyFactor(double ratedEnergyFactor);

      double ratedAirFlowRate() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);

      double minimumDryBulbTemperatureforDehumidifierOperation() const;
      bool setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation);

      double maximumDryBulbTemperatureforDehumidifierOperation() const;
      bool setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation);

      double offCycleParasiticElectricLoad() const;
      bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
