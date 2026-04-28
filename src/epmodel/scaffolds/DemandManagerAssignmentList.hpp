/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERASSIGNMENTLIST_HPP
#define EPMODEL_DEMANDMANAGERASSIGNMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DemandManagerAssignmentList_Impl;
  }

  class EPMODEL_API DemandManagerAssignmentList : public ModelObject
  {
   public:
    explicit DemandManagerAssignmentList(const Model& model);

    virtual ~DemandManagerAssignmentList() override = default;
    DemandManagerAssignmentList(const DemandManagerAssignmentList& other) = default;
    DemandManagerAssignmentList(DemandManagerAssignmentList&& other) = default;
    DemandManagerAssignmentList& operator=(const DemandManagerAssignmentList&) = default;
    DemandManagerAssignmentList& operator=(DemandManagerAssignmentList&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> demandManagerPriorityValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Scalar APIs map directly to DemandManagerAssignmentList scalar fields.
    // - Field Mapping: Demand Limit Schedule Name, Billing/Peak Period Schedule Name, and extensible DemandManager
    //   object/name pairs remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    /** @name Meter Name */
    //@{
    std::string meterName() const;
    bool setMeterName(const std::string& meterName);
    //@}

    /** @name Demand Limit Safety Fraction */
    //@{
    double demandLimitSafetyFraction() const;
    bool setDemandLimitSafetyFraction(double demandLimitSafetyFraction);
    //@}

    /** @name Demand Window Length */
    //@{
    int demandWindowLength() const;
    bool setDemandWindowLength(int demandWindowLength);
    //@}

    /** @name Demand Manager Priority */
    //@{
    std::string demandManagerPriority() const;
    bool setDemandManagerPriority(const std::string& demandManagerPriority);
    //@}

   protected:
    using ImplType = detail::DemandManagerAssignmentList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DemandManagerAssignmentList(std::shared_ptr<detail::DemandManagerAssignmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
