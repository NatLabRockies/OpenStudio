/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERFUNCTIONOFPOWER_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERFUNCTIONOFPOWER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterInverterFunctionOfPower_Impl;
}

class EPMODEL_API ElectricLoadCenterInverterFunctionOfPower : public ModelObject
{
 public:
  explicit ElectricLoadCenterInverterFunctionOfPower(const Model& model);

  virtual ~ElectricLoadCenterInverterFunctionOfPower() override = default;
  ElectricLoadCenterInverterFunctionOfPower(const ElectricLoadCenterInverterFunctionOfPower& other) = default;
  ElectricLoadCenterInverterFunctionOfPower(ElectricLoadCenterInverterFunctionOfPower&& other) = default;
  ElectricLoadCenterInverterFunctionOfPower& operator=(const ElectricLoadCenterInverterFunctionOfPower&) = default;
  ElectricLoadCenterInverterFunctionOfPower& operator=(ElectricLoadCenterInverterFunctionOfPower&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: radiativeFraction, ratedMaximumContinuousInputPower, minimumEfficiency, maximumEfficiency,
  //   minimumPowerOutput, maximumPowerOutput, and ancillaryPowerConsumedInStandby map directly to
  //   ElectricLoadCenter:Inverter:FunctionOfPower scalar numeric fields.
  // - Field Mapping: Availability Schedule Name, Zone Name, and Efficiency Function of Power Curve Name are
  //   relationship-like link fields and intentionally excluded from scalar accessor scope.
  // - ForwardTranslator evidence: no openstudio::model counterpart exists; IDD-derived naming is used for this EP-only type.
  // - TODO(parity): add relationship APIs incrementally without breaking scalar signatures.
  boost::optional<double> radiativeFraction() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();

  boost::optional<double> ratedMaximumContinuousInputPower() const;
  bool setRatedMaximumContinuousInputPower(double ratedMaximumContinuousInputPower);
  void resetRatedMaximumContinuousInputPower();

  boost::optional<double> minimumEfficiency() const;
  bool setMinimumEfficiency(double minimumEfficiency);
  void resetMinimumEfficiency();

  boost::optional<double> maximumEfficiency() const;
  bool setMaximumEfficiency(double maximumEfficiency);
  void resetMaximumEfficiency();

  boost::optional<double> minimumPowerOutput() const;
  bool setMinimumPowerOutput(double minimumPowerOutput);
  void resetMinimumPowerOutput();

  boost::optional<double> maximumPowerOutput() const;
  bool setMaximumPowerOutput(double maximumPowerOutput);
  void resetMaximumPowerOutput();

  boost::optional<double> ancillaryPowerConsumedInStandby() const;
  bool setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby);
  void resetAncillaryPowerConsumedInStandby();

 protected:
  using ImplType = detail::ElectricLoadCenterInverterFunctionOfPower_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterInverterFunctionOfPower(std::shared_ptr<detail::ElectricLoadCenterInverterFunctionOfPower_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
