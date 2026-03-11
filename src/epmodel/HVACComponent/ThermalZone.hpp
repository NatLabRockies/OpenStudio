/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALZONE_HPP
#define EPMODEL_THERMALZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

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
    // Schema Alignment Notes:
    // - API: `addToNode` keeps the EnergyPlus `ZoneHVAC:EquipmentConnections` object aligned with the current demand branch node when the
    //   zone is connected to or moved between air loop branches.
    // - Field Mapping: `ForwardTranslateThermalZone::translateThermalZone` writes the same `ZoneHVAC:EquipmentConnections` fields (Zone Air
    //   Inlet/Exhaust/Node/Return references plus the Zone Conditioning Equipment List) so this method makes the backing nodes available for
    //   the translator-friendly object.
    bool addToNode(Node& node);
    SizingZone sizingZone() const;

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model ThermalZone scalar accessors for multiplier, ceiling height, volume, and
    //   convection-algorithm values.
    // - Field Mapping: Each wrapper targets the matching EnergyPlus Zone field (Multiplier, Ceiling Height, Volume,
    //   Zone Inside Convection Algorithm, Zone Outside Convection Algorithm).
    // - ForwardTranslator Evidence: ForwardTranslateThermalZone::translateThermalZone writes these Zone fields when the
    //   OpenStudio properties are populated.
    int multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(int multiplier);
    void resetMultiplier();

    boost::optional<double> ceilingHeight() const;
    bool isCeilingHeightDefaulted() const;
    bool isCeilingHeightAutocalculated() const;
    bool setCeilingHeight(boost::optional<double> ceilingHeight);
    bool setCeilingHeight(double ceilingHeight);
    void resetCeilingHeight();
    void autocalculateCeilingHeight();

    boost::optional<double> volume() const;
    bool isVolumeDefaulted() const;
    bool isVolumeAutocalculated() const;
    bool setVolume(boost::optional<double> volume);
    bool setVolume(double volume);
    void resetVolume();
    void autocalculateVolume();

    boost::optional<std::string> zoneInsideConvectionAlgorithm() const;
    boost::optional<std::string> zoneOutsideConvectionAlgorithm() const;
    bool setZoneInsideConvectionAlgorithm(boost::optional<std::string> zoneInsideConvectionAlgorithm);
    bool setZoneInsideConvectionAlgorithm(const std::string& zoneInsideConvectionAlgorithm);
    void resetZoneInsideConvectionAlgorithm();
    bool setZoneOutsideConvectionAlgorithm(boost::optional<std::string> zoneOutsideConvectionAlgorithm);
    bool setZoneOutsideConvectionAlgorithm(const std::string& zoneOutsideConvectionAlgorithm);
    void resetZoneOutsideConvectionAlgorithm();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model ThermalZone useIdealAirLoads/setUseIdealAirLoads names/signatures.
    // - Field Mapping: API delegates to presence of HVACTemplate:Zone:IdealLoadsAirSystem mapped by Zone Name.
    // - ForwardTranslator Evidence: ForwardTranslateThermalZone writes HVACTemplate:Zone:IdealLoadsAirSystem when
    //   ThermalZone::useIdealAirLoads() is true and sets Zone Name to ThermalZone nameString().
    // - TODO(parity): Revisit when epmodel adds explicit ZoneHVACIdealLoadsAirSystem parity path.
    bool useIdealAirLoads() const;
    bool setUseIdealAirLoads(bool useIdealAirLoads);

    // Schema Alignment Notes:
    // - API: Mirror the EnergyPlus ZoneControl:Thermostat scalar fields that describe thermostat control metadata on a ThermalZone.
    // - Field Mapping: These getters/setters read/write the ZoneControl:Thermostat fields targeting this zone (Zone Name == ThermalZone nameString()), matching ForwardTranslateThermalZone behavior.
    // - TODO(parity): Add explicit epmodel ZoneControlThermostat object once scalar coverage or relationships grow.
    static std::vector<std::string> control1ObjectTypeValues();
    std::string control1ObjectType() const;
    bool setControl1ObjectType(const std::string& control1ObjectType);

    static std::vector<std::string> control2ObjectTypeValues();
    boost::optional<std::string> control2ObjectType() const;
    bool setControl2ObjectType(const std::string& control2ObjectType);
    void resetControl2ObjectType();

    static std::vector<std::string> control3ObjectTypeValues();
    boost::optional<std::string> control3ObjectType() const;
    bool setControl3ObjectType(const std::string& control3ObjectType);
    void resetControl3ObjectType();

    static std::vector<std::string> control4ObjectTypeValues();
    boost::optional<std::string> control4ObjectType() const;
    bool setControl4ObjectType(const std::string& control4ObjectType);
    void resetControl4ObjectType();

    double temperatureDifferenceBetweenCutoutAndSetpoint() const;
    bool isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const;
    bool setTemperatureDifferenceBetweenCutoutAndSetpoint(double temperatureDifferenceBetweenCutoutAndSetpoint);
    void resetTemperatureDifferenceBetweenCutoutAndSetpoint();

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
    // - API: Mirror OpenStudio's ZoneVentilationDesignFlowRate scalar accessors so a ThermalZone can work directly with the
    //   EnergyPlus `ZoneVentilation:DesignFlowRate` object that targets this zone.
    // - Field Mapping: ThermalZone methods map to the corresponding EnergyPlus `ZoneVentilation:DesignFlowRate` fields
    //   (Design Flow Rate, Flow Rate per Zone Floor Area, Flow Rate per Person, Air Changes per Hour, Ventilation Type,
    //   Fan performance coefficients, Temperature thresholds, Wind speed, Density basis).
    // - ForwardTranslator Evidence: ForwardTranslateThermalZone will consume these scalars when wiring zone-level ventilation
    //   data into `ZoneVentilation:DesignFlowRate` objects.
    double designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    double flowRateperZoneFloorArea() const;
    bool setFlowRateperZoneFloorArea(double flowRateperZoneFloorArea);

    double flowRateperPerson() const;
    bool setFlowRateperPerson(double flowRateperPerson);

    double airChangesperHour() const;
    bool setAirChangesperHour(double airChangesperHour);

    static std::vector<std::string> ventilationTypeValues();
    std::string ventilationType() const;
    bool setVentilationType(const std::string& ventilationType);

    double fanPressureRise() const;
    bool setFanPressureRise(double fanPressureRise);

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double constantTermCoefficient() const;
    bool setConstantTermCoefficient(double constantTermCoefficient);

    double temperatureTermCoefficient() const;
    bool setTemperatureTermCoefficient(double temperatureTermCoefficient);

    double velocityTermCoefficient() const;
    bool setVelocityTermCoefficient(double velocityTermCoefficient);

    double velocitySquaredTermCoefficient() const;
    bool setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient);

    double minimumIndoorTemperature() const;
    bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

    double maximumIndoorTemperature() const;
    bool setMaximumIndoorTemperature(double maximumIndoorTemperature);

    double deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);

    double minimumOutdoorTemperature() const;
    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

    double maximumOutdoorTemperature() const;
    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

    double maximumWindSpeed() const;
    bool setMaximumWindSpeed(double maximumWindSpeed);

    static std::vector<std::string> densityBasisValues();
    std::string densityBasis() const;
    bool setDensityBasis(const std::string& densityBasis);

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
