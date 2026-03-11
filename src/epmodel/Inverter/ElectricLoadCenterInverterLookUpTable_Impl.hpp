/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERLOOKUPTABLE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterInverterLookUpTable_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricLoadCenterInverterLookUpTable_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
