/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ComponentCostReference.hpp"
#include "ComponentCostReference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ComponentCost_Reference_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ComponentCostReference::ComponentCostReference(const Model& model) : ModelObject(ComponentCostReference::iddObjectType(), model) {}

ComponentCostReference::ComponentCostReference(std::shared_ptr<detail::ComponentCostReference_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ComponentCostReference::iddObjectType() {
  return IddObjectType::ComponentCost_Reference;
}

boost::optional<double> ComponentCostReference::referenceBuildingLineItemCosts() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingLineItemCosts();
}

bool ComponentCostReference::setReferenceBuildingLineItemCosts(double referenceBuildingLineItemCosts) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingLineItemCosts(referenceBuildingLineItemCosts);
}

void ComponentCostReference::resetReferenceBuildingLineItemCosts() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingLineItemCosts();
}

boost::optional<double> ComponentCostReference::referenceBuildingMiscellaneousCostperConditionedArea() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingMiscellaneousCostperConditionedArea();
}

bool ComponentCostReference::setReferenceBuildingMiscellaneousCostperConditionedArea(double referenceBuildingMiscellaneousCostperConditionedArea) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingMiscellaneousCostperConditionedArea(
    referenceBuildingMiscellaneousCostperConditionedArea);
}

void ComponentCostReference::resetReferenceBuildingMiscellaneousCostperConditionedArea() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingMiscellaneousCostperConditionedArea();
}

boost::optional<double> ComponentCostReference::referenceBuildingDesignandEngineeringFees() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingDesignandEngineeringFees();
}

bool ComponentCostReference::setReferenceBuildingDesignandEngineeringFees(double referenceBuildingDesignandEngineeringFees) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingDesignandEngineeringFees(referenceBuildingDesignandEngineeringFees);
}

void ComponentCostReference::resetReferenceBuildingDesignandEngineeringFees() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingDesignandEngineeringFees();
}

boost::optional<double> ComponentCostReference::referenceBuildingContractorFee() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingContractorFee();
}

bool ComponentCostReference::setReferenceBuildingContractorFee(double referenceBuildingContractorFee) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingContractorFee(referenceBuildingContractorFee);
}

void ComponentCostReference::resetReferenceBuildingContractorFee() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingContractorFee();
}

boost::optional<double> ComponentCostReference::referenceBuildingContingency() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingContingency();
}

bool ComponentCostReference::setReferenceBuildingContingency(double referenceBuildingContingency) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingContingency(referenceBuildingContingency);
}

void ComponentCostReference::resetReferenceBuildingContingency() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingContingency();
}

boost::optional<double> ComponentCostReference::referenceBuildingPermitsBondingandInsurance() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingPermitsBondingandInsurance();
}

bool ComponentCostReference::setReferenceBuildingPermitsBondingandInsurance(double referenceBuildingPermitsBondingandInsurance) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingPermitsBondingandInsurance(
    referenceBuildingPermitsBondingandInsurance);
}

void ComponentCostReference::resetReferenceBuildingPermitsBondingandInsurance() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingPermitsBondingandInsurance();
}

boost::optional<double> ComponentCostReference::referenceBuildingCommissioningFee() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingCommissioningFee();
}

bool ComponentCostReference::setReferenceBuildingCommissioningFee(double referenceBuildingCommissioningFee) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingCommissioningFee(referenceBuildingCommissioningFee);
}

void ComponentCostReference::resetReferenceBuildingCommissioningFee() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingCommissioningFee();
}

boost::optional<double> ComponentCostReference::referenceBuildingRegionalAdjustmentFactor() const {
  return getImpl<detail::ComponentCostReference_Impl>()->referenceBuildingRegionalAdjustmentFactor();
}

bool ComponentCostReference::setReferenceBuildingRegionalAdjustmentFactor(double referenceBuildingRegionalAdjustmentFactor) {
  return getImpl<detail::ComponentCostReference_Impl>()->setReferenceBuildingRegionalAdjustmentFactor(referenceBuildingRegionalAdjustmentFactor);
}

void ComponentCostReference::resetReferenceBuildingRegionalAdjustmentFactor() {
  getImpl<detail::ComponentCostReference_Impl>()->resetReferenceBuildingRegionalAdjustmentFactor();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ComponentCostReference_Impl::referenceBuildingLineItemCosts() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingLineItemCosts, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingLineItemCosts(double referenceBuildingLineItemCosts) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingLineItemCosts, referenceBuildingLineItemCosts);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingLineItemCosts() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingLineItemCosts, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingMiscellaneousCostperConditionedArea() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingMiscellaneousCostperConditionedArea, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingMiscellaneousCostperConditionedArea(double referenceBuildingMiscellaneousCostperConditionedArea) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingMiscellaneousCostperConditionedArea,
                                referenceBuildingMiscellaneousCostperConditionedArea);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingMiscellaneousCostperConditionedArea() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingMiscellaneousCostperConditionedArea, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingDesignandEngineeringFees() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingDesignandEngineeringFees, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingDesignandEngineeringFees(double referenceBuildingDesignandEngineeringFees) {
  const bool result =
    setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingDesignandEngineeringFees, referenceBuildingDesignandEngineeringFees);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingDesignandEngineeringFees() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingDesignandEngineeringFees, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingContractorFee() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContractorFee, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingContractorFee(double referenceBuildingContractorFee) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContractorFee, referenceBuildingContractorFee);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingContractorFee() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContractorFee, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingContingency() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContingency, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingContingency(double referenceBuildingContingency) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContingency, referenceBuildingContingency);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingContingency() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingContingency, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingPermitsBondingandInsurance() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingPermitsBondingandInsurance, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingPermitsBondingandInsurance(double referenceBuildingPermitsBondingandInsurance) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingPermitsBondingandInsurance,
                                referenceBuildingPermitsBondingandInsurance);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingPermitsBondingandInsurance() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingPermitsBondingandInsurance, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingCommissioningFee() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingCommissioningFee, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingCommissioningFee(double referenceBuildingCommissioningFee) {
  const bool result =
    setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingCommissioningFee, referenceBuildingCommissioningFee);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingCommissioningFee() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingCommissioningFee, ""));
}

boost::optional<double> ComponentCostReference_Impl::referenceBuildingRegionalAdjustmentFactor() const {
  return getDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingRegionalAdjustmentFactor, true);
}

bool ComponentCostReference_Impl::setReferenceBuildingRegionalAdjustmentFactor(double referenceBuildingRegionalAdjustmentFactor) {
  const bool result = setDouble(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingRegionalAdjustmentFactor,
                                referenceBuildingRegionalAdjustmentFactor);
  OS_ASSERT(result);
  return result;
}

void ComponentCostReference_Impl::resetReferenceBuildingRegionalAdjustmentFactor() {
  OS_ASSERT(setString(openstudio::ComponentCost_ReferenceFields::ReferenceBuildingRegionalAdjustmentFactor, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
