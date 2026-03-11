/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTREFERENCE_IMPL_HPP
#define EPMODEL_COMPONENTCOSTREFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ComponentCostReference_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ComponentCostReference_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
