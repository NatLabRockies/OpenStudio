/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorFuelCellAuxiliaryHeater_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorFuelCellAuxiliaryHeater_Impl() override = default;

  double excessAirRatio() const;
  bool setExcessAirRatio(double excessAirRatio);
  void resetExcessAirRatio();

  double ancillaryPowerConstantTerm() const;
  bool setAncillaryPowerConstantTerm(double ancillaryPowerConstantTerm);
  void resetAncillaryPowerConstantTerm();

  double ancillaryPowerLinearTerm() const;
  bool setAncillaryPowerLinearTerm(double ancillaryPowerLinearTerm);
  void resetAncillaryPowerLinearTerm();

  double skinLossUFactorTimesAreaValue() const;
  bool setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue);
  void resetSkinLossUFactorTimesAreaValue();

  std::string skinLossDestination() const;
  bool setSkinLossDestination(const std::string& skinLossDestination);
  void resetSkinLossDestination();

  std::string heatingCapacityUnits() const;
  bool setHeatingCapacityUnits(const std::string& heatingCapacityUnits);
  void resetHeatingCapacityUnits();

  double maximumHeatingCapacityinWatts() const;
  bool setMaximumHeatingCapacityinWatts(double maximumHeatingCapacityinWatts);
  void resetMaximumHeatingCapacityinWatts();

  double minimumHeatingCapacityinWatts() const;
  bool setMinimumHeatingCapacityinWatts(double minimumHeatingCapacityinWatts);
  void resetMinimumHeatingCapacityinWatts();

  double maximumHeatingCapacityinKmolperSecond() const;
  bool setMaximumHeatingCapacityinKmolperSecond(double maximumHeatingCapacityinKmolperSecond);
  void resetMaximumHeatingCapacityinKmolperSecond();

  double minimumHeatingCapacityinKmolperSecond() const;
  bool setMinimumHeatingCapacityinKmolperSecond(double minimumHeatingCapacityinKmolperSecond);
  void resetMinimumHeatingCapacityinKmolperSecond();

  std::vector<std::string> skinLossDestinationValues() const;
  std::vector<std::string> heatingCapacityUnitsValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
