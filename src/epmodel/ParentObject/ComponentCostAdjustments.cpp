/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ComponentCostAdjustments.hpp"
#include "ParentObject/ComponentCostAdjustments_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ComponentCost_Adjustments_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ComponentCostAdjustments::ComponentCostAdjustments(const Model& model) : ParentObject(ComponentCostAdjustments::iddObjectType(), model) {}

  ComponentCostAdjustments::ComponentCostAdjustments(std::shared_ptr<detail::ComponentCostAdjustments_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType ComponentCostAdjustments::iddObjectType() {
    return IddObjectType::ComponentCost_Adjustments;
  }

  boost::optional<double> ComponentCostAdjustments::miscellaneousCostperConditionedArea() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->miscellaneousCostperConditionedArea();
  }

  bool ComponentCostAdjustments::setMiscellaneousCostperConditionedArea(double miscellaneousCostperConditionedArea) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setMiscellaneousCostperConditionedArea(miscellaneousCostperConditionedArea);
  }

  void ComponentCostAdjustments::resetMiscellaneousCostperConditionedArea() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetMiscellaneousCostperConditionedArea();
  }

  boost::optional<double> ComponentCostAdjustments::designandEngineeringFees() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->designandEngineeringFees();
  }

  bool ComponentCostAdjustments::setDesignandEngineeringFees(double designandEngineeringFees) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setDesignandEngineeringFees(designandEngineeringFees);
  }

  void ComponentCostAdjustments::resetDesignandEngineeringFees() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetDesignandEngineeringFees();
  }

  boost::optional<double> ComponentCostAdjustments::contractorFee() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->contractorFee();
  }

  bool ComponentCostAdjustments::setContractorFee(double contractorFee) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setContractorFee(contractorFee);
  }

  void ComponentCostAdjustments::resetContractorFee() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetContractorFee();
  }

  boost::optional<double> ComponentCostAdjustments::contingency() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->contingency();
  }

  bool ComponentCostAdjustments::setContingency(double contingency) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setContingency(contingency);
  }

  void ComponentCostAdjustments::resetContingency() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetContingency();
  }

  boost::optional<double> ComponentCostAdjustments::permitsBondingandInsurance() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->permitsBondingandInsurance();
  }

  bool ComponentCostAdjustments::setPermitsBondingandInsurance(double permitsBondingandInsurance) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setPermitsBondingandInsurance(permitsBondingandInsurance);
  }

  void ComponentCostAdjustments::resetPermitsBondingandInsurance() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetPermitsBondingandInsurance();
  }

  boost::optional<double> ComponentCostAdjustments::commissioningFee() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->commissioningFee();
  }

  bool ComponentCostAdjustments::setCommissioningFee(double commissioningFee) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setCommissioningFee(commissioningFee);
  }

  void ComponentCostAdjustments::resetCommissioningFee() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetCommissioningFee();
  }

  boost::optional<double> ComponentCostAdjustments::regionalAdjustmentFactor() const {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->regionalAdjustmentFactor();
  }

  bool ComponentCostAdjustments::setRegionalAdjustmentFactor(double regionalAdjustmentFactor) {
    return getImpl<detail::ComponentCostAdjustments_Impl>()->setRegionalAdjustmentFactor(regionalAdjustmentFactor);
  }

  void ComponentCostAdjustments::resetRegionalAdjustmentFactor() {
    getImpl<detail::ComponentCostAdjustments_Impl>()->resetRegionalAdjustmentFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ComponentCostAdjustments_Impl::miscellaneousCostperConditionedArea() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea, true);
    }

    bool ComponentCostAdjustments_Impl::setMiscellaneousCostperConditionedArea(double miscellaneousCostperConditionedArea) {
      const bool result =
        setDouble(openstudio::ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea, miscellaneousCostperConditionedArea);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetMiscellaneousCostperConditionedArea() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::designandEngineeringFees() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::DesignandEngineeringFees, true);
    }

    bool ComponentCostAdjustments_Impl::setDesignandEngineeringFees(double designandEngineeringFees) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::DesignandEngineeringFees, designandEngineeringFees);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetDesignandEngineeringFees() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::DesignandEngineeringFees, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::contractorFee() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::ContractorFee, true);
    }

    bool ComponentCostAdjustments_Impl::setContractorFee(double contractorFee) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::ContractorFee, contractorFee);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetContractorFee() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::ContractorFee, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::contingency() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::Contingency, true);
    }

    bool ComponentCostAdjustments_Impl::setContingency(double contingency) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::Contingency, contingency);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetContingency() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::Contingency, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::permitsBondingandInsurance() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::PermitsBondingandInsurance, true);
    }

    bool ComponentCostAdjustments_Impl::setPermitsBondingandInsurance(double permitsBondingandInsurance) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::PermitsBondingandInsurance, permitsBondingandInsurance);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetPermitsBondingandInsurance() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::PermitsBondingandInsurance, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::commissioningFee() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::CommissioningFee, true);
    }

    bool ComponentCostAdjustments_Impl::setCommissioningFee(double commissioningFee) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::CommissioningFee, commissioningFee);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetCommissioningFee() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::CommissioningFee, ""));
    }

    boost::optional<double> ComponentCostAdjustments_Impl::regionalAdjustmentFactor() const {
      return getDouble(openstudio::ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor, true);
    }

    bool ComponentCostAdjustments_Impl::setRegionalAdjustmentFactor(double regionalAdjustmentFactor) {
      const bool result = setDouble(openstudio::ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor, regionalAdjustmentFactor);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostAdjustments_Impl::resetRegionalAdjustmentFactor() {
      OS_ASSERT(setString(openstudio::ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
