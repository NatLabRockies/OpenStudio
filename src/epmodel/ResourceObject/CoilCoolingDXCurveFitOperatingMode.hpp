/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITOPERATINGMODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingDXCurveFitOperatingMode_Impl;
}

class EPMODEL_API CoilCoolingDXCurveFitOperatingMode : public ModelObject
{
 public:
  explicit CoilCoolingDXCurveFitOperatingMode(const Model& model);

  virtual ~CoilCoolingDXCurveFitOperatingMode() override = default;
  CoilCoolingDXCurveFitOperatingMode(const CoilCoolingDXCurveFitOperatingMode& other) = default;
  CoilCoolingDXCurveFitOperatingMode(CoilCoolingDXCurveFitOperatingMode&& other) = default;
  CoilCoolingDXCurveFitOperatingMode& operator=(const CoilCoolingDXCurveFitOperatingMode&) = default;
  CoilCoolingDXCurveFitOperatingMode& operator=(CoilCoolingDXCurveFitOperatingMode&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Preserved scalar APIs map directly to matching E+ Coil:Cooling:DX:CurveFit:OperatingMode fields.
  // - Field Mapping: Relationship/extensible Speed Name links are intentionally excluded in this scalar scaffold phase.
  // - TODO(parity): Add non-scalar speed/performance relationship API parity incrementally after scalar saturation.
  boost::optional<double> ratedGrossTotalCoolingCapacity() const;
  bool isRatedGrossTotalCoolingCapacityAutosized() const;

  boost::optional<double> ratedEvaporatorAirFlowRate() const;
  bool isRatedEvaporatorAirFlowRateAutosized() const;

  boost::optional<double> ratedCondenserAirFlowRate() const;
  bool isRatedCondenserAirFlowRateAutosized() const;

  double maximumCyclingRate() const;

  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;

  double latentCapacityTimeConstant() const;

  double nominalTimeforCondensateRemovaltoBegin() const;

  bool applyLatentDegradationtoSpeedsGreaterthan1() const;

  std::string condenserType() const;

  boost::optional<double> nominalEvaporativeCondenserPumpPower() const;
  bool isNominalEvaporativeCondenserPumpPowerAutosized() const;

  unsigned nominalSpeedNumber() const;
  bool isNominalSpeedNumberDefaulted() const;

  bool setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity);
  void autosizeRatedGrossTotalCoolingCapacity();

  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  void autosizeRatedEvaporatorAirFlowRate();

  bool setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate);
  void autosizeRatedCondenserAirFlowRate();

  bool setMaximumCyclingRate(double maximumCyclingRate);

  bool setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);

  bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

  bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);

  bool setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1);

  bool setCondenserType(const std::string& condenserType);

  bool setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower);
  void autosizeNominalEvaporativeCondenserPumpPower();

  bool setNominalSpeedNumber(unsigned nominalSpeedNumber);
  void resetNominalSpeedNumber();

 protected:
  using ImplType = detail::CoilCoolingDXCurveFitOperatingMode_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXCurveFitOperatingMode(std::shared_ptr<detail::CoilCoolingDXCurveFitOperatingMode_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
