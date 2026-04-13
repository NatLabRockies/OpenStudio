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

class EPMODEL_API CoilHeatingWaterBaseboard : public StraightComponent
{
 public:
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
  // Schema Alignment Notes:
  // - Status: Partial Parity. epmodel now exposes the canonical heating-coil companion as a transient straight-component view over the
  //   parent baseboard object.
  // - Canonical Counterpart: openstudio::model::CoilHeatingWaterBaseboard.
  // - Implemented Parity: The water-side ports, sizing fields, defaults, autosize helpers, and loop-placement behavior are available
  //   through the canonical child wrapper surface.
  // - Documented Delta: This child is transient in epmodel because EnergyPlus does not persist a standalone coil object for this family.
  //   The child writes through to the parent `ZoneHVAC:Baseboard:Convective:Water` object and its water-node fields.
  // - Field/Storage Mapping: All coil fields map directly to the parent EnergyPlus baseboard object. The transient child is a canonical
  //   view over those parent-owned fields rather than a separate persisted object.
  // - Remaining Parity Work: Autosized query access still returns `none` on this transient child because epmodel does not yet project
  //   SQL-backed autosized results back through this wrapper.
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
