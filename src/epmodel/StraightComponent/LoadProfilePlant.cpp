/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LoadProfilePlant.hpp"
#include "LoadProfilePlant_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/LoadProfile_Plant_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

LoadProfilePlant::LoadProfilePlant(const Model& model) : StraightComponent(LoadProfilePlant::iddObjectType(), model) {}

LoadProfilePlant::LoadProfilePlant(std::shared_ptr<detail::LoadProfilePlant_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType LoadProfilePlant::iddObjectType() {
  return IddObjectType::LoadProfile_Plant;
}

std::vector<std::string> LoadProfilePlant::plantLoopFluidTypeValues() {
  return {"Water", "Steam"};
}

double LoadProfilePlant::peakFlowRate() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->peakFlowRate();
}

bool LoadProfilePlant::setPeakFlowRate(double peakFlowRate) {
  return getImpl<detail::LoadProfilePlant_Impl>()->setPeakFlowRate(peakFlowRate);
}

std::string LoadProfilePlant::plantLoopFluidType() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->plantLoopFluidType();
}

bool LoadProfilePlant::setPlantLoopFluidType(const std::string& plantLoopFluidType) {
  return getImpl<detail::LoadProfilePlant_Impl>()->setPlantLoopFluidType(plantLoopFluidType);
}

bool LoadProfilePlant::isPlantLoopFluidTypeDefaulted() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->isPlantLoopFluidTypeDefaulted();
}

void LoadProfilePlant::resetPlantLoopFluidType() {
  getImpl<detail::LoadProfilePlant_Impl>()->resetPlantLoopFluidType();
}

double LoadProfilePlant::degreeofSubCooling() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->degreeofSubCooling();
}

bool LoadProfilePlant::setDegreeofSubCooling(double degreeofSubCooling) {
  return getImpl<detail::LoadProfilePlant_Impl>()->setDegreeofSubCooling(degreeofSubCooling);
}

bool LoadProfilePlant::isDegreeofSubCoolingDefaulted() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->isDegreeofSubCoolingDefaulted();
}

void LoadProfilePlant::resetDegreeofSubCooling() {
  getImpl<detail::LoadProfilePlant_Impl>()->resetDegreeofSubCooling();
}

double LoadProfilePlant::degreeofLoopSubCooling() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->degreeofLoopSubCooling();
}

bool LoadProfilePlant::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
  return getImpl<detail::LoadProfilePlant_Impl>()->setDegreeofLoopSubCooling(degreeofLoopSubCooling);
}

bool LoadProfilePlant::isDegreeofLoopSubCoolingDefaulted() const {
  return getImpl<detail::LoadProfilePlant_Impl>()->isDegreeofLoopSubCoolingDefaulted();
}

void LoadProfilePlant::resetDegreeofLoopSubCooling() {
  getImpl<detail::LoadProfilePlant_Impl>()->resetDegreeofLoopSubCooling();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned LoadProfilePlant_Impl::inletPort() const {
  return LoadProfile_PlantFields::InletNodeName;
}

unsigned LoadProfilePlant_Impl::outletPort() const {
  return LoadProfile_PlantFields::OutletNodeName;
}

double LoadProfilePlant_Impl::peakFlowRate() const {
  const auto value = getDouble(openstudio::LoadProfile_PlantFields::PeakFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool LoadProfilePlant_Impl::setPeakFlowRate(double peakFlowRate) {
  const bool result = setDouble(openstudio::LoadProfile_PlantFields::PeakFlowRate, peakFlowRate);
  OS_ASSERT(result);
  return result;
}

std::string LoadProfilePlant_Impl::plantLoopFluidType() const {
  const auto value = getString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, true);
  OS_ASSERT(value);
  return *value;
}

bool LoadProfilePlant_Impl::setPlantLoopFluidType(const std::string& plantLoopFluidType) {
  return setString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, plantLoopFluidType);
}

bool LoadProfilePlant_Impl::isPlantLoopFluidTypeDefaulted() const {
  return isEmpty(openstudio::LoadProfile_PlantFields::PlantLoopFluidType);
}

void LoadProfilePlant_Impl::resetPlantLoopFluidType() {
  const bool result = setString(openstudio::LoadProfile_PlantFields::PlantLoopFluidType, "");
  OS_ASSERT(result);
}

double LoadProfilePlant_Impl::degreeofSubCooling() const {
  const auto value = getDouble(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, true);
  OS_ASSERT(value);
  return *value;
}

bool LoadProfilePlant_Impl::setDegreeofSubCooling(double degreeofSubCooling) {
  return setDouble(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, degreeofSubCooling);
}

bool LoadProfilePlant_Impl::isDegreeofSubCoolingDefaulted() const {
  return isEmpty(openstudio::LoadProfile_PlantFields::DegreeofSubCooling);
}

void LoadProfilePlant_Impl::resetDegreeofSubCooling() {
  const bool result = setString(openstudio::LoadProfile_PlantFields::DegreeofSubCooling, "");
  OS_ASSERT(result);
}

double LoadProfilePlant_Impl::degreeofLoopSubCooling() const {
  const auto value = getDouble(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, true);
  OS_ASSERT(value);
  return *value;
}

bool LoadProfilePlant_Impl::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
  return setDouble(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, degreeofLoopSubCooling);
}

bool LoadProfilePlant_Impl::isDegreeofLoopSubCoolingDefaulted() const {
  return isEmpty(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling);
}

void LoadProfilePlant_Impl::resetDegreeofLoopSubCooling() {
  const bool result = setString(openstudio::LoadProfile_PlantFields::DegreeofLoopSubCooling, "");
  OS_ASSERT(result);
}

std::vector<std::string> LoadProfilePlant_Impl::plantLoopFluidTypeValues() const {
  return openstudio::epmodel::LoadProfilePlant::plantLoopFluidTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
