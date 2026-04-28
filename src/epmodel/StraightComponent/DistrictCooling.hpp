/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTCOOLING_HPP
#define EPMODEL_DISTRICTCOOLING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictCooling_Impl;
  }

  class EPMODEL_API DistrictCooling : public StraightComponent
  {
   public:
    explicit DistrictCooling(const Model& model);

    virtual ~DistrictCooling() override = default;
    DistrictCooling(const DistrictCooling& other) = default;
    DistrictCooling(DistrictCooling&& other) = default;
    DistrictCooling& operator=(const DistrictCooling&) = default;
    DistrictCooling& operator=(DistrictCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical district-cooling wrapper surface, constructor default schedule seeding, and plant-supply placement
    //   contract are present, while autosized-result lookup remains a documented gap.
    // - Canonical Counterpart: openstudio::model::DistrictCooling.
    // - Implemented Parity: The nominal-capacity accessors, capacity-fraction schedule getter/setter, constructor default schedule seeding, and
    //   plant-supply-only `addToNode(...)` behavior match the canonical wrapper surface.
    // - Documented Delta: Resolved autosized nominal-capacity lookup remains intentionally unavailable because epmodel does not yet expose SQL-backed sizing
    //   results.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `DistrictCooling` nominal-capacity and capacity-fraction-schedule fields used by the
    //   forward translator.
    // - Evidence: `src/model/DistrictCooling.hpp`, `src/model/DistrictCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictCooling.cpp`.
    // - Remaining Parity Work: Wire `autosizedNominalCapacity()` to resolved sizing results once epmodel exposes the needed simulation-result query surface.
    boost::optional<double> nominalCapacity() const;
    Schedule capacityFractionSchedule() const;

    bool setNominalCapacity(double nominalCapacity);
    bool setCapacityFractionSchedule(Schedule& schedule);
    void autosizeNominalCapacity();
    bool isNominalCapacityAutosized() const;

    boost::optional<double> autosizedNominalCapacity() const;

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::DistrictCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictCooling(std::shared_ptr<detail::DistrictCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
