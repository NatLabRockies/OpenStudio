/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACEnergyRecoveryVentilator_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
