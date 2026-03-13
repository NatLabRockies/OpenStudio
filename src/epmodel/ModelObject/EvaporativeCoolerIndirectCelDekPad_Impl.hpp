/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTCELDEKPAD_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTCELDEKPAD_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API EvaporativeCoolerIndirectCelDekPad_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EvaporativeCoolerIndirectCelDekPad_Impl() override = default;

  // Direct pad area values
  boost::optional<double> directPadArea() const;
  bool setDirectPadArea(double directPadArea);
  void resetDirectPadArea();
  void autosizeDirectPadArea();
  bool isDirectPadAreaAutosized() const;

  // Direct pad depth values
  boost::optional<double> directPadDepth() const;
  bool setDirectPadDepth(double directPadDepth);
  void resetDirectPadDepth();
  void autosizeDirectPadDepth();
  bool isDirectPadDepthAutosized() const;

  double recirculatingWaterPumpPowerConsumption() const;
  bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

  double secondaryAirFanFlowRate() const;
  bool setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate);

  boost::optional<double> secondaryAirFanTotalEfficiency() const;
  bool setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency);
  void resetSecondaryAirFanTotalEfficiency();

  double secondaryAirFanDeltaPressure() const;
  bool setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure);

  double indirectHeatExchangerEffectiveness() const;
  bool setIndirectHeatExchangerEffectiveness(double indirectHeatExchangerEffectiveness);

  boost::optional<std::string> controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
