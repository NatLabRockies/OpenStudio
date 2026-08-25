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

  /** \brief Represents one performance-data speed for a variable-speed water-to-air heating heat pump.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. This class exposes one extensible speed-data
   * row on \epobject{group-heating-and-cooling-coils.html#coilheatingwatertoairheatpumpvariablespeedequationfit,Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit}.
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
   * <code>openstudio::model::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * This class cannot be persisted as an independent EnergyPlus object; use the
   * owning <code>Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit</code>
   * object to add or remove speed rows.
   */
  class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData : public ParentObject
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

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
