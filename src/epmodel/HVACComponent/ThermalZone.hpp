/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALZONE_HPP
#define EPMODEL_THERMALZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class SizingZone;

namespace detail {
  class ThermalZone_Impl;
}

class EPMODEL_API ThermalZone : public ModelObject
{
 public:
  explicit ThermalZone(const Model& model);

  virtual ~ThermalZone() override = default;
  ThermalZone(const ThermalZone& other) = default;
  ThermalZone(ThermalZone&& other) = default;
  ThermalZone& operator=(const ThermalZone&) = default;
  ThermalZone& operator=(ThermalZone&&) = default;

  static IddObjectType iddObjectType();
  bool addToNode(Node& node);
  SizingZone sizingZone() const;

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model ThermalZone useIdealAirLoads/setUseIdealAirLoads names/signatures.
  // - Field Mapping: API delegates to presence of HVACTemplate:Zone:IdealLoadsAirSystem mapped by Zone Name.
  // - ForwardTranslator Evidence: ForwardTranslateThermalZone writes HVACTemplate:Zone:IdealLoadsAirSystem when
  //   ThermalZone::useIdealAirLoads() is true and sets Zone Name to ThermalZone nameString().
  // - TODO(parity): Revisit when epmodel adds explicit ZoneHVACIdealLoadsAirSystem parity path.
  bool useIdealAirLoads() const;
  bool setUseIdealAirLoads(bool useIdealAirLoads);

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model DesignSpecificationOutdoorAir scalar accessor names on ThermalZone wrappers.
  // - Field Mapping: ThermalZone DSOA wrappers delegate to DesignSpecification:OutdoorAir scalar fields through
  //   ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList -> DesignSpecification:OutdoorAir.
  // - ForwardTranslator Evidence: ForwardTranslateThermalZone::getOrCreateThermalZoneDSOA resolves zone DSOA from
  //   Space assignments (single DSOA or DSOA:SpaceList), matching this wrapper mapping path.
  // - TODO(parity): Revisit if explicit zone-level DSOA object ownership is introduced in epmodel.
  std::string outdoorAirMethod() const;
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);

  double outdoorAirFlowperPerson() const;
  bool setOutdoorAirFlowperPerson(double outdoorAirFlowperPerson);

  double outdoorAirFlowperFloorArea() const;
  bool setOutdoorAirFlowperFloorArea(double outdoorAirFlowperFloorArea);

  double outdoorAirFlowRate() const;
  bool setOutdoorAirFlowRate(double outdoorAirFlowRate);

  double outdoorAirFlowAirChangesperHour() const;
  bool setOutdoorAirFlowAirChangesperHour(double outdoorAirFlowAirChangesperHour);

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model ThermalZone daylighting fraction accessor names/signatures.
  // - Field Mapping: API fractions delegate to Daylighting:Controls extensible field Fraction of Lights Controlled by Reference Point.
  // - Field Mapping: Primary/secondary map to extensible group index 0/1, matching ForwardTranslateThermalZone behavior.
  // - API: Daylighting:ReferencePoint coordinate scalars are exposed as ThermalZone primary/secondary daylighting control coordinate wrappers.
  // - Field Mapping: Coordinate wrappers delegate to Daylighting:ReferencePoint X/Y/Z via Daylighting:Controls extensible DaylightingReferencePointName.
  // - TODO(parity): Replace group-index mapping when explicit epmodel DaylightingControl objects are added.
  double fractionofZoneControlledbyPrimaryDaylightingControl() const;
  bool isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted() const;
  bool setFractionofZoneControlledbyPrimaryDaylightingControl(double fractionofZoneControlledbyPrimaryDaylightingControl);
  void resetFractionofZoneControlledbyPrimaryDaylightingControl();

  double fractionofZoneControlledbySecondaryDaylightingControl() const;
  bool isFractionofZoneControlledbySecondaryDaylightingControlDefaulted() const;
  bool setFractionofZoneControlledbySecondaryDaylightingControl(double fractionofZoneControlledbySecondaryDaylightingControl);
  void resetFractionofZoneControlledbySecondaryDaylightingControl();

  double primaryDaylightingControlXCoordinate() const;
  double primaryDaylightingControlYCoordinate() const;
  double primaryDaylightingControlZCoordinate() const;
  bool setPrimaryDaylightingControlXCoordinate(double primaryDaylightingControlXCoordinate);
  bool setPrimaryDaylightingControlYCoordinate(double primaryDaylightingControlYCoordinate);
  bool setPrimaryDaylightingControlZCoordinate(double primaryDaylightingControlZCoordinate);

  double secondaryDaylightingControlXCoordinate() const;
  double secondaryDaylightingControlYCoordinate() const;
  double secondaryDaylightingControlZCoordinate() const;
  bool setSecondaryDaylightingControlXCoordinate(double secondaryDaylightingControlXCoordinate);
  bool setSecondaryDaylightingControlYCoordinate(double secondaryDaylightingControlYCoordinate);
  bool setSecondaryDaylightingControlZCoordinate(double secondaryDaylightingControlZCoordinate);

  // Schema Alignment Notes:
  // - API: Illuminance map scalar wrappers preserve existing OpenStudio IlluminanceMap scalar naming
  //   while exposing them on ThermalZone for epmodel schema-alignment workflow.
  // - Field Mapping: API delegates to Output:IlluminanceMap by ZoneorSpaceName, with forward mapping:
  //   originX -> X Minimum Coordinate, xLength -> X Maximum - X Minimum, originY -> Y Minimum Coordinate,
  //   yLength -> Y Maximum - Y Minimum, originZ -> Z height, and grid points map directly.
  // - ForwardTranslator Evidence: ForwardTranslateThermalZone.cpp writes Output:IlluminanceMap fields from
  //   model::IlluminanceMap using this exact transform.
  // - TODO(parity): Replace wrapper mapping when epmodel adds explicit IlluminanceMap object parity.
  double illuminanceMapOriginXCoordinate() const;
  bool setIlluminanceMapOriginXCoordinate(double illuminanceMapOriginXCoordinate);

  double illuminanceMapOriginYCoordinate() const;
  bool setIlluminanceMapOriginYCoordinate(double illuminanceMapOriginYCoordinate);

  double illuminanceMapOriginZCoordinate() const;
  bool setIlluminanceMapOriginZCoordinate(double illuminanceMapOriginZCoordinate);

  double illuminanceMapXLength() const;
  bool setIlluminanceMapXLength(double illuminanceMapXLength);

  int illuminanceMapNumberofXGridPoints() const;
  bool setIlluminanceMapNumberofXGridPoints(int illuminanceMapNumberofXGridPoints);

  double illuminanceMapYLength() const;
  bool setIlluminanceMapYLength(double illuminanceMapYLength);

  int illuminanceMapNumberofYGridPoints() const;
  bool setIlluminanceMapNumberofYGridPoints(int illuminanceMapNumberofYGridPoints);

 protected:
  using ImplType = detail::ThermalZone_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ThermalZone(std::shared_ptr<detail::ThermalZone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
