/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerPond.hpp"
#include "GroundHeatExchangerPond_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Pond_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatExchangerPond::GroundHeatExchangerPond(const Model& model) : ModelObject(GroundHeatExchangerPond::iddObjectType(), model) {
  bool ok = true;
  ok = setPondDepth(3.0);
  OS_ASSERT(ok);
  ok = setPondArea(100.0);
  OS_ASSERT(ok);
  ok = setHydronicTubingInsideDiameter(0.02);
  OS_ASSERT(ok);
  ok = setHydronicTubingOutsideDiameter(0.025);
  OS_ASSERT(ok);
  ok = setHydronicTubingThermalConductivity(0.4);
  OS_ASSERT(ok);
  ok = setGroundThermalConductivity(1.0);
  OS_ASSERT(ok);
  ok = setNumberofTubingCircuits(1);
  OS_ASSERT(ok);
  ok = setLengthofEachTubingCircuit(100.0);
  OS_ASSERT(ok);
}

GroundHeatExchangerPond::GroundHeatExchangerPond(std::shared_ptr<detail::GroundHeatExchangerPond_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatExchangerPond::iddObjectType() {
  return IddObjectType::GroundHeatExchanger_Pond;
}

double GroundHeatExchangerPond::pondDepth() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->pondDepth();
}

double GroundHeatExchangerPond::pondArea() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->pondArea();
}

double GroundHeatExchangerPond::hydronicTubingInsideDiameter() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->hydronicTubingInsideDiameter();
}

double GroundHeatExchangerPond::hydronicTubingOutsideDiameter() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->hydronicTubingOutsideDiameter();
}

double GroundHeatExchangerPond::hydronicTubingThermalConductivity() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->hydronicTubingThermalConductivity();
}

double GroundHeatExchangerPond::groundThermalConductivity() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->groundThermalConductivity();
}

int GroundHeatExchangerPond::numberofTubingCircuits() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->numberofTubingCircuits();
}

double GroundHeatExchangerPond::lengthofEachTubingCircuit() const {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->lengthofEachTubingCircuit();
}

bool GroundHeatExchangerPond::setPondDepth(double pondDepth) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setPondDepth(pondDepth);
}

bool GroundHeatExchangerPond::setPondArea(double pondArea) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setPondArea(pondArea);
}

bool GroundHeatExchangerPond::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
}

bool GroundHeatExchangerPond::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
}

bool GroundHeatExchangerPond::setHydronicTubingThermalConductivity(double hydronicTubingThermalConductivity) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setHydronicTubingThermalConductivity(hydronicTubingThermalConductivity);
}

bool GroundHeatExchangerPond::setGroundThermalConductivity(double groundThermalConductivity) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setGroundThermalConductivity(groundThermalConductivity);
}

bool GroundHeatExchangerPond::setNumberofTubingCircuits(int numberofTubingCircuits) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setNumberofTubingCircuits(numberofTubingCircuits);
}

bool GroundHeatExchangerPond::setLengthofEachTubingCircuit(double lengthofEachTubingCircuit) {
  return getImpl<detail::GroundHeatExchangerPond_Impl>()->setLengthofEachTubingCircuit(lengthofEachTubingCircuit);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatExchangerPond_Impl::pondDepth() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::PondDepth, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::pondArea() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::PondArea, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::hydronicTubingInsideDiameter() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingInsideDiameter, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::hydronicTubingOutsideDiameter() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingOutsideDiameter, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::hydronicTubingThermalConductivity() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::groundThermalConductivity() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::GroundThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

int GroundHeatExchangerPond_Impl::numberofTubingCircuits() const {
  const auto value = getInt(openstudio::GroundHeatExchanger_PondFields::NumberofTubingCircuits, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerPond_Impl::lengthofEachTubingCircuit() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_PondFields::LengthofEachTubingCircuit, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatExchangerPond_Impl::setPondDepth(double pondDepth) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::PondDepth, pondDepth);
}

bool GroundHeatExchangerPond_Impl::setPondArea(double pondArea) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::PondArea, pondArea);
}

bool GroundHeatExchangerPond_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingInsideDiameter, hydronicTubingInsideDiameter);
}

bool GroundHeatExchangerPond_Impl::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingOutsideDiameter, hydronicTubingOutsideDiameter);
}

bool GroundHeatExchangerPond_Impl::setHydronicTubingThermalConductivity(double hydronicTubingThermalConductivity) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::HydronicTubingThermalConductivity, hydronicTubingThermalConductivity);
}

bool GroundHeatExchangerPond_Impl::setGroundThermalConductivity(double groundThermalConductivity) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::GroundThermalConductivity, groundThermalConductivity);
}

bool GroundHeatExchangerPond_Impl::setNumberofTubingCircuits(int numberofTubingCircuits) {
  return setInt(openstudio::GroundHeatExchanger_PondFields::NumberofTubingCircuits, numberofTubingCircuits);
}

bool GroundHeatExchangerPond_Impl::setLengthofEachTubingCircuit(double lengthofEachTubingCircuit) {
  return setDouble(openstudio::GroundHeatExchanger_PondFields::LengthofEachTubingCircuit, lengthofEachTubingCircuit);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
