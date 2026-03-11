/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirConditionerVariableRefrigerantFlow_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirConditionerVariableRefrigerantFlow_Impl() override = default;

  boost::optional<double> grossRatedTotalCoolingCapacity() const;
  bool isGrossRatedTotalCoolingCapacityAutosized() const;
  bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
  void autosizeGrossRatedTotalCoolingCapacity();

  double grossRatedCoolingCOP() const;
  bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

  boost::optional<double> grossRatedHeatingCapacity() const;
  bool isGrossRatedHeatingCapacityAutosized() const;
  bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
  void autosizeGrossRatedHeatingCapacity();

  double ratedHeatingCapacitySizingRatio() const;
  bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);

  std::string heatingPerformanceCurveOutdoorTemperatureType() const;
  bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

  bool heatPumpWasteHeatRecovery() const;
  bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

  int numberofCompressors() const;
  bool setNumberofCompressors(int numberofCompressors);

  std::string defrostStrategy() const;
  bool setDefrostStrategy(const std::string& defrostStrategy);

  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);
  bool isCondenserTypeDefaulted() const;
  void resetCondenserType();

  std::vector<std::string> heatingPerformanceCurveOutdoorTemperatureTypeValues() const;
  std::vector<std::string> defrostStrategyValues() const;
  std::vector<std::string> condenserTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
