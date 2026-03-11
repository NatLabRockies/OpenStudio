/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_IMPL_HPP
#define EPMODEL_SIZINGZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ThermalZone;
class ModelObject;
class DesignSpecificationOutdoorAir;
class DesignSpecificationOutdoorAirSpaceList;

namespace detail {

class EPMODEL_API SizingZone_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SizingZone_Impl() override = default;

  boost::optional<openstudio::epmodel::ThermalZone> optionalThermalZone() const;
  openstudio::epmodel::ThermalZone thermalZone() const;

  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> designSpecificationOutdoorAirSpaceList() const;
  bool setDesignSpecificationOutdoorAirSpaceList(
    const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& designSpecificationOutdoorAirSpaceList);

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

  void doCanonicalize(LoadContext& context) override;

 private:
  boost::optional<openstudio::epmodel::ModelObject> designSpecificationZoneAirDistribution() const;
  boost::optional<openstudio::epmodel::ModelObject> getOrCreateDesignSpecificationZoneAirDistribution();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
