/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLAIRSUPPLY_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLAIRSUPPLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorFuelCellAirSupply_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorFuelCellAirSupply_Impl() override = default;

  double blowerHeatLossFactor() const;
  bool setBlowerHeatLossFactor(double blowerHeatLossFactor);
  void resetBlowerHeatLossFactor();

  std::string airSupplyRateCalculationMode() const;
  bool setAirSupplyRateCalculationMode(const std::string& airSupplyRateCalculationMode);

  boost::optional<double> stoichiometricRatio() const;
  bool setStoichiometricRatio(double stoichiometricRatio);
  void resetStoichiometricRatio();

  boost::optional<double> airRateAirTemperatureCoefficient() const;
  bool setAirRateAirTemperatureCoefficient(double airRateAirTemperatureCoefficient);
  void resetAirRateAirTemperatureCoefficient();

  std::string airIntakeHeatRecoveryMode() const;
  bool setAirIntakeHeatRecoveryMode(const std::string& airIntakeHeatRecoveryMode);

  std::string airSupplyConstituentMode() const;
  bool setAirSupplyConstituentMode(const std::string& airSupplyConstituentMode);

  boost::optional<unsigned int> numberofUserDefinedConstituents() const;

  std::vector<std::string> airSupplyRateCalculationModeValues() const;
  std::vector<std::string> airIntakeHeatRecoveryModeValues() const;
  std::vector<std::string> airSupplyConstituentModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
