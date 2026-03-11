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
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: maximumDamperAirFlowRate maps directly to E+ AirTerminal:DualDuct:VAV Maximum Damper Air Flow Rate.
  // - Field Mapping: zoneMinimumAirFlowFraction maps directly to E+ AirTerminal:DualDuct:VAV Zone Minimum Air Flow Fraction.
  // - Field Mapping: Availability Schedule Name, Air Outlet Node Name, Hot Air Inlet Node Name, Cold Air Inlet Node Name,
  //   Design Specification Outdoor Air Object Name, and Minimum Air Flow Turndown Schedule Name are relationship fields and
  //   intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalDualDuctVAV writes these two scalar fields plus relationship links.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
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
