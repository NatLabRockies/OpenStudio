/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class AirLoopHVACOutdoorAirSystem;
  class Schedule;
  class AirLoopHVAC;

  namespace detail {
    class AirLoopHVACDedicatedOutdoorAirSystem_Impl;
  }

  class EPMODEL_API AirLoopHVACDedicatedOutdoorAirSystem : public ModelObject
  {
   public:
    explicit AirLoopHVACDedicatedOutdoorAirSystem(const Model& model);
    explicit AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& oaSystem);

    virtual ~AirLoopHVACDedicatedOutdoorAirSystem() override = default;
    AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACDedicatedOutdoorAirSystem& other) = default;
    AirLoopHVACDedicatedOutdoorAirSystem(AirLoopHVACDedicatedOutdoorAirSystem&& other) = default;
    AirLoopHVACDedicatedOutdoorAirSystem& operator=(const AirLoopHVACDedicatedOutdoorAirSystem&) = default;
    AirLoopHVACDedicatedOutdoorAirSystem& operator=(AirLoopHVACDedicatedOutdoorAirSystem&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. Scalar state, ordered AirLoopHVAC membership, and straight conditioned-equipment projection are present; the wider dedicated-OA equipment lifecycle remains bounded.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACDedicatedOutdoorAirSystem.
    // - Implemented Parity: Construction from an outdoor-air system, availability scheduling, ordered membership, reverse lookup, one-based `airLoopIndex`, idempotent same-owner addition, membership removal, served-loop deletion, owned mixer/splitter cleanup, and fan plus plant-connected water-coil projection preserve the canonical public transitions used by the repository DOAS workflow.
    // - Documented Delta: EPModel additionally exposes a Model constructor for direct EnergyPlus object creation. It rejects an AirLoopHVAC or outdoor-air system already owned by another DOAS without mutation; canonical Model currently reports success for the former and removes the competing DOAS for the latter. EPModel also requires a served AirLoopHVAC to have its own outdoor-air system because direct EnergyPlus DOAS mixer/splitter rows cannot otherwise be formed. Removing the DOAS currently retains its outdoor-air system while removing the EnergyPlus-only mixer and splitter; canonical Model removes the outdoor-air system too.
    // - Field/Storage Mapping: Preheat/precool values map directly. Each AirLoopHVAC membership is stored in three aligned EnergyPlus extensible rows: the DOAS AirLoopHVAC name, the common mixer relief inlet, and the common splitter outdoor-air outlet. The associated outdoor-air system uses a transient conceptual controller list for Controller:OutdoorAir and a distinct persisted list for Controller:WaterCoil rows. The EnergyPlus IDD's missing object-list types for the mixer and splitter links are corrected in `resources/energyplus/ProposedEnergy+.idd` so these relationships remain tracked pointers.
    // - Evidence: `src/model/AirLoopHVACDedicatedOutdoorAirSystem.*`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACDedicatedOutdoorAirSystem.cpp`, `../OpenStudio-resources/model/simulationtests/doas.rb`, and `src/epmodel/test/AirLoopHVACDedicatedOutdoorAirSystem_GTest.cpp`.
    // - Remaining Parity Work: Add two-stream heat recovery, outdoor-air-system removal, and clone behavior before claiming the wider class lifecycle.
    AirLoopHVACOutdoorAirSystem airLoopHVACOutdoorAirSystem() const;
    Schedule availabilitySchedule() const;

    double preheatDesignTemperature() const;
    bool setPreheatDesignTemperature(double preheatDesignTemperature);

    double preheatDesignHumidityRatio() const;
    bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

    double precoolDesignTemperature() const;
    bool setPrecoolDesignTemperature(double precoolDesignTemperature);

    double precoolDesignHumidityRatio() const;
    bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

    unsigned int numberofAirLoops() const;
    std::vector<AirLoopHVAC> airLoops() const;
    boost::optional<unsigned> airLoopIndex(const AirLoopHVAC& airLoopHVAC) const;

    bool setAirLoopHVACOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& airLoopHVACOutdoorAirSystem);
    bool setAvailabilitySchedule(Schedule& schedule);
    bool addAirLoop(const AirLoopHVAC& airLoopHVAC);
    bool removeAirLoop(const AirLoopHVAC& airLoopHVAC);
    bool removeAirLoop(unsigned groupIndex);
    void removeAllAirLoops();
    bool addAirLoops(const std::vector<AirLoopHVAC>& airLoopHVACs);

   protected:
    using ImplType = detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACDedicatedOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
