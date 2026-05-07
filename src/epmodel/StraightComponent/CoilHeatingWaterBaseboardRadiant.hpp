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
    // Schema Alignment Notes:
    // - Status: Partial Parity. epmodel now exposes the canonical heating-coil companion as a transient straight-component view over the
    //   parent baseboard object.
    // - Canonical Counterpart: openstudio::model::CoilHeatingWaterBaseboardRadiant.
    // - Implemented Parity: The water-side ports and the main coil sizing fields are available through the canonical child wrapper shape.
    // - Documented Delta: This child is transient in epmodel because EnergyPlus does not persist a standalone coil object for this family.
    //   The child writes through to the parent `ZoneHVAC:Baseboard:RadiantConvective:Water` object and its linked design object.
    // - Field/Storage Mapping: Water inlet/outlet nodes and the main rated and autosized fields map to the parent EnergyPlus baseboard
    //   object. Design-capacity method, per-floor-area sizing, autosized fraction, and convergence tolerance map to the linked design object.
    // - Remaining Parity Work: Autosized query access still returns `none` on the transient child because epmodel does not yet project
    //   SQL-backed autosized results back through this transient wrapper.
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
