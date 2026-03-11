/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_IMPL_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatExchangerAirToAirFlatPlate_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatExchangerAirToAirFlatPlate_Impl() override = default;

  boost::optional<std::string> flowArrangementType() const;
  bool economizerLockout() const;
  bool isEconomizerLockoutDefaulted() const;
  boost::optional<double> ratioofSupplytoSecondaryhAValues() const;
  boost::optional<double> nominalSupplyAirFlowRate() const;
  bool isNominalSupplyAirFlowRateAutosized() const;
  double nominalSupplyAirInletTemperature() const;
  double nominalSupplyAirOutletTemperature() const;
  boost::optional<double> nominalSecondaryAirFlowRate() const;
  bool isNominalSecondaryAirFlowRateAutosized() const;
  double nominalSecondaryAirInletTemperature() const;
  boost::optional<double> nominalElectricPower() const;

  bool setFlowArrangementType(const std::string& flowArrangementType);
  void resetFlowArrangementType();
  bool setEconomizerLockout(bool economizerLockout);
  void resetEconomizerLockout();
  bool setRatioofSupplytoSecondaryhAValues(double ratioofSupplytoSecondaryhAValues);
  void resetRatioofSupplytoSecondaryhAValues();
  bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
  void resetNominalSupplyAirFlowRate();
  void autosizeNominalSupplyAirFlowRate();
  bool setNominalSupplyAirInletTemperature(double nominalSupplyAirInletTemperature);
  bool setNominalSupplyAirOutletTemperature(double nominalSupplyAirOutletTemperature);
  bool setNominalSecondaryAirFlowRate(double nominalSecondaryAirFlowRate);
  void autosizeNominalSecondaryAirFlowRate();
  bool setNominalSecondaryAirInletTemperature(double nominalSecondaryAirInletTemperature);
  bool setNominalElectricPower(double nominalElectricPower);
  void resetNominalElectricPower();

 private:
  std::vector<std::string> flowArrangementTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
