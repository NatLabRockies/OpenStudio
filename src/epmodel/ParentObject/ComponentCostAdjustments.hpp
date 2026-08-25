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

/** \brief Defines component cost adjustment factors used by life-cycle cost calculations.
 *
 * \par EnergyPlus object
 * \epobject{cost-estimating.html#componentcostadjustments,ComponentCost:Adjustments}
 *
 * \par Important behavior
 * The cost-adjustment percentages and regional adjustment factor are persisted as scalar fields.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ComponentCostAdjustments</code>.
 * <b>Renamed:</b> EPModel uses <code>designandEngineeringFees()</code>, <code>miscellaneousCostperConditionedArea()</code>, and <code>permitsBondingandInsurance()</code>; Model capitalizes the corresponding words as <code>designAndEngineeringFees()</code>, <code>miscellaneousCostPerConditionedArea()</code>, and <code>permitsBondingAndInsurance()</code>.
 *
 * \par Known limitations
 * This object supplies cost inputs; it does not calculate or own life-cycle cost results.
 */
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
