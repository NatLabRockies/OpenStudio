/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilHeatingDXVariableRefrigerantFlow_Impl;
  }

  /** \brief Represents a variable-refrigerant-flow DX heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdxvariablerefrigerantflow,Coil:Heating:DX:VariableRefrigerantFlow}.
   *
   * \par Important behavior
   * EPModel exposes the fixed serial air path through <code>StraightComponent</code> while retaining the EnergyPlus scalar and curve relationships.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDXVariableRefrigerantFlow</code>.
   * <b>Changed:</b> EPModel adds the straight-component inlet/outlet surface. <b>Not yet available:</b> autosized-result helpers; standalone <code>addToNode()</code> insertion remains rejected.
   *
   * \par Known limitations
   * This coil is intended for compound VRF or terminal ownership rather than general standalone loop insertion.
   */
  class EPMODEL_API CoilHeatingDXVariableRefrigerantFlow : public StraightComponent
  {
   public:
    explicit CoilHeatingDXVariableRefrigerantFlow(const Model& model);

    virtual ~CoilHeatingDXVariableRefrigerantFlow() override = default;
    CoilHeatingDXVariableRefrigerantFlow(const CoilHeatingDXVariableRefrigerantFlow& other) = default;
    CoilHeatingDXVariableRefrigerantFlow(CoilHeatingDXVariableRefrigerantFlow&& other) = default;
    CoilHeatingDXVariableRefrigerantFlow& operator=(const CoilHeatingDXVariableRefrigerantFlow&) = default;
    CoilHeatingDXVariableRefrigerantFlow& operator=(CoilHeatingDXVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void autosizeRatedAirFlowRate();

    Curve heatingCapacityRatioModifierFunctionofTemperatureCurve() const;
    bool setHeatingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve);

    Curve heatingCapacityModifierFunctionofFlowFractionCurve() const;
    bool setHeatingCapacityModifierFunctionofFlowFractionCurve(const Curve& curve);

   protected:
    using ImplType = detail::CoilHeatingDXVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
