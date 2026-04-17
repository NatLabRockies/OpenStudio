/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATER_IMPL_HPP
#define EPMODEL_HEATPUMPAIRTOWATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Schedule;
class Curve;
class Node;

namespace detail {

class EPMODEL_API HeatPumpAirToWater_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HeatPumpAirToWater_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;

  std::string operatingModeControlMethod() const;
  bool isOperatingModeControlMethodDefaulted() const;
  bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);
  void resetOperatingModeControlMethod();

  std::string operatingModeControlOptionforMultipleUnit() const;
  bool isOperatingModeControlOptionforMultipleUnitDefaulted() const;
  bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);
  void resetOperatingModeControlOptionforMultipleUnit();

  boost::optional<Schedule> operatingModeControlSchedule() const;
  bool setOperatingModeControlSchedule(Schedule& operatingModeControlSchedule);
  void resetOperatingModeControlSchedule();

  double minimumPartLoadRatio() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  boost::optional<std::string> airInletNodeName() const;
  bool setAirInletNodeName(const std::string& airInletNodeName);
  void resetAirInletNodeName();

  boost::optional<std::string> airOutletNodeName() const;
  bool setAirOutletNodeName(const std::string& airOutletNodeName);
  void resetAirOutletNodeName();

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

  boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);
  void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

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

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
  bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
  bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
  void resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();

  std::vector<std::string> operatingModeControlMethodValues() const;
  std::vector<std::string> operatingModeControlOptionforMultipleUnitValues() const;
  std::vector<std::string> heatPumpDefrostControlValues() const;
  std::vector<std::string> controlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
