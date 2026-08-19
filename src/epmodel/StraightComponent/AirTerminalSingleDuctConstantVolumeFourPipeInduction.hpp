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

  /**
   * \brief Constant-volume four-pipe induction terminal with primary and induced-air paths and optional water coils.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumefourpipeinduction,AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction}.
   *
   * \par Important behavior
   * `addToNode` is transactional on the supported zone branch: it creates the terminal-owned inlet/mixer path and
   * projects the induced-air path through the heating and optional cooling coils. Removal clears zone, ADU, node,
   * mixer, and plant references together.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeInduction`. Availability, typed coil
   * relationships, induced-air access, scalar fields, and zone-branch insertion are represented. The epmodel no-arg
   * constructor and raw optional cooling-coil target are additional assembly conveniences.
   *
   * \par Known limitations
   * Autosized-result queries and broader local-topology conveniences are not exposed. Removal currently rejects the
   * uncommon case where both contained coils share one PlantLoop.
   */
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
    bool setCoolingCoil(const HVACComponent& coolingCoil);
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
