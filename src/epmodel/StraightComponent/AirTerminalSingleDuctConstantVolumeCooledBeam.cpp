/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_CooledBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctConstantVolumeCooledBeam::AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model)
  : ModelObject(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType(), model) {
  // Mirror model constructor behavior for this required choice field.
  OS_ASSERT(setCooledBeamType("Passive"));
}

AirTerminalSingleDuctConstantVolumeCooledBeam::AirTerminalSingleDuctConstantVolumeCooledBeam(
  std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam;
}

std::vector<std::string> AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType);
}

std::string AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamType() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->cooledBeamType();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setCooledBeamType(const std::string& cooledBeamType) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setCooledBeamType(cooledBeamType);
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::supplyAirVolumetricFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->supplyAirVolumetricFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isSupplyAirVolumetricFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isSupplyAirVolumetricFlowRateDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isSupplyAirVolumetricFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isSupplyAirVolumetricFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setSupplyAirVolumetricFlowRate(supplyAirVolumetricFlowRate);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetSupplyAirVolumetricFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetSupplyAirVolumetricFlowRate();
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeSupplyAirVolumetricFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeSupplyAirVolumetricFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::maximumTotalChilledWaterVolumetricFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->maximumTotalChilledWaterVolumetricFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isMaximumTotalChilledWaterVolumetricFlowRateDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isMaximumTotalChilledWaterVolumetricFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setMaximumTotalChilledWaterVolumetricFlowRate(
  double maximumTotalChilledWaterVolumetricFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setMaximumTotalChilledWaterVolumetricFlowRate(
    maximumTotalChilledWaterVolumetricFlowRate);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetMaximumTotalChilledWaterVolumetricFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetMaximumTotalChilledWaterVolumetricFlowRate();
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeMaximumTotalChilledWaterVolumetricFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeMaximumTotalChilledWaterVolumetricFlowRate();
}

boost::optional<int> AirTerminalSingleDuctConstantVolumeCooledBeam::numberofBeams() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->numberofBeams();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isNumberofBeamsDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isNumberofBeamsDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isNumberofBeamsAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isNumberofBeamsAutosized();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setNumberofBeams(int numberofBeams) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setNumberofBeams(numberofBeams);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetNumberofBeams() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetNumberofBeams();
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeNumberofBeams() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeNumberofBeams();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::beamLength() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->beamLength();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isBeamLengthDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isBeamLengthDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isBeamLengthAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isBeamLengthAutosized();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setBeamLength(double beamLength) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setBeamLength(beamLength);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetBeamLength();
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeBeamLength();
}

double AirTerminalSingleDuctConstantVolumeCooledBeam::designInletWaterTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->designInletWaterTemperature();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isDesignInletWaterTemperatureDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isDesignInletWaterTemperatureDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setDesignInletWaterTemperature(double designInletWaterTemperature) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setDesignInletWaterTemperature(designInletWaterTemperature);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetDesignInletWaterTemperature() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetDesignInletWaterTemperature();
}

double AirTerminalSingleDuctConstantVolumeCooledBeam::designOutletWaterTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->designOutletWaterTemperature();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isDesignOutletWaterTemperatureDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isDesignOutletWaterTemperatureDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setDesignOutletWaterTemperature(double designOutletWaterTemperature) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setDesignOutletWaterTemperature(designOutletWaterTemperature);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetDesignOutletWaterTemperature() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetDesignOutletWaterTemperature();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::coefficientofInductionKin() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->coefficientofInductionKin();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isCoefficientofInductionKinDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isCoefficientofInductionKinDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::isCoefficientofInductionKinAutocalculated() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isCoefficientofInductionKinAutocalculated();
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam::setCoefficientofInductionKin(double coefficientofInductionKin) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setCoefficientofInductionKin(coefficientofInductionKin);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::resetCoefficientofInductionKin() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetCoefficientofInductionKin();
}

void AirTerminalSingleDuctConstantVolumeCooledBeam::autocalculateCoefficientofInductionKin() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autocalculateCoefficientofInductionKin();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::cooledBeamType() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setCooledBeamType(const std::string& cooledBeamType) {
  return setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, cooledBeamType);
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::supplyAirVolumetricFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isSupplyAirVolumetricFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isSupplyAirVolumetricFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, supplyAirVolumetricFlowRate);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetSupplyAirVolumetricFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeSupplyAirVolumetricFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::maximumTotalChilledWaterVolumetricFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const {
  if (auto value =
        getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setMaximumTotalChilledWaterVolumetricFlowRate(
  double maximumTotalChilledWaterVolumetricFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate,
                   maximumTotalChilledWaterVolumetricFlowRate);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetMaximumTotalChilledWaterVolumetricFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeMaximumTotalChilledWaterVolumetricFlowRate() {
  OS_ASSERT(
    setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, "autosize"));
}

boost::optional<int> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::numberofBeams() const {
  return getInt(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, true);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isNumberofBeamsDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isNumberofBeamsAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setNumberofBeams(int numberofBeams) {
  return setInt(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, numberofBeams);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetNumberofBeams() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, ""));
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeNumberofBeams() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::beamLength() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, true);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isBeamLengthDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isBeamLengthAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setBeamLength(double beamLength) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, beamLength);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, ""));
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::designInletWaterTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isDesignInletWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setDesignInletWaterTemperature(double designInletWaterTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, designInletWaterTemperature);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetDesignInletWaterTemperature() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, ""));
}

double AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::designOutletWaterTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isDesignOutletWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setDesignOutletWaterTemperature(double designOutletWaterTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, designOutletWaterTemperature);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetDesignOutletWaterTemperature() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, ""));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::coefficientofInductionKin() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, true);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isCoefficientofInductionKinDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin);
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isCoefficientofInductionKinAutocalculated() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setCoefficientofInductionKin(double coefficientofInductionKin) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, coefficientofInductionKin);
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetCoefficientofInductionKin() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, ""));
}

void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autocalculateCoefficientofInductionKin() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, "autocalculate"));
}

std::vector<std::string> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::cooledBeamTypeValues() const {
  return openstudio::epmodel::AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
