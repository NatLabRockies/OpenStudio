/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFITSPEEDDATA_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl;
  }

  class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData : public ParentObject
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    // This wrapper preserves the canonical OpenStudio speed-data child object for
    // a family that EnergyPlus stores as extensible rows on the parent coil. A
    // detached transient speed-data object keeps its own OS-style fields until it
    // is added to a parent coil. An attached transient speed-data object is a
    // live view over one specific parent extensible row.
    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model);

    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model, const Curve& totalCoolingCapacityFunctionofTemperature,
                                                                   const Curve& totalCoolingCapacityFunctionofAirFlowFraction,
                                                                   const Curve& totalCoolingCapacityFunctionofWaterFlowFraction,
                                                                   const Curve& energyInputRatioFunctionofTemperature,
                                                                   const Curve& energyInputRatioFunctionofAirFlowFraction,
                                                                   const Curve& energyInputRatioFunctionofWaterFlowFraction,
                                                                   const Curve& wasteHeatFunctionofTemperature);

    virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData() override = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& other) =
      default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&& other) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&
      operator=(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&
      operator=(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.
    // - Implemented Parity: The canonical scalar and curve relationships are exposed here. Detached instances behave like the canonical
    //   OpenStudio speed-data object. Attached instances are transient views over one parent EnergyPlus extensible row.
    // - Documented Delta: This child is transient in epmodel because EnergyPlus does not persist a standalone speed-data object.
    // - Field/Storage Mapping: Detached instances store their own OS-style fields. Attached instances route through the parent's
    //   `Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit` extensible row using `WorkspaceExtensibleGroup`.
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

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
      std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
