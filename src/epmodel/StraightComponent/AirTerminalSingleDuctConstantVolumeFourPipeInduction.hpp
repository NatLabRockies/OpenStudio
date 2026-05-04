/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeInduction : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model);
    AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model, HVACComponent& heatingCoil);

    virtual ~AirTerminalSingleDuctConstantVolumeFourPipeInduction() override = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction(const AirTerminalSingleDuctConstantVolumeFourPipeInduction& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction(AirTerminalSingleDuctConstantVolumeFourPipeInduction&& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction& operator=(const AirTerminalSingleDuctConstantVolumeFourPipeInduction&) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction& operator=(AirTerminalSingleDuctConstantVolumeFourPipeInduction&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical availability schedule, coil relationships, induced-air node, and zone-branch insertion path are
    //   surfaced, while the broader canonical autosized-result helpers and more specialized local-topology conveniences remain intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeInduction.
    // - Implemented Parity: `availabilitySchedule`, `setHeatingCoil`, `setCoolingCoil`, `inducedAirInletNode`, `inducedAirInletPort`,
    //   guarded zone-branch `addToNode`, `removeFromLoop`, child-coil ownership, the scalar accessors, and the explicit heating-coil constructor
    //   preserve the relationship surface that is practical on the current epmodel zone-branch path.
    // - Documented Delta: The optional epmodel-only no-arg constructor seeds the current defaulted flow parameters as a convenience while leaving
    //   availability unset; canonical model exposes only the heating-coil constructor. The optional cooling coil is exposed as a raw epmodel
    //   `HVACComponent` target with the same-model validation and reset behavior preserved, and the wrapper still omits the canonical
    //   autosized-result helpers and broader topology conveniences such as the model-side exhaust-node convenience surface.
    // - Field/Storage Mapping: The availability schedule, heating/cooling coil targets, induced-air inlet node, preserved scalars, and inherited
    //   straight-component inlet/outlet node fields all store directly on the EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction`
    //   object. `addToNode` only inserts on the current epmodel zone-branch path when the target node is the matching same-model
    //   ZoneSplitter/ZoneMixer branch node for an AirLoopHVAC and the terminal is not already connected; on success it creates the transient
    //   branch inlet node and updates the owning thermal zone's exhaust-node connection. Removal clears zone equipment registration, terminal
    //   node fields, `ZoneHVAC:AirDistributionUnit` references, and child coil plant demand branches; it also clears the induced-air linkage
    //   when that stored exhaust node belongs exclusively to the terminal being removed.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeFourPipeInduction.cpp`,
    //   and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeFourPipeInduction_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted autosized-result helpers and any broader canonical topology conveniences if shared infrastructure later
    //   makes them practical.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<double> maximumTotalAirFlowRate() const;
    bool setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate);
    bool isMaximumTotalAirFlowRateAutosized() const;
    void autosizeMaximumTotalAirFlowRate();

    double inductionRatio() const;
    bool setInductionRatio(double inductionRatio);
    bool isInductionRatioDefaulted() const;
    void resetInductionRatio();

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    boost::optional<double> maximumHotWaterFlowRate() const;
    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    bool isMaximumHotWaterFlowRateAutosized() const;
    void resetMaximumHotWaterFlowRate();
    void autosizeMaximumHotWaterFlowRate();

    double minimumHotWaterFlowRate() const;
    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    bool isMinimumHotWaterFlowRateDefaulted() const;
    void resetMinimumHotWaterFlowRate();

    double heatingConvergenceTolerance() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    bool isHeatingConvergenceToleranceDefaulted() const;
    void resetHeatingConvergenceTolerance();

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(const boost::optional<HVACComponent>& coolingCoil);
    void resetCoolingCoil();

    boost::optional<double> maximumColdWaterFlowRate() const;
    bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
    bool isMaximumColdWaterFlowRateAutosized() const;
    void resetMaximumColdWaterFlowRate();
    void autosizeMaximumColdWaterFlowRate();

    double minimumColdWaterFlowRate() const;
    bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
    bool isMinimumColdWaterFlowRateDefaulted() const;
    void resetMinimumColdWaterFlowRate();

    double coolingConvergenceTolerance() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    bool isCoolingConvergenceToleranceDefaulted() const;
    void resetCoolingConvergenceTolerance();

    boost::optional<Node> inducedAirInletNode() const;
    unsigned inducedAirInletPort() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeFourPipeInduction(
      std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
