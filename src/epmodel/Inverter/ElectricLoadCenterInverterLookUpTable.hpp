/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterInverterLookUpTable_Impl;
}

class EPMODEL_API ElectricLoadCenterInverterLookUpTable : public ModelObject
{
 public:
  explicit ElectricLoadCenterInverterLookUpTable(const Model& model);

  virtual ~ElectricLoadCenterInverterLookUpTable() override = default;
  ElectricLoadCenterInverterLookUpTable(const ElectricLoadCenterInverterLookUpTable& other) = default;
  ElectricLoadCenterInverterLookUpTable(ElectricLoadCenterInverterLookUpTable&& other) = default;
  ElectricLoadCenterInverterLookUpTable& operator=(const ElectricLoadCenterInverterLookUpTable&) = default;
  ElectricLoadCenterInverterLookUpTable& operator=(ElectricLoadCenterInverterLookUpTable&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves existing openstudio::model scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: scalar APIs map directly to ElectricLoadCenter:Inverter:LookUpTable scalar numeric fields.
  // - Field Mapping: Availability Schedule Name and Zone Name are relationship-like link fields and are excluded.
  // - ForwardTranslator evidence: translateElectricLoadCenterInverterLookUpTable maps these same scalar methods to
  //   matching EnergyPlus fields.
  // - TODO(parity): add relationship APIs incrementally without changing preserved scalar signatures.
  boost::optional<double> radiativeFraction() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();

  boost::optional<double> ratedMaximumContinuousOutputPower() const;
  bool setRatedMaximumContinuousOutputPower(double ratedMaximumContinuousOutputPower);
  void resetRatedMaximumContinuousOutputPower();

  boost::optional<double> nightTareLossPower() const;
  bool setNightTareLossPower(double nightTareLossPower);
  void resetNightTareLossPower();

  boost::optional<double> nominalVoltageInput() const;
  bool setNominalVoltageInput(double nominalVoltageInput);
  void resetNominalVoltageInput();

  boost::optional<double> efficiencyAt10PowerAndNominalVoltage() const;
  bool setEfficiencyAt10PowerAndNominalVoltage(double efficiencyAt10PowerAndNominalVoltage);
  void resetEfficiencyAt10PowerAndNominalVoltage();

  boost::optional<double> efficiencyAt20PowerAndNominalVoltage() const;
  bool setEfficiencyAt20PowerAndNominalVoltage(double efficiencyAt20PowerAndNominalVoltage);
  void resetEfficiencyAt20PowerAndNominalVoltage();

  boost::optional<double> efficiencyAt30PowerAndNominalVoltage() const;
  bool setEfficiencyAt30PowerAndNominalVoltage(double efficiencyAt30PowerAndNominalVoltage);
  void resetEfficiencyAt30PowerAndNominalVoltage();

  boost::optional<double> efficiencyAt50PowerAndNominalVoltage() const;
  bool setEfficiencyAt50PowerAndNominalVoltage(double efficiencyAt50PowerAndNominalVoltage);
  void resetEfficiencyAt50PowerAndNominalVoltage();

  boost::optional<double> efficiencyAt75PowerAndNominalVoltage() const;
  bool setEfficiencyAt75PowerAndNominalVoltage(double efficiencyAt75PowerAndNominalVoltage);
  void resetEfficiencyAt75PowerAndNominalVoltage();

  boost::optional<double> efficiencyAt100PowerAndNominalVoltage() const;
  bool setEfficiencyAt100PowerAndNominalVoltage(double efficiencyAt100PowerAndNominalVoltage);
  void resetEfficiencyAt100PowerAndNominalVoltage();

 protected:
  using ImplType = detail::ElectricLoadCenterInverterLookUpTable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterInverterLookUpTable(std::shared_ptr<detail::ElectricLoadCenterInverterLookUpTable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
