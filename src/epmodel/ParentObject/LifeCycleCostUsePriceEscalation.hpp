/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_HPP
#define EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class LifeCycleCostUsePriceEscalation_Impl;
  }

/** \brief Defines resource-price escalation factors for life-cycle cost analysis.
 *
 * \par EnergyPlus object
 * \epobject{lifecyclecost-usepriceescalation.html#lifecyclecostusepriceescalation,LifeCycleCost:UsePriceEscalation}
 *
 * \par Important behavior
 * The resource, escalation start date, and year-by-year escalation values are stored in the object's extensible fields.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::LifeCycleCostUsePriceEscalation</code>.
 * <b>Not yet available:</b> Model's <code>numYears()</code>,
 * <code>yearEscalation()</code>, and <code>setYearEscalation()</code> methods
 * for the year-by-year escalation extensible rows are not exposed by EPModel.
 *
 * \par Known limitations
 * The escalation object does not own a resource meter or perform the economic
 * calculation; EnergyPlus consumes its stored assumptions during simulation.
 */
  class EPMODEL_API LifeCycleCostUsePriceEscalation : public ParentObject
  {
   public:
    explicit LifeCycleCostUsePriceEscalation(const Model& model);

    virtual ~LifeCycleCostUsePriceEscalation() override = default;
    LifeCycleCostUsePriceEscalation(const LifeCycleCostUsePriceEscalation& other) = default;
    LifeCycleCostUsePriceEscalation(LifeCycleCostUsePriceEscalation&& other) = default;
    LifeCycleCostUsePriceEscalation& operator=(const LifeCycleCostUsePriceEscalation&) = default;
    LifeCycleCostUsePriceEscalation& operator=(LifeCycleCostUsePriceEscalation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> resourceValues();
    static std::vector<std::string> escalationStartMonthValues();


    // Resource value
    std::string resource() const;
    bool setResource(const std::string& resource);

    // Escalation start year
    boost::optional<int> escalationStartYear() const;
    bool setEscalationStartYear(int escalationStartYear);
    void resetEscalationStartYear();

    // Escalation start month
    std::string escalationStartMonth() const;
    bool isEscalationStartMonthDefaulted() const;
    bool setEscalationStartMonth(const std::string& escalationStartMonth);
    void resetEscalationStartMonth();

   protected:
    using ImplType = detail::LifeCycleCostUsePriceEscalation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LifeCycleCostUsePriceEscalation(std::shared_ptr<detail::LifeCycleCostUsePriceEscalation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
