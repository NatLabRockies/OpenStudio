/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;

  namespace detail {
    class ZoneHVACEnergyRecoveryVentilator_Impl;
  }

  class EPMODEL_API ZoneHVACEnergyRecoveryVentilator : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACEnergyRecoveryVentilator(const Model& model);

    virtual ~ZoneHVACEnergyRecoveryVentilator() override = default;
    ZoneHVACEnergyRecoveryVentilator(const ZoneHVACEnergyRecoveryVentilator& other) = default;
    ZoneHVACEnergyRecoveryVentilator(ZoneHVACEnergyRecoveryVentilator&& other) = default;
    ZoneHVACEnergyRecoveryVentilator& operator=(const ZoneHVACEnergyRecoveryVentilator&) = default;
    ZoneHVACEnergyRecoveryVentilator& operator=(ZoneHVACEnergyRecoveryVentilator&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Scalar getters/setters map to EnergyPlus ZoneHVAC:EnergyRecoveryVentilator fields enumerated by
    //   ZoneHVAC_EnergyRecoveryVentilatorFields via ForwardTranslateZoneHVACEnergyRecoveryVentilator.cpp.
    // - Field Mapping: availability schedule, heat exchanger, supply/exhaust fans, controller, availability manager,
    //   and node/link references are relationship-only and intentionally excluded from this scalar-only API.

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

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACEnergyRecoveryVentilator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACEnergyRecoveryVentilator(std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACENERGYRECOVERYVENTILATOR_HPP
