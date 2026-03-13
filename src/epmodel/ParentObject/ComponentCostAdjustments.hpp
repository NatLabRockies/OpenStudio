/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTADJUSTMENTS_HPP
#define EPMODEL_COMPONENTCOSTADJUSTMENTS_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ComponentCostAdjustments_Impl;
  }

  class EPMODEL_API ComponentCostAdjustments : public ParentObject
  {
   public:
    explicit ComponentCostAdjustments(const Model& model);

    virtual ~ComponentCostAdjustments() override = default;
    ComponentCostAdjustments(const ComponentCostAdjustments& other) = default;
    ComponentCostAdjustments(ComponentCostAdjustments&& other) = default;
    ComponentCostAdjustments& operator=(const ComponentCostAdjustments&) = default;
    ComponentCostAdjustments& operator=(ComponentCostAdjustments&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus ComponentCost:Adjustments scalar fields.
    // - Field Mapping: Relationship-like fields are not present on this object; scalar-only coverage is complete for this scaffold pass.
    // - TODO(parity): Revisit naming only if a model-counterpart parity target is introduced.

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

   protected:
    using ImplType = detail::ComponentCostAdjustments_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ComponentCostAdjustments(std::shared_ptr<detail::ComponentCostAdjustments_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
