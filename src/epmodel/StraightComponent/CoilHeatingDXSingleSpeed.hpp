/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXSINGLESPEED_HPP
#define EPMODEL_COILHEATINGDXSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingDXSingleSpeed_Impl;
}

class EPMODEL_API CoilHeatingDXSingleSpeed : public StraightComponent
{
 public:
  explicit CoilHeatingDXSingleSpeed(const Model& model);

  virtual ~CoilHeatingDXSingleSpeed() override = default;
  CoilHeatingDXSingleSpeed(const CoilHeatingDXSingleSpeed& other) = default;
  CoilHeatingDXSingleSpeed(CoilHeatingDXSingleSpeed&& other) = default;
  CoilHeatingDXSingleSpeed& operator=(const CoilHeatingDXSingleSpeed&) = default;
  CoilHeatingDXSingleSpeed& operator=(CoilHeatingDXSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validDefrostStrategyValues();
  static std::vector<std::string> validDefrostControlValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilHeatingDXSingleSpeed scalar accessor names/signatures.
  // - Field Mapping: ratedTotalHeatingCapacity/ratedCOP map to E+ GrossRatedHeatingCapacity/GrossRatedHeatingCOP.
  // - Field Mapping: Deprecated ratedSupplyFanPowerPerVolumeFlowRate delegates to 2017 field API.
  // - Field Mapping: Relationship-like fields (schedules, curves, and node links) are excluded in this pass.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingDXSingleSpeed.cpp writes these scalar fields directly.
  // - TODO(parity): Add excluded relationship APIs later without changing preserved scalar signatures.
  boost::optional<double> ratedTotalHeatingCapacity() const;
  bool isRatedTotalHeatingCapacityAutosized() const;

  double ratedCOP() const;

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateAutosized() const;

  double ratedSupplyFanPowerPerVolumeFlowRate() const;
  double ratedSupplyFanPowerPerVolumeFlowRate2017() const;
  double ratedSupplyFanPowerPerVolumeFlowRate2023() const;

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const;

  double crankcaseHeaterCapacity() const;
  bool isCrankcaseHeaterCapacityDefaulted() const;

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const;

  std::string defrostStrategy() const;
  bool isDefrostStrategyDefaulted() const;

  std::string defrostControl() const;
  bool isDefrostControlDefaulted() const;

  double defrostTimePeriodFraction() const;
  bool isDefrostTimePeriodFractionDefaulted() const;

  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityDefaulted() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;

  bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
  void autosizeRatedTotalHeatingCapacity();

  bool setRatedCOP(double ratedCOP);

  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void autosizeRatedAirFlowRate();

  bool setRatedSupplyFanPowerPerVolumeFlowRate(double ratedSupplyFanPowerPerVolumeFlowRate);
  bool setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017);
  bool setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023);

  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
  void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);
  void resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();

  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
  void resetCrankcaseHeaterCapacity();

  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  void resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();

  bool setDefrostStrategy(const std::string& defrostStrategy);
  void resetDefrostStrategy();

  bool setDefrostControl(const std::string& defrostControl);
  void resetDefrostControl();

  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
  void resetDefrostTimePeriodFraction();

  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void resetResistiveDefrostHeaterCapacity();
  void autosizeResistiveDefrostHeaterCapacity();

 protected:
  using ImplType = detail::CoilHeatingDXSingleSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingDXSingleSpeed(std::shared_ptr<detail::CoilHeatingDXSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
