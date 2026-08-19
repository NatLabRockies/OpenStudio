/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  /** \brief Represents a fluid-temperature-controlled VRF DX cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxvariablerefrigerantflowfluidtemperaturecontrol,Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl}.
   *
   * \par Important behavior
   * EPModel exposes the fixed serial air path through <code>StraightComponent</code> while retaining the EnergyPlus scalar and curve relationships.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl</code>.
   * <b>Changed:</b> EPModel adds the straight-component inlet/outlet surface. <b>Not yet available:</b> autosized-result helpers; standalone <code>addToNode()</code> insertion remains rejected.
   *
   * \par Known limitations
   * This coil is intended for compound VRF or terminal ownership rather than general standalone loop insertion.
   */
  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl : public StraightComponent
  {
   public:
    explicit CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model);

    virtual ~CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl() override = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(const CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl& other) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&& other) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&
      operator=(const CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl& operator=(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&&) = default;

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

    double indoorUnitReferenceSuperheating() const;
    bool setIndoorUnitReferenceSuperheating(double indoorUnitReferenceSuperheating);

    Curve indoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const;
    bool setIndoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(const Curve& curve);

   protected:
    using ImplType = detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(
      std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
