/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class HVACComponent;
class Model;
class ModelObject;
class Schedule;

namespace detail {
class ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;
}

class EPMODEL_API ZoneHVACCoolingPanelRadiantConvectiveWater : public ZoneHVACComponent
{
 public:
  explicit ZoneHVACCoolingPanelRadiantConvectiveWater(const Model& model);

  virtual ~ZoneHVACCoolingPanelRadiantConvectiveWater() override = default;
  ZoneHVACCoolingPanelRadiantConvectiveWater(const ZoneHVACCoolingPanelRadiantConvectiveWater& other) = default;
  ZoneHVACCoolingPanelRadiantConvectiveWater(ZoneHVACCoolingPanelRadiantConvectiveWater&& other) = default;
  ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(const ZoneHVACCoolingPanelRadiantConvectiveWater&) = default;
  ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(ZoneHVACCoolingPanelRadiantConvectiveWater&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. epmodel preserves the canonical parent-plus-
  //   cooling-coil shape instead of exposing the flattened coil fields
  //   directly on the parent wrapper.
  // - Canonical Counterpart:
  //   openstudio::model::ZoneHVACCoolingPanelRadiantConvectiveWater.
  // - Why This Type Is Slightly Different: canonical OpenStudio exposes a
  //   cooling-coil child object, but EnergyPlus flattens that coil state onto
  //   the parent `ZoneHVAC:CoolingPanel:RadiantConvective:Water` object.
  //   Epmodel preserves the canonical API additively by exposing a transient
  //   `CoilCoolingWaterPanelRadiant` child view over those parent-owned fields.
  // - Implemented Parity: Availability schedule, radiant fractions, zone
  //   attachment, canonical cooling coil access, and canonical child discovery
  //   are all available.
  // - Documented Delta: The transient cooling-coil child can be added through
  //   the canonical child-facing API, but the persisted plant branch row still
  //   stores the parent panel object and high-level loop traversal projects
  //   that row back to the child. The persisted surface rows are recomputed
  //   when the panel is attached to a zone, detached, canonicalized, or when
  //   the people-radiation fraction changes. Later zone surface edits do not
  //   yet automatically resynchronize those rows.
  // - Field/Storage Mapping: Coil scalar fields and water nodes live on the
  //   persisted EnergyPlus parent object. The child coil is a transient view
  //   over that parent storage. Surface membership and per-surface radiant
  //   fractions live in the parent's extensible rows.
  // - Evidence:
  //   `src/model/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp`,
  //   `src/model/ZoneHVACCoolingPanelRadiantConvectiveWater.cpp`,
  //   `src/model/CoilCoolingWaterPanelRadiant.hpp`,
  //   `src/model/CoilCoolingWaterPanelRadiant.cpp`,
  //   `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACCoolingPanelRadiantConvectiveWater.cpp`,
  //   and `src/epmodel/test/ZoneHVACCoolingPanelRadiantConvectiveWater_GTest.cpp`.

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

  double fractionRadiant() const;
  bool setFractionRadiant(double fractionRadiant);

  double fractionofRadiantEnergyIncidentonPeople() const;
  bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

  HVACComponent coolingCoil() const;
  bool setCoolingCoil(HVACComponent& coolingCoil);

  std::vector<ModelObject> children() const;

 protected:
  using ImplType = detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ZoneHVACCoolingPanelRadiantConvectiveWater(std::shared_ptr<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
