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
    // - Status: Partial Parity. The scalar ventilation fields are aligned, but the heat-exchanger and fan/controller relationships still live outside the scalar surface.
    // - Canonical Counterpart: openstudio::model::ZoneHVACEnergyRecoveryVentilator.
    // - Implemented Parity: `supplyAirFlowRate`, `exhaustAirFlowRate`, `ventilationRateperUnitFloorArea`, `ventilationRateperOccupant`, and `children()` preserve the main canonical wrapper behavior.
    // - Documented Delta: Availability schedule, heat exchanger, supply/exhaust fans, controller, availability manager, and node/link references remain relationship-only.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while the omitted links are represented through child-object and zone-topology state.
    // - Evidence: `src/model/ZoneHVACEnergyRecoveryVentilator.hpp`, `src/model/ZoneHVACEnergyRecoveryVentilator.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEnergyRecoveryVentilator.cpp`, and `src/epmodel/test/ZoneHVACEnergyRecoveryVentilator_GTest.cpp`.
    // - Remaining Parity Work: Expose the missing relationship helpers only if the canonical model surface needs them as public epmodel APIs.

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
