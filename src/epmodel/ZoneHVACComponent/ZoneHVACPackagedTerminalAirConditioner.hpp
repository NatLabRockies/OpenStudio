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
    // - API: supplyAirFlowRateDuringCoolingOperation, supplyAirFlowRateDuringHeatingOperation, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded,
    //   outdoorAirFlowRateDuringCoolingOperation, outdoorAirFlowRateDuringHeatingOperation, outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded,
    //   noLoadSupplyAirFlowRateControlSetToLowSpeed, and fanPlacement map to the EnergyPlus ZoneHVAC:PackagedTerminalAirConditioner fields
    //   enumerated by ZoneHVAC_PackagedTerminalAirConditionerFields; ForwardTranslateZoneHVACPackagedTerminalAirConditioner.cpp documents these mappings.
    // - Field Mapping: relationship-like values (availability schedule, supply-air fan/heating/cooling coil links, node names, and the outdoor air mixer)
    //   remain outside this scalar-focused interface.

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

   protected:
    using ImplType = detail::ZoneHVACPackagedTerminalAirConditioner_Impl;

    explicit ZoneHVACPackagedTerminalAirConditioner(std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
