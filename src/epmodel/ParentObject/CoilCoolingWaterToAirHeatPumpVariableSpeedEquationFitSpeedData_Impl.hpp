/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

class Curve;
class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit;

namespace detail {

class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl() override = default;

  double referenceUnitGrossRatedTotalCoolingCapacity() const;
  bool setReferenceUnitGrossRatedTotalCoolingCapacity(double referenceUnitGrossRatedTotalCoolingCapacity);

  double referenceUnitGrossRatedSensibleHeatRatio() const;
  bool setReferenceUnitGrossRatedSensibleHeatRatio(double referenceUnitGrossRatedSensibleHeatRatio);

  double referenceUnitGrossRatedCoolingCOP() const;
  bool setReferenceUnitGrossRatedCoolingCOP(double referenceUnitGrossRatedCoolingCOP);

  double referenceUnitRatedAirFlowRate() const;
  bool setReferenceUnitRatedAirFlowRate(double referenceUnitRatedAirFlowRate);

  double referenceUnitRatedWaterFlowRate() const;
  bool setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate);

  Curve totalCoolingCapacityFunctionofTemperatureCurve() const;
  bool setTotalCoolingCapacityFunctionofTemperatureCurve(const Curve& curve);

  Curve totalCoolingCapacityFunctionofAirFlowFractionCurve() const;
  bool setTotalCoolingCapacityFunctionofAirFlowFractionCurve(const Curve& curve);

  Curve totalCoolingCapacityFunctionofWaterFlowFractionCurve() const;
  bool setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve);

  Curve energyInputRatioFunctionofTemperatureCurve() const;
  bool setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);

  Curve energyInputRatioFunctionofAirFlowFractionCurve() const;
  bool setEnergyInputRatioFunctionofAirFlowFractionCurve(const Curve& curve);

  Curve energyInputRatioFunctionofWaterFlowFractionCurve() const;
  bool setEnergyInputRatioFunctionofWaterFlowFractionCurve(const Curve& curve);

  double referenceUnitWasteHeatFractionofInputPowerAtRatedConditions() const;
  bool setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(double referenceUnitWasteHeatFractionofInputPowerAtRatedConditions);

  Curve wasteHeatFunctionofTemperatureCurve() const;
  bool setWasteHeatFunctionofTemperatureCurve(const Curve& curve);

  std::vector<ModelObject> children() const override;

  boost::optional<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit> parent() const;
  boost::optional<unsigned> attachedSpeedIndex() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
