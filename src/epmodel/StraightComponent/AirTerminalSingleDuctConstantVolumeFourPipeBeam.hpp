/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class Node;
  class PlantLoop;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeBeam : public StraightComponent
  {
   public:
    AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model);
    AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model, HVACComponent& coolingCoil, HVACComponent& heatingCoil);

    virtual ~AirTerminalSingleDuctConstantVolumeFourPipeBeam() override = default;
    AirTerminalSingleDuctConstantVolumeFourPipeBeam(const AirTerminalSingleDuctConstantVolumeFourPipeBeam& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeBeam(AirTerminalSingleDuctConstantVolumeFourPipeBeam&& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(const AirTerminalSingleDuctConstantVolumeFourPipeBeam&) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(AirTerminalSingleDuctConstantVolumeFourPipeBeam&&) = default;

    static IddObjectType iddObjectType();
    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Near Parity. The scalar surface, typed coil relationships, primary-air nodes, plant-loop conveniences, current zone-branch insertion,
    //   and owner-local child removal are exposed, while deep-clone behavior and the family-specific autosized-result helpers remain omitted.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeBeam.
    // - Implemented Parity: `primaryAirAvailabilitySchedule`, `coolingAvailabilitySchedule`, `heatingAvailabilitySchedule`, `primaryAirInletNode`,
    //   `primaryAirOutletNode`, typed `coolingCoil` / `heatingCoil` getters and setters, chilled- and hot-water loop/node conveniences, `addToNode`,
    //   `designPrimaryAirVolumeFlowRate`, `designChilledWaterVolumeFlowRate`, `designHotWaterVolumeFlowRate`, `zoneTotalBeamLength`, and
    //   `ratedPrimaryAirFlowRateperBeamLength` preserve the canonical field and topology contracts that are practical here.
    // - Documented Delta: Dedicated `CoilCoolingFourPipeBeam` and `CoilHeatingFourPipeBeam` wrappers are intentionally narrow plant-compatible
    //   child-coil handles for connectivity cleanup; broader child coil scalar helpers remain outside this campaign pass.
    // - Field/Storage Mapping: The availability schedules, preserved scalars, child coil relationships, and inherited straight-component inlet/outlet
    //   node fields retain the local epmodel field contract. `addToNode` uses the current epmodel zone-branch path and registers the terminal
    //   on the owning thermal-zone equipment list when one is resolved. Terminal removal deletes its owned cooling and heating coils only after
    //   air- and plant-side topology teardown and successful terminal removal.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`, and the focused epmodel tests.
    // - Remaining Parity Work: Add canonical deep-clone behavior for owned coils and expose the family-specific autosized-result query helpers
    //   once shared clone and sizing-result plumbing exists.
    Schedule primaryAirAvailabilitySchedule() const;
    bool setPrimaryAirAvailabilitySchedule(Schedule& schedule);

    Schedule coolingAvailabilitySchedule() const;
    bool setCoolingAvailabilitySchedule(Schedule& schedule);

    Schedule heatingAvailabilitySchedule() const;
    bool setHeatingAvailabilitySchedule(Schedule& schedule);

    boost::optional<Node> primaryAirInletNode() const;
    boost::optional<Node> primaryAirOutletNode() const;

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    boost::optional<double> designPrimaryAirVolumeFlowRate() const;
    bool isDesignPrimaryAirVolumeFlowRateAutosized() const;
    bool setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate);
    void autosizeDesignPrimaryAirVolumeFlowRate();

    boost::optional<double> designChilledWaterVolumeFlowRate() const;
    bool isDesignChilledWaterVolumeFlowRateAutosized() const;
    bool setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate);
    void autosizeDesignChilledWaterVolumeFlowRate();

    boost::optional<double> designHotWaterVolumeFlowRate() const;
    bool isDesignHotWaterVolumeFlowRateAutosized() const;
    bool setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate);
    void autosizeDesignHotWaterVolumeFlowRate();

    boost::optional<double> zoneTotalBeamLength() const;
    bool isZoneTotalBeamLengthAutosized() const;
    bool setZoneTotalBeamLength(double zoneTotalBeamLength);
    void autosizeZoneTotalBeamLength();

    double ratedPrimaryAirFlowRateperBeamLength() const;
    bool isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const;
    bool setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength);
    void resetRatedPrimaryAirFlowRateperBeamLength();

    boost::optional<PlantLoop> chilledWaterPlantLoop() const;
    boost::optional<Node> chilledWaterInletNode() const;
    boost::optional<Node> chilledWaterOutletNode() const;

    boost::optional<PlantLoop> hotWaterPlantLoop() const;
    boost::optional<Node> hotWaterInletNode() const;
    boost::optional<Node> hotWaterOutletNode() const;

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeFourPipeBeam(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
