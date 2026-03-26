/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model)
  : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), model) {
  autosizeDesignPrimaryAirVolumeFlowRate();
  autosizeDesignChilledWaterVolumeFlowRate();
  autosizeDesignHotWaterVolumeFlowRate();
  autosizeZoneTotalBeamLength();
}

AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(
  std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam;
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designPrimaryAirVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designPrimaryAirVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignPrimaryAirVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignPrimaryAirVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignPrimaryAirVolumeFlowRate(designPrimaryAirVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignPrimaryAirVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignPrimaryAirVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designChilledWaterVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designChilledWaterVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignChilledWaterVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignChilledWaterVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignChilledWaterVolumeFlowRate(
    designChilledWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignChilledWaterVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignChilledWaterVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designHotWaterVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designHotWaterVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignHotWaterVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignHotWaterVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignHotWaterVolumeFlowRate(designHotWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignHotWaterVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignHotWaterVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::zoneTotalBeamLength() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->zoneTotalBeamLength();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isZoneTotalBeamLengthAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isZoneTotalBeamLengthAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setZoneTotalBeamLength(double zoneTotalBeamLength) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setZoneTotalBeamLength(zoneTotalBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeZoneTotalBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeZoneTotalBeamLength();
}

double AirTerminalSingleDuctConstantVolumeFourPipeBeam::ratedPrimaryAirFlowRateperBeamLength() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->ratedPrimaryAirFlowRateperBeamLength();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isRatedPrimaryAirFlowRateperBeamLengthDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setRatedPrimaryAirFlowRateperBeamLength(
    ratedPrimaryAirFlowRateperBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::resetRatedPrimaryAirFlowRateperBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->resetRatedPrimaryAirFlowRateperBeamLength();
}

unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirInletNodeName;
}

unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirOutletNodeName;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designPrimaryAirVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignPrimaryAirVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate,
                   designPrimaryAirVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignPrimaryAirVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designChilledWaterVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignChilledWaterVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate,
                   designChilledWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignChilledWaterVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designHotWaterVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignHotWaterVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, designHotWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignHotWaterVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::zoneTotalBeamLength() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isZoneTotalBeamLengthAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setZoneTotalBeamLength(double zoneTotalBeamLength) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, zoneTotalBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeZoneTotalBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::ratedPrimaryAirFlowRateperBeamLength() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength,
                   ratedPrimaryAirFlowRateperBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::resetRatedPrimaryAirFlowRateperBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
