/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;

  namespace detail {
    class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl;
  }

  class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData : public ParentObject
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    // This wrapper preserves the canonical OpenStudio speed-data child object for
    // a family that EnergyPlus stores as extensible rows on the parent coil. A
    // detached transient speed-data object keeps its own OS-style fields until it
    // is added to a parent coil. An attached transient speed-data object is a
    // live view over one specific parent extensible row.
    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model);

    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model, const Curve& heatingCapacityFunctionofTemperature,
                                                                   const Curve& totalHeatingCapacityFunctionofAirFlowFraction,
                                                                   const Curve& heatingCapacityFunctionofWaterFlowFraction,
                                                                   const Curve& energyInputRatioFunctionofTemperature,
                                                                   const Curve& energyInputRatioFunctionofAirFlowFraction,
                                                                   const Curve& energyInputRatioFunctionofWaterFlowFraction,
                                                                   const Curve& wasteHeatFunctionofTemperature);

    virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData() override = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& other) =
      default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&& other) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&
      operator=(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&
      operator=(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.
    // - Implemented Parity: The canonical scalar and curve relationships are exposed here. Detached instances behave like the canonical
    //   OpenStudio speed-data object. Attached instances are transient views over one parent EnergyPlus extensible row.
    // - Documented Delta: This child is transient in epmodel because EnergyPlus does not persist a standalone speed-data object.
    // - Field/Storage Mapping: Detached instances store their own OS-style fields. Attached instances route through the parent's
    //   `Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit` extensible row using `WorkspaceExtensibleGroup`.
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

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
      std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
