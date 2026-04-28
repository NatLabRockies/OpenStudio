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
  class Schedule;
  class Curve;

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
    // - Status: Partial Parity. The canonical scalar surface plus direct schedule, curve, and air-node helpers are present, while plant-side operation-mode helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::HeatPumpAirToWater.
    // - Implemented Parity: The wrapper now matches the canonical operating-mode, defrost, control, part-load, crankcase-heater, multiplier, operating-mode schedule, air-node-name, and direct curve relationship helpers with matching constructor defaults.
    // - Documented Delta: Heating/cooling operation-mode child wrappers and loop lookup helpers remain intentionally omitted because epmodel does not yet expose those canonical child types for `HeatPump:AirToWater`.
    // - Field/Storage Mapping: These APIs map directly to persisted `HeatPump:AirToWater` fields used by the forward translator, including the wrapper-level schedule, air-node, and curve references.
    // - Evidence: `src/model/HeatPumpAirToWater.hpp`, `src/model/HeatPumpAirToWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWater.cpp`.
    // - Remaining Parity Work: Add the omitted heating/cooling operation-mode and loop lookup helpers without changing the preserved relationship signatures.
    std::string operatingModeControlMethod() const;
    bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);
    bool isOperatingModeControlMethodDefaulted() const;
    void resetOperatingModeControlMethod();

    std::string operatingModeControlOptionforMultipleUnit() const;
    bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);
    bool isOperatingModeControlOptionforMultipleUnitDefaulted() const;
    void resetOperatingModeControlOptionforMultipleUnit();

    boost::optional<Schedule> operatingModeControlSchedule() const;
    bool setOperatingModeControlSchedule(Schedule& operatingModeControlSchedule);
    void resetOperatingModeControlSchedule();

    double minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    bool isMinimumPartLoadRatioDefaulted() const;
    void resetMinimumPartLoadRatio();

    boost::optional<std::string> airInletNodeName() const;
    bool setAirInletNodeName(const std::string& airInletNodeName);
    void resetAirInletNodeName();

    boost::optional<std::string> airOutletNodeName() const;
    bool setAirOutletNodeName(const std::string& airOutletNodeName);
    void resetAirOutletNodeName();

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

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

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

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

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
