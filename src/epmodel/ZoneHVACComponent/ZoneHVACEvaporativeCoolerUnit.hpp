/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP
#define EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACEvaporativeCoolerUnit_Impl;
  }

  class EPMODEL_API ZoneHVACEvaporativeCoolerUnit : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACEvaporativeCoolerUnit(const Model& model);

    virtual ~ZoneHVACEvaporativeCoolerUnit() override = default;
    ZoneHVACEvaporativeCoolerUnit(const ZoneHVACEvaporativeCoolerUnit& other) = default;
    ZoneHVACEvaporativeCoolerUnit(ZoneHVACEvaporativeCoolerUnit&& other) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(const ZoneHVACEvaporativeCoolerUnit&) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(ZoneHVACEvaporativeCoolerUnit&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar fan/control fields are aligned, while the fan, cooler, and node wiring stays relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACEvaporativeCoolerUnit.
    // - Implemented Parity: `designSupplyAirFlowRate`, `fanPlacement`, `coolerUnitControlMethod`, throttling-range, cooling-load threshold, and shutoff humidity map directly to the EnergyPlus object.
    // - Documented Delta: Availability schedule, supply air fan, evaporative cooler children, and connected node references are relationship-only and remain excluded from the scalar surface.
    // - Field/Storage Mapping: Scalar fields live directly on the EnergyPlus object; topology and child links are maintained through explicit child-object helpers.
    // - Evidence: `src/model/ZoneHVACEvaporativeCoolerUnit.hpp`, `src/model/ZoneHVACEvaporativeCoolerUnit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEvaporativeCoolerUnit.cpp`, and `src/epmodel/test/ZoneHVACEvaporativeCoolerUnit_GTest.cpp`.
    // - Remaining Parity Work: Add the missing relationship helpers only if the canonical wrapper needs them beyond the current child/topology surface.
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> coolerUnitControlMethodValues();

    unsigned inletPort() const;
    unsigned outletPort() const;

    boost::optional<double> designSupplyAirFlowRate() const;
    bool isDesignSupplyAirFlowRateAutosized() const;
    bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
    void autosizeDesignSupplyAirFlowRate();

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);

    std::string coolerUnitControlMethod() const;
    bool setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod);

    double throttlingRangeTemperatureDifference() const;
    bool setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference);

    double coolingLoadControlThresholdHeatTransferRate() const;
    bool setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate);

    double shutOffRelativeHumidity() const;
    bool setShutOffRelativeHumidity(double shutOffRelativeHumidity);

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACEvaporativeCoolerUnit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACEvaporativeCoolerUnit(std::shared_ptr<detail::ZoneHVACEvaporativeCoolerUnit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
