/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAV_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAV_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalDualDuctVAV_Impl;
}

class EPMODEL_API AirTerminalDualDuctVAV : public ModelObject
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
  // - Status: Scalar Parity. The scalar surface is aligned, but the canonical wrapper still exposes schedule, node, and DSOA relationship convenience APIs that epmodel has not reintroduced.
  // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctVAV.
  // - Implemented Parity: `maximumDamperAirFlowRate` and `zoneMinimumAirFlowFraction` preserve the canonical scalar behavior and autosize semantics.
  // - Documented Delta: epmodel still omits the availability-schedule, node, DSOA, and turndown-schedule wrappers that canonical model code exposes.
  // - Field/Storage Mapping: Availability Schedule Name, Air Outlet Node Name, Hot Air Inlet Node Name, Cold Air Inlet Node Name, Design Specification Outdoor Air Object Name, and Minimum Air Flow Turndown Schedule Name are relationship fields and intentionally excluded from scalar accessors.
  // - Evidence: `src/model/AirTerminalDualDuctVAV.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAV.cpp`, and `src/epmodel/test/AirTerminalDualDuctVAV_GTest.cpp` show the same scalar mapping and omitted relationship surface.
  // - Remaining Parity Work: Reintroduce the schedule, DSOA, and node-relationship wrappers if full model-side parity is needed.
  boost::optional<double> maximumDamperAirFlowRate() const;
  bool isMaximumDamperAirFlowRateAutosized() const;
  bool setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate);
  void autosizeMaximumDamperAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

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
