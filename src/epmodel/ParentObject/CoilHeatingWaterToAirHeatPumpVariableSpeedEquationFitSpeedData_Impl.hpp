/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_IMPL_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit;

  namespace detail {

    class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl() override = default;

      double referenceUnitGrossRatedHeatingCapacity() const;
      bool setReferenceUnitGrossRatedHeatingCapacity(double referenceUnitGrossRatedHeatingCapacity);

      double referenceUnitGrossRatedHeatingCOP() const;
      bool setReferenceUnitGrossRatedHeatingCOP(double referenceUnitGrossRatedHeatingCOP);

      double referenceUnitRatedAirFlow() const;
      bool setReferenceUnitRatedAirFlow(double referenceUnitRatedAirFlow);

      double referenceUnitRatedWaterFlowRate() const;
      bool setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate);

      Curve heatingCapacityFunctionofTemperatureCurve() const;
      bool setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve);

      Curve totalHeatingCapacityFunctionofAirFlowFractionCurve() const;
      bool setTotalHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve);

      Curve heatingCapacityFunctionofWaterFlowFractionCurve() const;
      bool setHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve);

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

      boost::optional<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit> parent() const;
      boost::optional<unsigned> attachedSpeedIndex() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
