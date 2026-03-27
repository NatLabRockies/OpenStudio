/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACEnergyRecoveryVentilator_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACEnergyRecoveryVentilator_Impl() override = default;

      boost::optional<double> supplyAirFlowRate() const;
      bool setSupplyAirFlowRate(double supplyAirFlowRate);
      bool isSupplyAirFlowRateAutosized() const;
      void autosizeSupplyAirFlowRate();

      boost::optional<double> exhaustAirFlowRate() const;
      bool setExhaustAirFlowRate(double exhaustAirFlowRate);
      bool isExhaustAirFlowRateAutosized() const;
      void autosizeExhaustAirFlowRate();

      double ventilationRateperUnitFloorArea() const;
      bool setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea);

      double ventilationRateperOccupant() const;
      bool setVentilationRateperOccupant(double ventilationRateperOccupant);

      std::vector<ModelObject> children() const override;

      boost::optional<Node> inletNode() const override;
      boost::optional<Node> outletNode() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
