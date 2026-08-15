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
#include <string>
#include <vector>

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

    static std::vector<std::string> outdoorAirMethodValues();

    /** \deprecated */
    static std::vector<std::string> validOutdoorAirMethodValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar/default surface and optional outdoor-air flow-rate fraction schedule relationship are exposed,
    //   while the proportional-control schedule and canonical resource-lifecycle differences remain documented deltas.
    // - Canonical Counterpart: openstudio::model::DesignSpecificationOutdoorAir.
    // - Implemented Parity: Outdoor-air method and flow inputs expose canonical values, default flags, reset behavior, and configured key discovery.
    //   Blank scalar storage remains canonical: getters project `Sum` and 0.0 without eagerly writing those values. The canonical optional schedule
    //   relationship supports validated assignment, reset, save/load, and post-load mutation.
    // - Documented Delta: EnergyPlus also has a Proportional Control Minimum Outdoor Air Flow Rate Schedule Name field, but the canonical Model wrapper
    //   has no corresponding public API, so epmodel does not expose it. This epmodel wrapper remains a `ModelObject` rather than the canonical
    //   `ResourceObject`; broader resource lifecycle parity is not claimed.
    // - Field/Storage Mapping: `outdoorAirFlowRateFractionSchedule()` maps to EnergyPlus `Outdoor Air Schedule Name`; the referenced schedule remains
    //   an independent model resource. Scalar fields map directly to EnergyPlus, but blank A2/N1 project canonical Model defaults (`Sum`/0.0) rather
    //   than the configured EnergyPlus defaults (`Flow/Person`/0.00944).
    // - Canonicalization: Blank scalar storage is preserved. A unique persisted schedule name is reattached during load repair; blank, missing, or
    //   ambiguous names are not invented or guessed. Ordinary getters remain observational and assume canonical resolved relationships.
    // - Evidence: `src/model/DesignSpecificationOutdoorAir.hpp`, `src/model/ScheduleTypeRegistry.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/DesignSpecificationOutdoorAir_GTest.cpp`.
    // - Remaining Parity Work: Revisit the proportional-control schedule and ResourceObject lifecycle only if the canonical API or epmodel ownership
    //   contract expands.

    std::string outdoorAirMethod() const;
    bool isOutdoorAirMethodDefaulted() const;
    bool setOutdoorAirMethod(const std::string& value);
    void resetOutdoorAirMethod();

    double outdoorAirFlowperPerson() const;
    bool isOutdoorAirFlowperPersonDefaulted() const;
    bool setOutdoorAirFlowperPerson(double value);
    void resetOutdoorAirFlowperPerson();

    double outdoorAirFlowperFloorArea() const;
    bool isOutdoorAirFlowperFloorAreaDefaulted() const;
    bool setOutdoorAirFlowperFloorArea(double value);
    void resetOutdoorAirFlowperFloorArea();

    double outdoorAirFlowRate() const;
    bool isOutdoorAirFlowRateDefaulted() const;
    bool setOutdoorAirFlowRate(double value);
    void resetOutdoorAirFlowRate();

    double outdoorAirFlowAirChangesperHour() const;
    bool isOutdoorAirFlowAirChangesperHourDefaulted() const;
    bool setOutdoorAirFlowAirChangesperHour(double value);
    void resetOutdoorAirFlowAirChangesperHour();

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
