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

  /**
   * \brief Constant-volume four-pipe beam terminal with separate hot- and chilled-water coil relationships.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumefourpipebeam,AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam}.
   *
   * \par Important behavior
   * The terminal maintains primary-air, zone, and two plant branches. `addToNode` registers the terminal on the
   * resolved zone equipment list; removal prepares both coil branches and deletes owned coils only after teardown
   * succeeds.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeBeam`. Availability schedules, typed
   * coils, primary-air nodes, loop/node conveniences, and beam sizing fields are represented. The epmodel coil wrappers
   * are narrow plant-compatible handles for connectivity cleanup.
   *
   * \par Known limitations
   * OS-prefixed child persistence, ambiguous projected Branch identity, two-coil same-PlantLoop batch removal, deep
   * cloning, and family-specific autosized-result queries are not fully supported.
   */
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
