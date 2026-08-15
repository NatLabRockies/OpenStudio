/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class DesignSpecificationOutdoorAir_Impl;
  }

  class EPMODEL_API DesignSpecificationOutdoorAir : public ModelObject
  {
   public:
    explicit DesignSpecificationOutdoorAir(const Model& model);

    virtual ~DesignSpecificationOutdoorAir() override = default;
    DesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& other) = default;
    DesignSpecificationOutdoorAir(DesignSpecificationOutdoorAir&& other) = default;
    DesignSpecificationOutdoorAir& operator=(const DesignSpecificationOutdoorAir&) = default;
    DesignSpecificationOutdoorAir& operator=(DesignSpecificationOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The persisted scalar fields and optional outdoor-air flow-rate fraction schedule relationship are exposed, while
    //   broader canonical default/reset conveniences remain incomplete.
    // - Canonical Counterpart: openstudio::model::DesignSpecificationOutdoorAir.
    // - Implemented Parity: Outdoor-air method and flow inputs map directly to EnergyPlus, and the canonical optional schedule relationship supports
    //   validated assignment, reset, save/load, and post-load mutation.
    // - Documented Delta: EnergyPlus also has a Proportional Control Minimum Outdoor Air Flow Rate Schedule Name field, but the canonical Model wrapper
    //   has no corresponding public API, so epmodel does not expose it.
    // - Field/Storage Mapping: `outdoorAirFlowRateFractionSchedule()` maps to EnergyPlus `Outdoor Air Schedule Name`; the referenced schedule remains
    //   an independent model resource.
    // - Canonicalization: A unique persisted schedule name is reattached during load repair; blank, missing, or ambiguous names are not invented or
    //   guessed. Ordinary getters remain observational and assume canonical resolved relationships.
    // - Evidence: `src/model/DesignSpecificationOutdoorAir.hpp`, `src/model/ScheduleTypeRegistry.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/DesignSpecificationOutdoorAir_GTest.cpp`.
    // - Remaining Parity Work: Add the remaining canonical scalar default/reset helpers when that broader API surface is needed.

    std::string outdoorAirMethod() const;
    bool setOutdoorAirMethod(const std::string& value);

    double outdoorAirFlowperPerson() const;
    bool setOutdoorAirFlowperPerson(double value);

    double outdoorAirFlowperFloorArea() const;
    bool setOutdoorAirFlowperFloorArea(double value);

    double outdoorAirFlowRate() const;
    bool setOutdoorAirFlowRate(double value);

    double outdoorAirFlowAirChangesperHour() const;
    bool setOutdoorAirFlowAirChangesperHour(double value);

    boost::optional<Schedule> outdoorAirFlowRateFractionSchedule() const;
    bool setOutdoorAirFlowRateFractionSchedule(Schedule& schedule);
    void resetOutdoorAirFlowRateFractionSchedule();

   protected:
    using ImplType = detail::DesignSpecificationOutdoorAir_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit DesignSpecificationOutdoorAir(std::shared_ptr<detail::DesignSpecificationOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
