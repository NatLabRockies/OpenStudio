/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTREFERENCE_HPP
#define EPMODEL_COMPONENTCOSTREFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ComponentCostReference_Impl;
}

class EPMODEL_API ComponentCostReference : public ModelObject
{
 public:
  explicit ComponentCostReference(const Model& model);

  virtual ~ComponentCostReference() override = default;
  ComponentCostReference(const ComponentCostReference& other) = default;
  ComponentCostReference(ComponentCostReference&& other) = default;
  ComponentCostReference& operator=(const ComponentCostReference&) = default;
  ComponentCostReference& operator=(ComponentCostReference&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar accessors map directly to EnergyPlus ComponentCost:Reference scalar fields.
  // - Field Mapping: Relationship-like/object-list/reference fields are not present on this object.
  // - TODO(parity): Revisit only if future model parity introduces a canonical counterpart API.
  boost::optional<double> referenceBuildingLineItemCosts() const;
  bool setReferenceBuildingLineItemCosts(double referenceBuildingLineItemCosts);
  void resetReferenceBuildingLineItemCosts();

  boost::optional<double> referenceBuildingMiscellaneousCostperConditionedArea() const;
  bool setReferenceBuildingMiscellaneousCostperConditionedArea(double referenceBuildingMiscellaneousCostperConditionedArea);
  void resetReferenceBuildingMiscellaneousCostperConditionedArea();

  boost::optional<double> referenceBuildingDesignandEngineeringFees() const;
  bool setReferenceBuildingDesignandEngineeringFees(double referenceBuildingDesignandEngineeringFees);
  void resetReferenceBuildingDesignandEngineeringFees();

  boost::optional<double> referenceBuildingContractorFee() const;
  bool setReferenceBuildingContractorFee(double referenceBuildingContractorFee);
  void resetReferenceBuildingContractorFee();

  boost::optional<double> referenceBuildingContingency() const;
  bool setReferenceBuildingContingency(double referenceBuildingContingency);
  void resetReferenceBuildingContingency();

  boost::optional<double> referenceBuildingPermitsBondingandInsurance() const;
  bool setReferenceBuildingPermitsBondingandInsurance(double referenceBuildingPermitsBondingandInsurance);
  void resetReferenceBuildingPermitsBondingandInsurance();

  boost::optional<double> referenceBuildingCommissioningFee() const;
  bool setReferenceBuildingCommissioningFee(double referenceBuildingCommissioningFee);
  void resetReferenceBuildingCommissioningFee();

  boost::optional<double> referenceBuildingRegionalAdjustmentFactor() const;
  bool setReferenceBuildingRegionalAdjustmentFactor(double referenceBuildingRegionalAdjustmentFactor);
  void resetReferenceBuildingRegionalAdjustmentFactor();

 protected:
  using ImplType = detail::ComponentCostReference_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ComponentCostReference(std::shared_ptr<detail::ComponentCostReference_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
