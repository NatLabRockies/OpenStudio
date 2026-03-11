/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolNoReheat : public ModelObject
{
 public:
  explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const Model& model);

  virtual ~AirTerminalSingleDuctVAVHeatAndCoolNoReheat() override = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat&) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: maximumAirFlowRate maps directly to E+ AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat Maximum Air Flow Rate.
  // - Field Mapping: zoneMinimumAirFlowFraction maps directly to E+ AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat Zone Minimum Air Flow Fraction.
  // - Field Mapping: Availability Schedule Name, Air Outlet Node Name, Air Inlet Node Name, and Minimum Air Flow Turndown Schedule Name are relationship
  //   fields and intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctVAVHeatAndCoolNoReheat writes these two scalar fields plus relationship links.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void autosizeMaximumAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

 protected:
  using ImplType = detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
