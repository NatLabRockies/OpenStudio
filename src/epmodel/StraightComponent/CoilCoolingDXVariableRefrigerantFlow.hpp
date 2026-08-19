/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlow_Impl;
  }

  /** \brief Represents a variable-refrigerant-flow DX cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxvariablerefrigerantflow,Coil:Cooling:DX:VariableRefrigerantFlow}.
   *
   * \par Important behavior
   * EPModel exposes the fixed serial air path through <code>StraightComponent</code> while retaining the EnergyPlus scalar and curve relationships.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDXVariableRefrigerantFlow</code>.
   * <b>Changed:</b> EPModel adds the straight-component inlet/outlet surface. <b>Not yet available:</b> autosized-result helpers; standalone <code>addToNode()</code> insertion remains rejected.
   *
   * \par Known limitations
   * This coil is intended for compound VRF or terminal ownership rather than general standalone loop insertion.
   */
  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow : public StraightComponent
  {
   public:
    explicit CoilCoolingDXVariableRefrigerantFlow(const Model& model);

    virtual ~CoilCoolingDXVariableRefrigerantFlow() override = default;
    CoilCoolingDXVariableRefrigerantFlow(const CoilCoolingDXVariableRefrigerantFlow& other) = default;
    CoilCoolingDXVariableRefrigerantFlow(CoilCoolingDXVariableRefrigerantFlow&& other) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(const CoilCoolingDXVariableRefrigerantFlow&) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(CoilCoolingDXVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    bool isRatedTotalCoolingCapacityAutosized() const;
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleHeatRatio() const;
    bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
    bool isRatedSensibleHeatRatioAutosized() const;
    void autosizeRatedSensibleHeatRatio();

    boost::optional<double> ratedAirFlowRate() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    bool isRatedAirFlowRateAutosized() const;
    void autosizeRatedAirFlowRate();

    Curve coolingCapacityRatioModifierFunctionofTemperatureCurve() const;
    bool setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve);

    Curve coolingCapacityModifierCurveFunctionofFlowFraction() const;
    bool setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve);

   protected:
    using ImplType = detail::CoilCoolingDXVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
