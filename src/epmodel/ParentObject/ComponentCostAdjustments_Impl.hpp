/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTADJUSTMENTS_IMPL_HPP
#define EPMODEL_COMPONENTCOSTADJUSTMENTS_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ComponentCostAdjustments_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~ComponentCostAdjustments_Impl() override = default;

  boost::optional<double> miscellaneousCostperConditionedArea() const;
  bool setMiscellaneousCostperConditionedArea(double miscellaneousCostperConditionedArea);
  void resetMiscellaneousCostperConditionedArea();

  boost::optional<double> designandEngineeringFees() const;
  bool setDesignandEngineeringFees(double designandEngineeringFees);
  void resetDesignandEngineeringFees();

  boost::optional<double> contractorFee() const;
  bool setContractorFee(double contractorFee);
  void resetContractorFee();

  boost::optional<double> contingency() const;
  bool setContingency(double contingency);
  void resetContingency();

  boost::optional<double> permitsBondingandInsurance() const;
  bool setPermitsBondingandInsurance(double permitsBondingandInsurance);
  void resetPermitsBondingandInsurance();

  boost::optional<double> commissioningFee() const;
  bool setCommissioningFee(double commissioningFee);
  void resetCommissioningFee();

  boost::optional<double> regionalAdjustmentFactor() const;
  bool setRegionalAdjustmentFactor(double regionalAdjustmentFactor);
  void resetRegionalAdjustmentFactor();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
