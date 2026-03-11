/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORINTERNALCOMBUSTIONENGINE_HPP
#define EPMODEL_GENERATORINTERNALCOMBUSTIONENGINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorInternalCombustionEngine_Impl;
}

class EPMODEL_API GeneratorInternalCombustionEngine : public ModelObject
{
 public:
  explicit GeneratorInternalCombustionEngine(const Model& model);

  virtual ~GeneratorInternalCombustionEngine() override = default;
  GeneratorInternalCombustionEngine(const GeneratorInternalCombustionEngine& other) = default;
  GeneratorInternalCombustionEngine(GeneratorInternalCombustionEngine&& other) = default;
  GeneratorInternalCombustionEngine& operator=(const GeneratorInternalCombustionEngine&) = default;
  GeneratorInternalCombustionEngine& operator=(GeneratorInternalCombustionEngine&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived scalar accessor names.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Generator:InternalCombustionEngine scalar fields.
  // - Field Mapping: Relationship-like fields are excluded from this scalar scaffold: Electric Circuit Node Name, all object-list curve name fields,
  //   and Heat Recovery Inlet/Outlet Node Name.
  // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
  boost::optional<double> ratedPowerOutput() const;
  bool setRatedPowerOutput(double ratedPowerOutput);

  boost::optional<double> minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  boost::optional<double> maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

  boost::optional<double> optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);

  boost::optional<double> coefficient1ofUFactorTimesAreaCurve() const;
  bool setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve);

  boost::optional<double> coefficient2ofUFactorTimesAreaCurve() const;
  bool setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve);

  boost::optional<double> maximumExhaustFlowperUnitofPowerOutput() const;
  bool setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput);

  boost::optional<double> designMinimumExhaustTemperature() const;
  bool setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature);

  boost::optional<double> fuelHigherHeatingValue() const;
  bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);

  double designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateDefaulted() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void resetDesignHeatRecoveryWaterFlowRate();

  std::string fuelType() const;
  bool isFuelTypeDefaulted() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  double heatRecoveryMaximumTemperature() const;
  bool isHeatRecoveryMaximumTemperatureDefaulted() const;
  bool setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature);
  void resetHeatRecoveryMaximumTemperature();

 protected:
  using ImplType = detail::GeneratorInternalCombustionEngine_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorInternalCombustionEngine(std::shared_ptr<detail::GeneratorInternalCombustionEngine_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
