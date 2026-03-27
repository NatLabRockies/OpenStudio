/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>
#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class HVACComponent;

  namespace detail {
    class ZoneHVACPackagedTerminalAirConditioner_Impl;
  }

  class EPMODEL_API ZoneHVACPackagedTerminalAirConditioner : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACPackagedTerminalAirConditioner(const Model& model);

    virtual ~ZoneHVACPackagedTerminalAirConditioner() override = default;
    ZoneHVACPackagedTerminalAirConditioner(const ZoneHVACPackagedTerminalAirConditioner& other) = default;
    ZoneHVACPackagedTerminalAirConditioner(ZoneHVACPackagedTerminalAirConditioner&& other) = default;
    ZoneHVACPackagedTerminalAirConditioner& operator=(const ZoneHVACPackagedTerminalAirConditioner&) = default;
    ZoneHVACPackagedTerminalAirConditioner& operator=(ZoneHVACPackagedTerminalAirConditioner&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> validFanPlacementValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The flow and fan-placement scalars are aligned, but the supply-fan/coils/node wiring remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACPackagedTerminalAirConditioner.
    // - Implemented Parity: Supply-air and outdoor-air flow scalars, `noLoadSupplyAirFlowRateControlSetToLowSpeed`, and `fanPlacement` map directly to the EnergyPlus object.
    // - Documented Delta: Supply-air fan, heating/cooling coil links, and node names are relationship-style fields and remain outside the scalar surface.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while the contained equipment and node topology are modeled explicitly through child-object state.
    // - Evidence: `src/model/ZoneHVACPackagedTerminalAirConditioner.hpp`, `src/model/ZoneHVACPackagedTerminalAirConditioner.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACPackagedTerminalAirConditioner.cpp`, and `src/epmodel/test/ZoneHVACPackagedTerminalAirConditioner_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers only if the canonical wrapper still exposes them directly.

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
    bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

    bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
    bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

    boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
    bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
    bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
    void autosizeOutdoorAirFlowRateDuringCoolingOperation();

    boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
    bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
    bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
    void autosizeOutdoorAirFlowRateDuringHeatingOperation();

    boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
    bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(HVACComponent& fan);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(HVACComponent& heatingCoil);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coolingCoil);

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACPackagedTerminalAirConditioner_Impl;

    explicit ZoneHVACPackagedTerminalAirConditioner(std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
