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
  bool isOperatingModeControlMethodDefaulted() const;
  bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);
  void resetOperatingModeControlMethod();

  std::string operatingModeControlOptionforMultipleUnit() const;
  bool isOperatingModeControlOptionforMultipleUnitDefaulted() const;
  bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);
  void resetOperatingModeControlOptionforMultipleUnit();

  double minimumPartLoadRatio() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted() const;
  bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);
  void resetMaximumOutdoorDryBulbTemperatureForDefrostOperation();

  std::string heatPumpDefrostControl() const;
  bool isHeatPumpDefrostControlDefaulted() const;
  bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
  void resetHeatPumpDefrostControl();

  double heatPumpDefrostTimePeriodFraction() const;
  bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
  bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
  void resetHeatPumpDefrostTimePeriodFraction();

  double resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityDefaulted() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void resetResistiveDefrostHeaterCapacity();

  int heatPumpMultiplier() const;
  bool isHeatPumpMultiplierDefaulted() const;
  bool setHeatPumpMultiplier(int heatPumpMultiplier);
  void resetHeatPumpMultiplier();

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  double crankcaseHeaterCapacity() const;
  bool isCrankcaseHeaterCapacityDefaulted() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
  void resetCrankcaseHeaterCapacity();

  double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
  bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
  bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
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
