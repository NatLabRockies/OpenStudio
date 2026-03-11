/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctInletSideMixer_Impl;
}

class EPMODEL_API AirTerminalSingleDuctInletSideMixer : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctInletSideMixer(const Model& model);

  virtual ~AirTerminalSingleDuctInletSideMixer() override = default;
  AirTerminalSingleDuctInletSideMixer(const AirTerminalSingleDuctInletSideMixer& other) = default;
  AirTerminalSingleDuctInletSideMixer(AirTerminalSingleDuctInletSideMixer&& other) = default;
  AirTerminalSingleDuctInletSideMixer& operator=(const AirTerminalSingleDuctInletSideMixer&) = default;
  AirTerminalSingleDuctInletSideMixer& operator=(AirTerminalSingleDuctInletSideMixer&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> perPersonVentilationRateModeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: perPersonVentilationRateMode maps to EnergyPlus AirTerminal:SingleDuct:Mixer Per Person Ventilation Rate Mode.
  // - Field Mapping: The model-only controlForOutdoorAir behavior maps through ForwardTranslator to
  //   Design Specification Outdoor Air Object Name relationship wiring and is intentionally excluded from scalar epmodel accessors.
  // - Field Mapping: ZoneHVAC Unit Object Type/Name, Mixer Connection Type, and node/DSOA fields are relationship/target-link concepts
  //   and are intentionally excluded from scalar accessor generation in this saturation pass.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctInletSideMixer writes MixerConnectionType as "InletSide" and
  //   perPersonVentilationRateMode as a direct scalar, while relationship fields are resolved separately.
  // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
  std::string perPersonVentilationRateMode() const;
  bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);

 protected:
  using ImplType = detail::AirTerminalSingleDuctInletSideMixer_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctInletSideMixer(std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
