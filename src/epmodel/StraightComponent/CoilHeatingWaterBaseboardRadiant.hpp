/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERBASEBOARDRADIANT_HPP
#define EPMODEL_COILHEATINGWATERBASEBOARDRADIANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingWaterBaseboardRadiant_Impl;
  }

  /** \brief Represents a heating-coil view of a radiant-convective water baseboard.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Heating:Water:Baseboard:Radiant</code> onto \epobject{group-radiative-convective-units.html#zonehvacbaseboardradiantconvectivewater,ZoneHVAC:Baseboard:RadiantConvective:Water} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to parent-owned storage and maps its plant
   * ports to the parent's <code>Inlet Node Name</code> and <code>Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingWaterBaseboardRadiant</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilHeatingWaterBaseboardRadiant : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilHeatingWaterBaseboardRadiant(const Model& model);

    virtual ~CoilHeatingWaterBaseboardRadiant() override = default;
    CoilHeatingWaterBaseboardRadiant(const CoilHeatingWaterBaseboardRadiant& other) = default;
    CoilHeatingWaterBaseboardRadiant(CoilHeatingWaterBaseboardRadiant&& other) = default;
    CoilHeatingWaterBaseboardRadiant& operator=(const CoilHeatingWaterBaseboardRadiant&) = default;
    CoilHeatingWaterBaseboardRadiant& operator=(CoilHeatingWaterBaseboardRadiant&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // This is a transient canonical companion wrapper, not a standalone
    // EnergyPlus object. canonical OpenStudio factors the water baseboard into a
    // parent ZoneHVAC object plus a heating-coil child, but EnergyPlus stores
    // the coil state directly on the parent baseboard object and its linked
    // design object. epmodel preserves the canonical child shape by exposing a
    // transient child that reads and writes that parent-owned storage.
    //
    double ratedAverageWaterTemperature() const;
    bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);

    double ratedWaterMassFlowRate() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);

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

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateAutosized() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    void autosizeMaximumWaterFlowRate();
    boost::optional<double> autosizedMaximumWaterFlowRate() const;

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);

   protected:
    using ImplType = detail::CoilHeatingWaterBaseboardRadiant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWaterBaseboardRadiant(std::shared_ptr<detail::CoilHeatingWaterBaseboardRadiant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
