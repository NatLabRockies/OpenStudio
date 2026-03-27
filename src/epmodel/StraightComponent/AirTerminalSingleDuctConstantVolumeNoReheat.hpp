/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeNoReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model);

    virtual ~AirTerminalSingleDuctConstantVolumeNoReheat() override = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(const AirTerminalSingleDuctConstantVolumeNoReheat& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(AirTerminalSingleDuctConstantVolumeNoReheat&& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(const AirTerminalSingleDuctConstantVolumeNoReheat&) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(AirTerminalSingleDuctConstantVolumeNoReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The constant-volume no-reheat scalar surface is aligned, while schedule and node-link helpers remain intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeNoReheat.
    // - Implemented Parity: `maximumAirFlowRate` preserves the canonical scalar contract and `addToNode` retains the expected topology-mutation behavior.
    // - Documented Delta: Availability schedule, inlet node, and outlet node accessors are not exposed as public methods yet.
    // - Field/Storage Mapping: The preserved scalar maps directly to EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:NoReheat` fields, while the translator wires the node links separately.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeNoReheat.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeNoReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule and node-link helpers when relationship parity expands.
    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl;

    friend class openstudio::epmodel::Model;

    explicit AirTerminalSingleDuctConstantVolumeNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
