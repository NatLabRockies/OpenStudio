/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_HPP
#define EPMODEL_SIZINGZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ThermalZone;

namespace detail {
class SizingZone_Impl;
}

class EPMODEL_API SizingZone : public ModelObject
{
 public:
  explicit SizingZone(const Model& model, const ThermalZone& thermalZone);

  virtual ~SizingZone() override = default;
  SizingZone(const SizingZone& other) = default;
  SizingZone(SizingZone&& other) = default;
  SizingZone& operator=(const SizingZone&) = default;
  SizingZone& operator=(SizingZone&&) = default;

  static IddObjectType iddObjectType();

  ThermalZone thermalZone() const;

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model SizingZone DSZAD accessor names/signatures.
  // - Field Mapping: SizingZone DSZAD scalar API delegates to linked
  //   DesignSpecification:ZoneAirDistribution fields through
  //   Sizing:Zone.Design Specification Zone Air Distribution Object Name.
  // - ForwardTranslator Evidence: ForwardTranslateSizingZone writes these API fields to
  //   DesignSpecification:ZoneAirDistribution when any DSZAD value is non-default.
  // - TODO(parity): Replace linked-object indirection if DSZAD receives a dedicated epmodel type.
  double designZoneAirDistributionEffectivenessinCoolingMode() const;
  bool isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const;

  double designZoneAirDistributionEffectivenessinHeatingMode() const;
  bool isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const;

  double designZoneSecondaryRecirculationFraction() const;
  bool isDesignZoneSecondaryRecirculationFractionDefaulted() const;

  double designMinimumZoneVentilationEfficiency() const;
  bool isDesignMinimumZoneVentilationEfficiencyDefaulted() const;

  bool setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode);
  void resetDesignZoneAirDistributionEffectivenessinCoolingMode();

  bool setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode);
  void resetDesignZoneAirDistributionEffectivenessinHeatingMode();

  bool setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction);
  void resetDesignZoneSecondaryRecirculationFraction();

  bool setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency);
  void resetDesignMinimumZoneVentilationEfficiency();

 protected:
  using ImplType = detail::SizingZone_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
