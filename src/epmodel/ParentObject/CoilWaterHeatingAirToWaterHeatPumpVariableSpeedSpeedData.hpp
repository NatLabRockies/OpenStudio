/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEEDSPEEDDATA_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEEDSPEEDDATA_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;

  namespace detail {
    class CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl;
  }

  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData : public ParentObject
  {
   public:
    // This wrapper preserves the canonical OpenStudio speed-data child object
    // for a family that EnergyPlus stores as extensible rows on the parent coil.
    // A detached transient speed-data object keeps its own OpenStudio-style
    // fields until it is added to a parent coil. An attached transient
    // speed-data object is a live view over one specific parent extensible row.
    explicit CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(const Model& model);

    virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData() override = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& operator=(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& operator=(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.
    // - Implemented Parity: The canonical scalar and curve relationships are exposed here. Detached instances behave
    //   like the canonical OpenStudio speed-data object. Attached instances are transient views over one parent
    //   EnergyPlus extensible row, and removing an attached transient wrapper removes the parent speed row too.
    // - Documented Delta: This child is transient in epmodel because EnergyPlus does not persist a standalone
    //   speed-data object.
    // - Field/Storage Mapping: Detached instances store their own OS-style fields. Attached instances route through the
    //   parent's `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` extensible row using `WorkspaceExtensibleGroup`.
    // - API Note: The lowercase `copFunctionof...` getters mirror the canonical model API. The legacy mixed-case
    //   `cOPFunctionof...` getters remain as compatibility aliases over the same underlying fields.
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

    Curve copFunctionofTemperatureCurve() const;
    Curve cOPFunctionofTemperatureCurve() const;
    bool setCOPFunctionofTemperatureCurve(const Curve& curve);

    Curve copFunctionofAirFlowFractionCurve() const;
    Curve cOPFunctionofAirFlowFractionCurve() const;
    bool setCOPFunctionofAirFlowFractionCurve(const Curve& curve);

    Curve copFunctionofWaterFlowFractionCurve() const;
    Curve cOPFunctionofWaterFlowFractionCurve() const;
    bool setCOPFunctionofWaterFlowFractionCurve(const Curve& curve);

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(
      std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
