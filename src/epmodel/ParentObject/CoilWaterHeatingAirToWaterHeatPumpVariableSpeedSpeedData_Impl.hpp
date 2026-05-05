/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEEDSPEEDDATA_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEEDSPEEDDATA_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class CoilWaterHeatingAirToWaterHeatPumpVariableSpeed;

  namespace detail {

    class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl() override = default;

      double ratedWaterHeatingCapacity() const;
      bool setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity);

      double ratedWaterHeatingCOP() const;
      bool setRatedWaterHeatingCOP(double ratedWaterHeatingCOP);

      double ratedSensibleHeatRatio() const;
      bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);

      double referenceUnitRatedAirFlowRate() const;
      bool setReferenceUnitRatedAirFlowRate(double referenceUnitRatedAirFlowRate);

      double referenceUnitRatedWaterFlowRate() const;
      bool setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate);

      double referenceUnitWaterPumpInputPowerAtRatedConditions() const;
      bool setReferenceUnitWaterPumpInputPowerAtRatedConditions(double referenceUnitWaterPumpInputPowerAtRatedConditions);

      Curve totalWaterHeatingCapacityFunctionofTemperatureCurve() const;
      bool setTotalWaterHeatingCapacityFunctionofTemperatureCurve(const Curve& curve);

      Curve totalWaterHeatingCapacityFunctionofAirFlowFractionCurve() const;
      bool setTotalWaterHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve);

      Curve totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve() const;
      bool setTotalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve);

      Curve cOPFunctionofTemperatureCurve() const;
      bool setCOPFunctionofTemperatureCurve(const Curve& curve);

      Curve cOPFunctionofAirFlowFractionCurve() const;
      bool setCOPFunctionofAirFlowFractionCurve(const Curve& curve);

      Curve cOPFunctionofWaterFlowFractionCurve() const;
      bool setCOPFunctionofWaterFlowFractionCurve(const Curve& curve);

      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      boost::optional<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed> parent() const;
      boost::optional<unsigned> attachedSpeedIndex() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
