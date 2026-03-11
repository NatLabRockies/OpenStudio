/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXMULTISPEED_HPP
#define EPMODEL_COILHEATINGDXMULTISPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingDXMultiSpeed_Impl;
}

class EPMODEL_API CoilHeatingDXMultiSpeed : public StraightComponent
{
 public:
  explicit CoilHeatingDXMultiSpeed(const Model& model);

  virtual ~CoilHeatingDXMultiSpeed() override = default;
  CoilHeatingDXMultiSpeed(const CoilHeatingDXMultiSpeed& other) = default;
  CoilHeatingDXMultiSpeed(CoilHeatingDXMultiSpeed&& other) = default;
  CoilHeatingDXMultiSpeed& operator=(const CoilHeatingDXMultiSpeed&) = default;
  CoilHeatingDXMultiSpeed& operator=(CoilHeatingDXMultiSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> defrostStrategyValues();
  static std::vector<std::string> defrostControlValues();
  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilHeatingDXMultiSpeed scalar accessor names/signatures.
  // - Field Mapping: APIs below map directly to EnergyPlus Coil:Heating:DX:MultiSpeed scalar fields.
  // - Field Mapping: Relationship/extensible fields (availability schedule, inlet/outlet nodes, curves, stages) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingDXMultiSpeed.cpp writes these scalar fields directly.
  // - TODO(parity): Add relationship and stage APIs later without changing preserved scalar signatures.
  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
  bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
  void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

  std::string defrostStrategy() const;
  bool setDefrostStrategy(const std::string& defrostStrategy);

  std::string defrostControl() const;
  bool setDefrostControl(const std::string& defrostControl);

  double defrostTimePeriodFraction() const;
  bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

  boost::optional<double> resistiveDefrostHeaterCapacity() const;
  bool isResistiveDefrostHeaterCapacityAutosized() const;
  bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
  void autosizeResistiveDefrostHeaterCapacity();

  bool applyPartLoadFractiontoSpeedsGreaterthan1() const;
  bool setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1);

  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);

  int regionnumberforCalculatingHSPF() const;
  bool setRegionnumberforCalculatingHSPF(int regionnumberforCalculatingHSPF);

 protected:
  using ImplType = detail::CoilHeatingDXMultiSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingDXMultiSpeed(std::shared_ptr<detail::CoilHeatingDXMultiSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
