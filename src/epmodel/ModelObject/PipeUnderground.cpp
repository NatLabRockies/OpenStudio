/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PipeUnderground.hpp"
#include "PipeUnderground_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pipe_Underground_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

PipeUnderground::PipeUnderground(const Model& model) : ModelObject(PipeUnderground::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::PipeUnderground_Impl>());

  bool ok = true;
  ok = setSunExposure("NoSun");
  OS_ASSERT(ok);
  ok = setSoilMaterialName("Soil Material");
  OS_ASSERT(ok);
  ok = setUndisturbedGroundTemperatureModelType("Site:GroundTemperature:Undisturbed:FiniteDifference");
  OS_ASSERT(ok);
}

PipeUnderground::PipeUnderground(std::shared_ptr<detail::PipeUnderground_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType PipeUnderground::iddObjectType() {
  return IddObjectType::Pipe_Underground;
}

std::vector<std::string> PipeUnderground::sunExposureValues() {
  return {"SunExposed", "NoSun"};
}

std::vector<std::string> PipeUnderground::undisturbedGroundTemperatureModelTypeValues() {
  return {"Site:GroundTemperature:Undisturbed:FiniteDifference", "Site:GroundTemperature:Undisturbed:KusudaAchenbach",
          "Site:GroundTemperature:Undisturbed:Xing"};
}

std::string PipeUnderground::sunExposure() const {
  return getImpl<detail::PipeUnderground_Impl>()->sunExposure();
}

boost::optional<double> PipeUnderground::pipeInsideDiameter() const {
  return getImpl<detail::PipeUnderground_Impl>()->pipeInsideDiameter();
}

boost::optional<double> PipeUnderground::pipeLength() const {
  return getImpl<detail::PipeUnderground_Impl>()->pipeLength();
}

std::string PipeUnderground::soilMaterialName() const {
  return getImpl<detail::PipeUnderground_Impl>()->soilMaterialName();
}

std::string PipeUnderground::undisturbedGroundTemperatureModelType() const {
  return getImpl<detail::PipeUnderground_Impl>()->undisturbedGroundTemperatureModelType();
}

bool PipeUnderground::isPipeInsideDiameterDefaulted() const {
  return getImpl<detail::PipeUnderground_Impl>()->isPipeInsideDiameterDefaulted();
}

bool PipeUnderground::isPipeLengthDefaulted() const {
  return getImpl<detail::PipeUnderground_Impl>()->isPipeLengthDefaulted();
}

bool PipeUnderground::setSunExposure(const std::string& sunExposure) {
  return getImpl<detail::PipeUnderground_Impl>()->setSunExposure(sunExposure);
}

bool PipeUnderground::setPipeInsideDiameter(double pipeInsideDiameter) {
  return getImpl<detail::PipeUnderground_Impl>()->setPipeInsideDiameter(pipeInsideDiameter);
}

bool PipeUnderground::setPipeLength(double pipeLength) {
  return getImpl<detail::PipeUnderground_Impl>()->setPipeLength(pipeLength);
}

bool PipeUnderground::setSoilMaterialName(const std::string& soilMaterialName) {
  return getImpl<detail::PipeUnderground_Impl>()->setSoilMaterialName(soilMaterialName);
}

bool PipeUnderground::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
  return getImpl<detail::PipeUnderground_Impl>()->setUndisturbedGroundTemperatureModelType(undisturbedGroundTemperatureModelType);
}

void PipeUnderground::resetPipeInsideDiameter() {
  getImpl<detail::PipeUnderground_Impl>()->resetPipeInsideDiameter();
}

void PipeUnderground::resetPipeLength() {
  getImpl<detail::PipeUnderground_Impl>()->resetPipeLength();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string PipeUnderground_Impl::sunExposure() const {
  const auto value = getString(openstudio::Pipe_UndergroundFields::SunExposure, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> PipeUnderground_Impl::pipeInsideDiameter() const {
  return getDouble(openstudio::Pipe_UndergroundFields::PipeInsideDiameter, true);
}

boost::optional<double> PipeUnderground_Impl::pipeLength() const {
  return getDouble(openstudio::Pipe_UndergroundFields::PipeLength, true);
}

std::string PipeUnderground_Impl::soilMaterialName() const {
  const auto value = getString(openstudio::Pipe_UndergroundFields::SoilMaterialName, true);
  OS_ASSERT(value);
  return *value;
}

std::string PipeUnderground_Impl::undisturbedGroundTemperatureModelType() const {
  const auto value = getString(openstudio::Pipe_UndergroundFields::UndisturbedGroundTemperatureModelType, true);
  OS_ASSERT(value);
  return *value;
}

bool PipeUnderground_Impl::isPipeInsideDiameterDefaulted() const {
  return isEmpty(openstudio::Pipe_UndergroundFields::PipeInsideDiameter);
}

bool PipeUnderground_Impl::isPipeLengthDefaulted() const {
  return isEmpty(openstudio::Pipe_UndergroundFields::PipeLength);
}

bool PipeUnderground_Impl::setSunExposure(const std::string& sunExposure) {
  return setString(openstudio::Pipe_UndergroundFields::SunExposure, sunExposure);
}

bool PipeUnderground_Impl::setPipeInsideDiameter(double pipeInsideDiameter) {
  return setDouble(openstudio::Pipe_UndergroundFields::PipeInsideDiameter, pipeInsideDiameter);
}

bool PipeUnderground_Impl::setPipeLength(double pipeLength) {
  return setDouble(openstudio::Pipe_UndergroundFields::PipeLength, pipeLength);
}

bool PipeUnderground_Impl::setSoilMaterialName(const std::string& soilMaterialName) {
  return setString(openstudio::Pipe_UndergroundFields::SoilMaterialName, soilMaterialName);
}

bool PipeUnderground_Impl::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
  return setString(openstudio::Pipe_UndergroundFields::UndisturbedGroundTemperatureModelType, undisturbedGroundTemperatureModelType);
}

void PipeUnderground_Impl::resetPipeInsideDiameter() {
  OS_ASSERT(setString(openstudio::Pipe_UndergroundFields::PipeInsideDiameter, ""));
}

void PipeUnderground_Impl::resetPipeLength() {
  OS_ASSERT(setString(openstudio::Pipe_UndergroundFields::PipeLength, ""));
}

std::vector<std::string> PipeUnderground_Impl::sunExposureValues() const {
  return openstudio::epmodel::PipeUnderground::sunExposureValues();
}

std::vector<std::string> PipeUnderground_Impl::undisturbedGroundTemperatureModelTypeValues() const {
  return openstudio::epmodel::PipeUnderground::undisturbedGroundTemperatureModelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
