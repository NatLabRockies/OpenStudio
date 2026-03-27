/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATER_HPP
#define EPMODEL_HEATPUMPAIRTOWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpAirToWater_Impl;
  }

  class EPMODEL_API HeatPumpAirToWater : public StraightComponent
  {
   public:
    explicit HeatPumpAirToWater(const Model& model);

    virtual ~HeatPumpAirToWater() override = default;
    HeatPumpAirToWater(const HeatPumpAirToWater& other) = default;
    HeatPumpAirToWater(HeatPumpAirToWater&& other) = default;
    HeatPumpAirToWater& operator=(const HeatPumpAirToWater&) = default;
    HeatPumpAirToWater& operator=(HeatPumpAirToWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> operatingModeControlMethodValues();
    static std::vector<std::string> operatingModeControlOptionforMultipleUnitValues();
    static std::vector<std::string> heatPumpDefrostControlValues();
    static std::vector<std::string> controlTypeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical air-to-water heat-pump scalar surface is present, while schedule, curve, node, and speed-data helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::HeatPumpAirToWater.
    // - Implemented Parity: The preserved scalar API matches the operating-mode, defrost, control, part-load, crankcase-heater, and multiplier accessors with matching default behavior.
    // - Documented Delta: Schedule, curve, node, and speed-data helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `HeatPump:AirToWater` scalar fields used by the forward translator.
    // - Evidence: `src/model/HeatPumpAirToWater.hpp`, `src/model/HeatPumpAirToWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWater.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    std::string operatingModeControlMethod() const;
    bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);
    bool isOperatingModeControlMethodDefaulted() const;
    void resetOperatingModeControlMethod();

    std::string operatingModeControlOptionforMultipleUnit() const;
    bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);
    bool isOperatingModeControlOptionforMultipleUnitDefaulted() const;
    void resetOperatingModeControlOptionforMultipleUnit();

    double minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    bool isMinimumPartLoadRatioDefaulted() const;
    void resetMinimumPartLoadRatio();

    double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);
    bool isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted() const;
    void resetMaximumOutdoorDryBulbTemperatureForDefrostOperation();

    std::string heatPumpDefrostControl() const;
    bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
    bool isHeatPumpDefrostControlDefaulted() const;
    void resetHeatPumpDefrostControl();

    double heatPumpDefrostTimePeriodFraction() const;
    bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
    bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
    void resetHeatPumpDefrostTimePeriodFraction();

    double resistiveDefrostHeaterCapacity() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    bool isResistiveDefrostHeaterCapacityDefaulted() const;
    void resetResistiveDefrostHeaterCapacity();

    int heatPumpMultiplier() const;
    bool setHeatPumpMultiplier(int heatPumpMultiplier);
    bool isHeatPumpMultiplierDefaulted() const;
    void resetHeatPumpMultiplier();

    std::string controlType() const;
    bool setControlType(const std::string& controlType);
    bool isControlTypeDefaulted() const;
    void resetControlType();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
    bool isCrankcaseHeaterCapacityDefaulted() const;
    void resetCrankcaseHeaterCapacity();

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
    bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
    void resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();

   protected:
    using ImplType = detail::HeatPumpAirToWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpAirToWater(std::shared_ptr<detail::HeatPumpAirToWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
