/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_HPP
#define EPMODEL_PIPEINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Construction;
  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class PipeIndoor_Impl;
  }

  class EPMODEL_API PipeIndoor : public StraightComponent
  {
   public:
    explicit PipeIndoor(const Model& model);

    virtual ~PipeIndoor() override = default;
    PipeIndoor(const PipeIndoor& other) = default;
    PipeIndoor(PipeIndoor&& other) = default;
    PipeIndoor& operator=(const PipeIndoor&) = default;
    PipeIndoor& operator=(PipeIndoor&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> environmentTypeValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical PipeIndoor scalar surface, object relationships, and plant-loop-only topology behavior are present.
    // - Canonical Counterpart: openstudio::model::PipeIndoor.
    // - Implemented Parity: `construction`, `environmentType`, `ambientTemperatureZone`, `ambientTemperatureSchedule`,
    //   `ambientAirVelocitySchedule`, `pipeInsideDiameter`, `pipeLength`, and plant-loop-only `addToNode(...)` preserve the canonical wrapper behavior
    //   that maps cleanly to `Pipe:Indoor`.
    // - Documented Delta: epmodel still relies on inherited HVACComponent/StraightComponent topology helpers instead of the broader canonical
    //   component/fuel-type public surface, which remains a shared epmodel base-class gap.
    // - Field/Storage Mapping: The wrapper maps directly to EnergyPlus `Pipe:Indoor` construction, ambient zone/schedule, node-name, and scalar fields.
    // - Evidence: `src/model/PipeIndoor.hpp`, `src/model/PipeIndoor.cpp`, `src/model/test/PipeIndoor_GTest.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslatePipeIndoor.cpp` define and exercise the canonical behavior this wrapper preserves.
    // - Remaining Parity Work: Close the remaining shared HVACComponent base-surface gaps so PipeIndoor can inherit the missing canonical
    //   component/fuel-type conveniences without adding type-local divergence.

    /** @name Topology */
    //@{
    bool addToNode(Node& node);
    //@}

    /** @name Construction */
    //@{
    boost::optional<Construction> construction() const;
    bool setConstruction(const Construction& construction);
    void resetConstruction();
    //@}

    /** @name Environment Type */
    //@{
    std::string environmentType() const;
    bool setEnvironmentType(const std::string& environmentType);
    //@}

    /** @name Ambient Temperature Zone */
    //@{
    boost::optional<ThermalZone> ambientTemperatureZone() const;
    bool setAmbientTemperatureZone(const ThermalZone& thermalZone);
    void resetAmbientTemperatureZone();
    //@}

    /** @name Ambient Temperature Schedule */
    //@{
    boost::optional<Schedule> ambientTemperatureSchedule() const;
    bool setAmbientTemperatureSchedule(Schedule& schedule);
    void resetAmbientTemperatureSchedule();
    //@}

    /** @name Ambient Air Velocity Schedule */
    //@{
    boost::optional<Schedule> ambientAirVelocitySchedule() const;
    bool setAmbientAirVelocitySchedule(Schedule& schedule);
    void resetAmbientAirVelocitySchedule();
    //@}

    /** @name Pipe Inside Diameter */
    //@{
    double pipeInsideDiameter() const;
    bool setPipeInsideDiameter(double pipeInsideDiameter);
    //@}

    /** @name Pipe Length */
    //@{
    double pipeLength() const;
    bool setPipeLength(double pipeLength);
    //@}

   protected:
    using ImplType = detail::PipeIndoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
