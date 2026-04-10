/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERPANELRADIANT_HPP
#define EPMODEL_COILCOOLINGWATERPANELRADIANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;

namespace detail {
class CoilCoolingWaterPanelRadiant_Impl;
}

class EPMODEL_API CoilCoolingWaterPanelRadiant : public StraightComponent
{
 public:
  explicit CoilCoolingWaterPanelRadiant(const Model& model);

  virtual ~CoilCoolingWaterPanelRadiant() override = default;
  CoilCoolingWaterPanelRadiant(const CoilCoolingWaterPanelRadiant& other) = default;
  CoilCoolingWaterPanelRadiant(CoilCoolingWaterPanelRadiant&& other) = default;
  CoilCoolingWaterPanelRadiant& operator=(const CoilCoolingWaterPanelRadiant&) = default;
  CoilCoolingWaterPanelRadiant& operator=(CoilCoolingWaterPanelRadiant&&) = default;

  static IddObjectType iddObjectType();
  static std::vector<std::string> coolingDesignCapacityMethodValues();
  static std::vector<std::string> controlTypeValues();
  static std::vector<std::string> condensationControlTypeValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. epmodel preserves the canonical coil child as a
  //   transient straight-component view over the parent cooling panel object.
  // - Canonical Counterpart: openstudio::model::CoilCoolingWaterPanelRadiant.
  // - Why This Type Is Slightly Different: canonical OpenStudio factors the
  //   cooling panel family into one parent ZoneHVAC object plus a cooling-coil
  //   child. EnergyPlus does not persist a standalone coil object here; all of
  //   the coil state is flattened onto the parent
  //   `ZoneHVAC:CoolingPanel:RadiantConvective:Water` object. Epmodel keeps
  //   the canonical child shape additively by exposing a transient coil that
  //   reads and writes those parent-owned fields.
  // - Implemented Parity: The canonical scalar, schedule, autosizing, and
  //   water-node APIs are available through this child wrapper.
  // - Documented Delta: Because this child is transient, it is not currently
  //   allowed to place itself independently on a plant loop. `addToNode(...)`
  //   therefore returns `false` instead of pretending there is a persisted
  //   loop component behind the child wrapper.
  // - Field/Storage Mapping: Every field exposed here writes through to the
  //   persisted parent cooling-panel object.

  double ratedInletWaterTemperature() const;
  bool isRatedInletWaterTemperatureDefaulted() const;
  bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
  void resetRatedInletWaterTemperature();

  double ratedInletSpaceTemperature() const;
  bool isRatedInletSpaceTemperatureDefaulted() const;
  bool setRatedInletSpaceTemperature(double ratedInletSpaceTemperature);
  void resetRatedInletSpaceTemperature();

  double ratedWaterMassFlowRate() const;
  bool isRatedWaterMassFlowRateDefaulted() const;
  bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
  void resetRatedWaterMassFlowRate();

  std::string coolingDesignCapacityMethod() const;
  bool isCoolingDesignCapacityMethodDefaulted() const;
  bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
  void resetCoolingDesignCapacityMethod();

  boost::optional<double> coolingDesignCapacity() const;
  bool isCoolingDesignCapacityAutosized() const;
  bool setCoolingDesignCapacity(double coolingDesignCapacity);
  void autosizeCoolingDesignCapacity();
  boost::optional<double> autosizedCoolingDesignCapacity() const;

  double coolingDesignCapacityPerFloorArea() const;
  bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

  double fractionofAutosizedCoolingDesignCapacity() const;
  bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

  boost::optional<double> maximumChilledWaterFlowRate() const;
  bool isMaximumChilledWaterFlowRateAutosized() const;
  bool setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate);
  void autosizeMaximumChilledWaterFlowRate();
  boost::optional<double> autosizedMaximumChilledWaterFlowRate() const;

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  double coolingControlThrottlingRange() const;
  bool isCoolingControlThrottlingRangeDefaulted() const;
  bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
  void resetCoolingControlThrottlingRange();

  boost::optional<Schedule> coolingControlTemperatureSchedule() const;
  bool setCoolingControlTemperatureSchedule(Schedule& coolingControlTemperatureSchedule);
  void resetCoolingControlTemperatureSchedule();

  std::string condensationControlType() const;
  bool isCondensationControlTypeDefaulted() const;
  bool setCondensationControlType(const std::string& condensationControlType);
  void resetCondensationControlType();

  double condensationControlDewpointOffset() const;
  bool isCondensationControlDewpointOffsetDefaulted() const;
  bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
  void resetCondensationControlDewpointOffset();

 protected:
  using ImplType = detail::CoilCoolingWaterPanelRadiant_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingWaterPanelRadiant(std::shared_ptr<detail::CoilCoolingWaterPanelRadiant_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
