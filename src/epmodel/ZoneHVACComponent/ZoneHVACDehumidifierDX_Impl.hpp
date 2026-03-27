/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP
#define EPMODEL_ZONEHVACDEHUMIDIFIERDX_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACDehumidifierDX_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACDehumidifierDX_Impl() override = default;

      std::vector<ModelObject> children() const override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

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
