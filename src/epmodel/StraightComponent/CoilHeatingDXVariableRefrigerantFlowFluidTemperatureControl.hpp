/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  /** \brief Represents a fluid-temperature-controlled VRF DX heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdxvariablerefrigerantflowfluidtemperaturecontrol,Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl}.
   *
   * \par Important behavior
   * EPModel exposes the fixed serial air path through <code>StraightComponent</code> while retaining the EnergyPlus scalar and curve relationships.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl</code>.
   * <b>Changed:</b> EPModel adds the straight-component inlet/outlet surface. <b>Not yet available:</b> autosized-result helpers; standalone <code>addToNode()</code> insertion remains rejected.
   *
   * \par Known limitations
   * This coil is intended for compound VRF or terminal ownership rather than general standalone loop insertion.
   */
  class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl : public StraightComponent
  {
   public:
    explicit CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model);

    virtual ~CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl() override = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& other) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&& other) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&
      operator=(const CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& operator=(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();

    double indoorUnitReferenceSubcooling() const;
    Curve indoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const;
    bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);
    bool setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve);

   protected:
    using ImplType = detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(
      std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
