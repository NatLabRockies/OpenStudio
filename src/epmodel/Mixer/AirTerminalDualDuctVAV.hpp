/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAV_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAV_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class AirTerminalDualDuctVAV_Impl;
}

class EPMODEL_API AirTerminalDualDuctVAV : public Mixer
{
 public:
  explicit AirTerminalDualDuctVAV(const Model& model);

  virtual ~AirTerminalDualDuctVAV() override = default;
  AirTerminalDualDuctVAV(const AirTerminalDualDuctVAV& other) = default;
  AirTerminalDualDuctVAV(AirTerminalDualDuctVAV&& other) = default;
  AirTerminalDualDuctVAV& operator=(const AirTerminalDualDuctVAV&) = default;
  AirTerminalDualDuctVAV& operator=(AirTerminalDualDuctVAV&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Connectivity parity for the tested dual-duct add/remove path and inlet-node wiring.
  // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctVAV.
  // - Implemented Connectivity Surface: constructor defaults used by the dual-duct path, `hotAirInletNode`, `coldAirInletNode`, and the shared `addToNode`/`remove` topology behavior are implemented here.
  // - Documented Delta: epmodel still does not expose canonical `availabilitySchedule()`, DSOA, minimum-air-flow-turndown, or autosized-value convenience wrappers even though the underlying IDD relationship fields remain stored.
  // - Field/Storage Mapping: `AvailabilityScheduleName`, `DesignSpecificationOutdoorAirObjectName`, and `MinimumAirFlowTurndownScheduleName` remain underlying relationship fields; Air Outlet/Hot Air Inlet/Cold Air Inlet node fields are surfaced through node accessors and shared AirLoopHVAC topology helpers.
  // - Evidence: `src/model/AirTerminalDualDuctVAV.cpp` and `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAV.cpp` document the canonical field mapping; `src/model/test/AirTerminalDualDuctVAV_GTest.cpp` and `src/epmodel/test/AirTerminalDualDuctVAV_GTest.cpp` cover the tested insertion, removal, reuse, and cleanup behavior.
  // - Remaining Parity Work: Reintroduce the omitted schedule, DSOA, and turndown wrappers only if broader model API parity is needed outside this connectivity campaign.
  boost::optional<double> maximumDamperAirFlowRate() const;
  bool isMaximumDamperAirFlowRateAutosized() const;
  bool setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate);
  void autosizeMaximumDamperAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);
  boost::optional<Node> hotAirInletNode() const;
  boost::optional<Node> coldAirInletNode() const;
  bool addToNode(Node& node);

 protected:
  using ImplType = detail::AirTerminalDualDuctVAV_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalDualDuctVAV(std::shared_ptr<detail::AirTerminalDualDuctVAV_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
