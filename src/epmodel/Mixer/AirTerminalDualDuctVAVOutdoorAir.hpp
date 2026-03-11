/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalDualDuctVAVOutdoorAir_Impl;
}

class EPMODEL_API AirTerminalDualDuctVAVOutdoorAir : public ModelObject
{
 public:
  explicit AirTerminalDualDuctVAVOutdoorAir(const Model& model);

  virtual ~AirTerminalDualDuctVAVOutdoorAir() override = default;
  AirTerminalDualDuctVAVOutdoorAir(const AirTerminalDualDuctVAVOutdoorAir& other) = default;
  AirTerminalDualDuctVAVOutdoorAir(AirTerminalDualDuctVAVOutdoorAir&& other) = default;
  AirTerminalDualDuctVAVOutdoorAir& operator=(const AirTerminalDualDuctVAVOutdoorAir&) = default;
  AirTerminalDualDuctVAVOutdoorAir& operator=(AirTerminalDualDuctVAVOutdoorAir&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> perPersonVentilationRateModeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: maximumTerminalAirFlowRate maps directly to E+ AirTerminal:DualDuct:VAV:OutdoorAir Maximum Terminal Air Flow Rate.
  // - Field Mapping: perPersonVentilationRateMode maps directly to E+ AirTerminal:DualDuct:VAV:OutdoorAir Per Person Ventilation Rate Mode.
  // - Field Mapping: controlForOutdoorAir behavior in model relies on OS-side boolean + translator wiring to
  //   Design Specification Outdoor Air Object Name; epmodel scalar scaffold excludes that relationship mapping.
  // - Field Mapping: Availability Schedule Name, Air Outlet Node Name, Outdoor Air Inlet Node Name,
  //   Recirculated Air Inlet Node Name, and Design Specification Outdoor Air Object Name are relationship fields
  //   and intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalDualDuctVAVOutdoorAir writes only these two scalar E+ fields plus relationship links.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
  boost::optional<double> maximumTerminalAirFlowRate() const;
  bool isMaximumTerminalAirFlowRateAutosized() const;
  bool setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate);
  void autosizeMaximumTerminalAirFlowRate();

  std::string perPersonVentilationRateMode() const;
  bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);

 protected:
  using ImplType = detail::AirTerminalDualDuctVAVOutdoorAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalDualDuctVAVOutdoorAir(std::shared_ptr<detail::AirTerminalDualDuctVAVOutdoorAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
