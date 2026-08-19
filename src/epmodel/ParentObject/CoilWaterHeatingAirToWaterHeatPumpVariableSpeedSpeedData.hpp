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

  /** \brief Represents one performance-data speed for a variable-speed air-to-water heat-pump water heater.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. This class exposes one extensible speed-data
   * row on \epobject{group-heating-and-cooling-coils.html#coil-waterheating-airtowaterheatpump-variablespeed,Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed}.
   * The row contains the rated values and performance-curve references
   * represented by this class.
   *
   * \par Important behavior
   * The wrapper is transient. A detached instance keeps its values and curve
   * references in the EPModel runtime object. When passed to the owning coil's
   * <code>addSpeed(...)</code>, those values are copied into one extensible row
   * and the wrapper becomes a live view of that row; setters then update the
   * parent row. Removing a row through the owning coil detaches the wrapper.
   * Calling <code>remove()</code> on an attached wrapper also removes its parent
   * speed row.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData</code>.
   * - <b>Added:</b> <code>cOPFunctionofTemperatureCurve()</code>,
   *   <code>cOPFunctionofAirFlowFractionCurve()</code>, and
   *   <code>cOPFunctionofWaterFlowFractionCurve()</code> are mixed-case aliases
   *   for <code>copFunctionofTemperatureCurve()</code>,
   *   <code>copFunctionofAirFlowFractionCurve()</code>, and
   *   <code>copFunctionofWaterFlowFractionCurve()</code>, respectively.
   * No other known public API differences.
   *
   * \par Known limitations
   * This class cannot be persisted as an independent EnergyPlus object; use the
   * owning <code>Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed</code>
   * object to add or remove speed rows. Removing a loaded speed row does not
   * copy its parent-row values into the detached wrapper; read or copy values
   * before removal when they must be retained.
   */
  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData : public ParentObject
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(const Model& model);

    virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData() override = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& operator=(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& operator=(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData&&) = default;

    static IddObjectType iddObjectType();

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
