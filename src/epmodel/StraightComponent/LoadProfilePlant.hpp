/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOADPROFILEPLANT_HPP
#define EPMODEL_LOADPROFILEPLANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class LoadProfilePlant_Impl;
  }

  class EPMODEL_API LoadProfilePlant : public StraightComponent
  {
   public:
    explicit LoadProfilePlant(const Model& model);
    explicit LoadProfilePlant(const Model& model, Schedule& loadSchedule, Schedule& flowRateFractionSchedule);

    virtual ~LoadProfilePlant() override = default;
    LoadProfilePlant(const LoadProfilePlant& other) = default;
    LoadProfilePlant(LoadProfilePlant&& other) = default;
    LoadProfilePlant& operator=(const LoadProfilePlant&) = default;
    LoadProfilePlant& operator=(LoadProfilePlant&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> plantLoopFluidTypeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical load-profile-plant wrapper surface, constructor seeding, required schedule relationships, and
    //   plant-demand placement contract are present.
    // - Canonical Counterpart: openstudio::model::LoadProfilePlant.
    // - Implemented Parity: `loadSchedule()`, `setLoadSchedule(...)`, `flowRateFractionSchedule()`, `setFlowRateFractionSchedule(...)`,
    //   both public constructors, and demand-side-only `addToNode(...)` match the canonical wrapper surface alongside the scalar accessors.
    // - Documented Delta: The default seeded load schedule uses `ScheduleCompact` because epmodel does not yet expose `ScheduleRuleset`.
    // - Documented Delta: epmodel currently retains the extra default/reset helpers inherited from the underlying EnergyPlus field semantics:
    //   `plantLoopFluidTypeValues()`, `isPlantLoopFluidTypeDefaulted()`, `resetPlantLoopFluidType()`, `isDegreeofSubCoolingDefaulted()`,
    //   `resetDegreeofSubCooling()`, `isDegreeofLoopSubCoolingDefaulted()`, and `resetDegreeofLoopSubCooling()`.
    // - Field/Storage Mapping: The wrapper maps directly to `LoadProfile:Plant` node, schedule, flow, fluid-type, and subcooling fields used by the
    //   forward translator.
    // - Evidence: `src/model/LoadProfilePlant.hpp`, `src/model/LoadProfilePlant.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateLoadProfilePlant.cpp`.
    // - Remaining Parity Work: Replace the default seeded `ScheduleCompact` with the canonical `ScheduleRuleset` once epmodel exposes that schedule family,
    //   then reassess whether the extra epmodel-only default/reset helpers should remain public.
    Schedule loadSchedule() const;
    bool setLoadSchedule(Schedule& schedule);

    double peakFlowRate() const;
    bool setPeakFlowRate(double peakFlowRate);

    Schedule flowRateFractionSchedule() const;
    bool setFlowRateFractionSchedule(Schedule& schedule);

    std::string plantLoopFluidType() const;
    bool setPlantLoopFluidType(const std::string& plantLoopFluidType);
    bool isPlantLoopFluidTypeDefaulted() const;
    void resetPlantLoopFluidType();

    double degreeofSubCooling() const;
    bool setDegreeofSubCooling(double degreeofSubCooling);
    bool isDegreeofSubCoolingDefaulted() const;
    void resetDegreeofSubCooling();

    double degreeofLoopSubCooling() const;
    bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
    bool isDegreeofLoopSubCoolingDefaulted() const;
    void resetDegreeofLoopSubCooling();

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::LoadProfilePlant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LoadProfilePlant(std::shared_ptr<detail::LoadProfilePlant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
