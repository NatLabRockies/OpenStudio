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
    // - API: Preserve openstudio::model::HeatPumpAirToWater scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: operatingModeControl* and heatPumpDefrost*/controlType map directly to matching E+ HeatPump:AirToWater fields.
    // - Field Mapping: minimumPartLoadRatio, maximumOutdoorDryBulbTemperatureForDefrostOperation,
    //   resistiveDefrostHeaterCapacity, heatPumpMultiplier, crankcaseHeaterCapacity, and
    //   maximumAmbientTemperatureforCrankcaseHeaterOperation map directly to same-name E+ scalar fields.
    // - ForwardTranslator evidence: ForwardTranslateHeatPumpAirToWater.cpp writes these scalar APIs directly to HeatPump:AirToWater.
    // - TODO(parity): schedule/curve/node and speed-data relationship fields remain intentionally excluded from this scalar scaffold.
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
