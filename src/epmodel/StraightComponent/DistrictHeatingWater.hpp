/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGWATER_HPP
#define EPMODEL_DISTRICTHEATINGWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictHeatingWater_Impl;
  }

  class EPMODEL_API DistrictHeatingWater : public StraightComponent
  {
   public:
    explicit DistrictHeatingWater(const Model& model);

    virtual ~DistrictHeatingWater() override = default;
    DistrictHeatingWater(const DistrictHeatingWater& other) = default;
    DistrictHeatingWater(DistrictHeatingWater&& other) = default;
    DistrictHeatingWater& operator=(const DistrictHeatingWater&) = default;
    DistrictHeatingWater& operator=(DistrictHeatingWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical district-heating-water wrapper surface, constructor default schedule seeding, and plant-supply
    //   placement contract are present, while autosized-result lookup remains a documented gap.
    // - Canonical Counterpart: openstudio::model::DistrictHeatingWater.
    // - Implemented Parity: The nominal-capacity accessors, capacity-fraction schedule getter/setter, constructor default schedule seeding, and
    //   plant-supply-only `addToNode(...)` behavior match the canonical wrapper surface.
    // - Documented Delta: Resolved autosized nominal-capacity lookup remains intentionally unavailable because epmodel does not yet expose SQL-backed sizing
    //   results.
    // - Field/Storage Mapping: `nominalCapacity()`, `isNominalCapacityAutosized()`, `setNominalCapacity(...)`, `autosizeNominalCapacity()`,
    //   `capacityFractionSchedule()`, and `setCapacityFractionSchedule(...)` map directly to the EnergyPlus `DistrictHeating:Water`
    //   nominal-capacity and capacity-fraction-schedule fields used by the forward translator.
    // - Evidence: `src/model/DistrictHeatingWater.hpp`, `src/model/DistrictHeatingWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingWater.cpp`.
    // - Remaining Parity Work: Wire `autosizedNominalCapacity()` to resolved sizing results once epmodel exposes the needed simulation-result query surface.
    boost::optional<double> nominalCapacity() const;
    Schedule capacityFractionSchedule() const;
    bool isNominalCapacityAutosized() const;
    boost::optional<double> autosizedNominalCapacity() const;

    bool setNominalCapacity(double nominalCapacity);
    bool setCapacityFractionSchedule(Schedule& schedule);
    void autosizeNominalCapacity();

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::DistrictHeatingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingWater(std::shared_ptr<detail::DistrictHeatingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
