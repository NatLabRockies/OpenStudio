/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERBASEBOARD_HPP
#define EPMODEL_COILHEATINGWATERBASEBOARD_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingWaterBaseboard_Impl;
  }

  /** \brief Represents a heating-coil view of a convective water baseboard.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Heating:Water:Baseboard</code> onto \epobject{group-radiative-convective-units.html#zonehvacbaseboardconvectivewater,ZoneHVAC:Baseboard:Convective:Water} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to parent-owned storage and maps its plant
   * ports to the parent's <code>Water Inlet Node Name</code> and <code>Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingWaterBaseboard</code>.
   * <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component.
   * <b>Not yet available:</b> the Model <code>inletPort()</code> and <code>outletPort()</code> convenience methods.
   *
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilHeatingWaterBaseboard : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilHeatingWaterBaseboard(const Model& model);

    virtual ~CoilHeatingWaterBaseboard() override = default;
    CoilHeatingWaterBaseboard(const CoilHeatingWaterBaseboard& other) = default;
    CoilHeatingWaterBaseboard(CoilHeatingWaterBaseboard&& other) = default;
    CoilHeatingWaterBaseboard& operator=(const CoilHeatingWaterBaseboard&) = default;
    CoilHeatingWaterBaseboard& operator=(CoilHeatingWaterBaseboard&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // This is a transient canonical companion wrapper, not a standalone
    // EnergyPlus object. canonical OpenStudio factors the convective water
    // baseboard into a parent ZoneHVAC object plus a heating-coil child, but
    // EnergyPlus stores the coil fields directly on the parent
    // `ZoneHVAC:Baseboard:Convective:Water` object. epmodel preserves the
    // canonical child shape by exposing a transient straight-component view that
    // reads and writes that parent-owned storage.
    //
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

    boost::optional<double> uFactorTimesAreaValue() const;
    bool isUFactorTimesAreaValueDefaulted() const;
    bool isUFactorTimesAreaValueAutosized() const;
    bool setUFactorTimesAreaValue(double uFactorTimesAreaValue);
    void resetUFactorTimesAreaValue();
    void autosizeUFactorTimesAreaValue();
    boost::optional<double> autosizedUFactorTimesAreaValue() const;

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateDefaulted() const;
    bool isMaximumWaterFlowRateAutosized() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    void resetMaximumWaterFlowRate();
    void autosizeMaximumWaterFlowRate();
    boost::optional<double> autosizedMaximumWaterFlowRate() const;

    double convergenceTolerance() const;
    bool isConvergenceToleranceDefaulted() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    void resetConvergenceTolerance();

   protected:
    using ImplType = detail::CoilHeatingWaterBaseboard_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWaterBaseboard(std::shared_ptr<detail::CoilHeatingWaterBaseboard_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
