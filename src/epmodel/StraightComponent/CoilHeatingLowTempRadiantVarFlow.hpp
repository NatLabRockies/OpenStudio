/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_HPP
#define EPMODEL_COILHEATINGLOWTEMPRADIANTVARFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ZoneHVACLowTempRadiantVarFlow;

  namespace detail {
    class CoilHeatingLowTempRadiantVarFlow_Impl;
  }

  /** \brief Represents a heating-coil view of a variable-flow low-temperature radiant system.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Heating:LowTemperatureRadiant:VariableFlow</code> onto \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantvariableflow,ZoneHVAC:LowTemperatureRadiant:VariableFlow} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to the parent design/coil storage and maps
   * its water ports to the parent's <code>Heating Water Inlet Node Name</code> and <code>Heating Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingLowTempRadiantVarFlow</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilHeatingLowTempRadiantVarFlow : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilHeatingLowTempRadiantVarFlow(const Model& model);

    virtual ~CoilHeatingLowTempRadiantVarFlow() override = default;
    CoilHeatingLowTempRadiantVarFlow(const CoilHeatingLowTempRadiantVarFlow& other) = default;
    CoilHeatingLowTempRadiantVarFlow(CoilHeatingLowTempRadiantVarFlow&& other) = default;
    CoilHeatingLowTempRadiantVarFlow& operator=(const CoilHeatingLowTempRadiantVarFlow&) = default;
    CoilHeatingLowTempRadiantVarFlow& operator=(CoilHeatingLowTempRadiantVarFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> heatingDesignCapacityMethodValues();

    boost::optional<double> maximumHotWaterFlow() const;
    bool isMaximumHotWaterFlowDefaulted() const;
    bool isMaximumHotWaterFlowAutosized() const;
    bool setMaximumHotWaterFlow(double maximumHotWaterFlow);
    void resetMaximumHotWaterFlow();
    void autosizeMaximumHotWaterFlow();
    boost::optional<double> autosizedMaximumHotWaterFlow() const;

    double heatingControlThrottlingRange() const;
    bool isHeatingControlThrottlingRangeDefaulted() const;
    bool setHeatingControlThrottlingRange(double heatingControlThrottlingRange);
    void resetHeatingControlThrottlingRange();

    boost::optional<Schedule> heatingControlTemperatureSchedule() const;
    bool setHeatingControlTemperatureSchedule(Schedule& schedule);
    void resetHeatingControlTemperatureSchedule();

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();
    boost::optional<double> autosizedHeatingDesignCapacity() const;

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

   protected:
    using ImplType = detail::CoilHeatingLowTempRadiantVarFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingLowTempRadiantVarFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantVarFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
