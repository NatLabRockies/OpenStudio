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

  /** \brief Represents one performance-data speed for a variable-speed water-to-air cooling heat pump.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. This class exposes one extensible speed-data
   * row on \epobject{group-heating-and-cooling-coils.html#coilcoolingwatertoairheatpumpvariablespeedequationfit,Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit}.
   * The row contains the rated values, performance-curve references, and waste
   * heat data represented by this class.
   *
   * \par Important behavior
   * The wrapper is transient. A detached instance keeps its values and curve
   * references in the EPModel runtime object. When passed to the owning coil's
   * <code>addSpeed(...)</code>, those values are copied into one extensible row
   * and the wrapper becomes a live view of that row; setters then update the
   * parent row. When the owning coil removes the row, the wrapper is detached
   * and retains its values and curve references.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * This class cannot be persisted as an independent EnergyPlus object; use the
   * owning <code>Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit</code>
   * object to add or remove speed rows.
   */
  class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData : public ParentObject
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

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
