/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTWETCOIL_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTWETCOIL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EvaporativeCoolerIndirectWetCoil_Impl;
}

class EPMODEL_API EvaporativeCoolerIndirectWetCoil : public ModelObject
{
 public:
  explicit EvaporativeCoolerIndirectWetCoil(const Model& model);

  virtual ~EvaporativeCoolerIndirectWetCoil() override = default;
  EvaporativeCoolerIndirectWetCoil(const EvaporativeCoolerIndirectWetCoil& other) = default;
  EvaporativeCoolerIndirectWetCoil(EvaporativeCoolerIndirectWetCoil&& other) = default;
  EvaporativeCoolerIndirectWetCoil& operator=(const EvaporativeCoolerIndirectWetCoil&) = default;
  EvaporativeCoolerIndirectWetCoil& operator=(EvaporativeCoolerIndirectWetCoil&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: coilMaximumEfficiency/coilFlowRatio/recirculatingWaterPumpPowerConsumption/secondaryAirFanFlowRate/
  //   secondaryAirFanTotalEfficiency/secondaryAirFanDeltaPressure/controlType map directly to
  //   EvaporativeCooler:Indirect:WetCoil fields.
  // - Field Mapping: Availability Schedule Name, Primary Air Inlet Node Name, Primary Air Outlet Node Name,
  //   Water Supply Storage Tank Name, and Secondary Air Inlet Node Name are relationship-like fields and are excluded from
  //   scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  double coilMaximumEfficiency() const;
  bool setCoilMaximumEfficiency(double coilMaximumEfficiency);

  boost::optional<double> coilFlowRatio() const;
  bool setCoilFlowRatio(double coilFlowRatio);
  void resetCoilFlowRatio();

  double recirculatingWaterPumpPowerConsumption() const;
  bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

  double secondaryAirFanFlowRate() const;
  bool setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate);

  double secondaryAirFanTotalEfficiency() const;
  bool setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency);

  double secondaryAirFanDeltaPressure() const;
  bool setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure);

  boost::optional<std::string> controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

 protected:
  using ImplType = detail::EvaporativeCoolerIndirectWetCoil_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EvaporativeCoolerIndirectWetCoil(std::shared_ptr<detail::EvaporativeCoolerIndirectWetCoil_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
