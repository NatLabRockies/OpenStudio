/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class HVACComponent;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeReheat_Impl;
  }

  /**
   * \brief Constant-volume single-duct terminal with a typed reheat coil.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumereheat,AirTerminal:SingleDuct:ConstantVolume:Reheat}.
   *
   * \par Important behavior
   * `addToNode` connects the terminal to the supported AirLoopHVAC zone branch, projects the terminal path through
   * the reheat coil, updates a linked AirDistributionUnit, and registers zone equipment. `removeFromLoop` reverses
   * those references and removes a plant-connected reheat branch.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctConstantVolumeReheat`. The schedule, typed reheat-coil,
   * scalar, and supported branch insertion/removal APIs are represented. The epmodel default constructor is retained
   * for incremental assembly.
   *
   * \par Known limitations
   * The supported insertion path is narrower than the Model API, and family-specific autosized-result queries are
   * not exposed. Child replacement requires a supported same-model, unconnected EnergyPlus coil.
   */
  class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeReheat(const Model& model);
    AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule, HVACComponent& reheatCoil);

    virtual ~AirTerminalSingleDuctConstantVolumeReheat() override = default;
    AirTerminalSingleDuctConstantVolumeReheat(const AirTerminalSingleDuctConstantVolumeReheat& other) = default;
    AirTerminalSingleDuctConstantVolumeReheat(AirTerminalSingleDuctConstantVolumeReheat&& other) = default;
    AirTerminalSingleDuctConstantVolumeReheat& operator=(const AirTerminalSingleDuctConstantVolumeReheat&) = default;
    AirTerminalSingleDuctConstantVolumeReheat& operator=(AirTerminalSingleDuctConstantVolumeReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent reheatCoil() const;
    bool setReheatCoil(const HVACComponent& coil);
    void resetReheatCoil();

    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void resetMaximumAirFlowRate();
    void autosizeMaximumAirFlowRate();

    boost::optional<double> maximumHotWaterorSteamFlowRate() const;
    bool isMaximumHotWaterorSteamFlowRateAutosized() const;
    bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
    void resetMaximumHotWaterorSteamFlowRate();
    void autosizeMaximumHotWaterorSteamFlowRate();

    double minimumHotWaterorSteamFlowRate() const;
    bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
    bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
    void resetMinimumHotWaterorSteamFlowRate();

    double convergenceTolerance() const;
    bool isConvergenceToleranceDefaulted() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    void resetConvergenceTolerance();

    double maximumReheatAirTemperature() const;
    bool isMaximumReheatAirTemperatureDefaulted() const;
    bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
    void resetMaximumReheatAirTemperature();

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
