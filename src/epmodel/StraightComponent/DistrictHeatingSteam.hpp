/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGSTEAM_HPP
#define EPMODEL_DISTRICTHEATINGSTEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictHeatingSteam_Impl;
  }

  class EPMODEL_API DistrictHeatingSteam : public StraightComponent
  {
   public:
    explicit DistrictHeatingSteam(const Model& model);

    virtual ~DistrictHeatingSteam() override = default;
    DistrictHeatingSteam(const DistrictHeatingSteam& other) = default;
    DistrictHeatingSteam(DistrictHeatingSteam&& other) = default;
    DistrictHeatingSteam& operator=(const DistrictHeatingSteam&) = default;
    DistrictHeatingSteam& operator=(DistrictHeatingSteam&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical district-heating-steam wrapper surface, constructor default schedule seeding, and plant-supply
    //   placement contract are present, while autosized-result lookup remains a documented gap.
    // - Canonical Counterpart: openstudio::model::DistrictHeatingSteam.
    // - Implemented Parity: The nominal-capacity accessors, capacity-fraction schedule getter/setter, constructor default schedule seeding, and
    //   plant-supply-only `addToNode(...)` behavior match the canonical wrapper surface.
    // - Documented Delta: Resolved autosized nominal-capacity lookup remains intentionally unavailable because epmodel does not yet expose SQL-backed sizing
    //   results.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `DistrictHeating:Steam` nominal-capacity and capacity-fraction-schedule fields
    //   used by the forward translator.
    // - Evidence: `src/model/DistrictHeatingSteam.hpp`, `src/model/DistrictHeatingSteam.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingSteam.cpp`.
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
    using ImplType = detail::DistrictHeatingSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingSteam(std::shared_ptr<detail::DistrictHeatingSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
