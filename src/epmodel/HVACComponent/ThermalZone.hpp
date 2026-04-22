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

  class AirLoopHVAC;
  class HVACComponent;
  class Model;
  class Node;
  class SizingZone;
  class Thermostat;
  class ThermostatSetpointDualSetpoint;
  class ZoneControlContaminantController;
  class ZoneControlHumidistat;

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
    // - Status: Near Parity. ThermalZone preserves the main HVAC topology, sizing, equipment, ideal-loads, and zone-control surfaces needed by downstream
    //   air-side and zone-equipment code, while broader daylighting and some thermostat-abstraction parity remain outstanding.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: `addToNode`, scalar zone fields, `useIdealAirLoads`, thermostat convenience, humidistat/contaminant-controller
    //   relationships, zone equipment list/name helpers, return-air/zone-air helpers, outdoor-air scalars, and daylighting scalars preserve the main
    //   canonical HVAC-facing zone wrapper behavior that is already implemented in epmodel.
    // - Documented Delta: Daylighting-control and illuminance-map object conveniences remain deferred.
    // - Field/Storage Mapping: `addToNode` keeps the EnergyPlus `ZoneHVAC:EquipmentConnections` object aligned with the current demand branch node when the zone is connected to or moved between air-loop branches.
    // - Evidence: `src/model/ThermalZone.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp`, `src/energyplus/ReverseTranslator/ReverseTranslateSizingZone.cpp`, and `src/epmodel/test/IDF_SmallOffice_GTest.cpp` show the canonical and epmodel zone-link behavior being preserved or exercised.
    // - Remaining Parity Work: Close the remaining daylighting and illuminance-map object convenience gaps.
    bool addToNode(Node& node);
    SizingZone sizingZone() const;

    // Schema Alignment Notes:
    // - Status: Partial Parity. The core zone scalar set is aligned, but the canonical wrapper has additional zone object and topology helpers outside this scalar block.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: Multiplier, ceiling-height, volume, and convection-algorithm accessors map cleanly to the canonical zone scalar fields and their default/autocalculation behavior.
    // - Field/Storage Mapping: Each wrapper targets the matching EnergyPlus Zone field (Multiplier, Ceiling Height, Volume, Zone Inside Convection Algorithm, Zone Outside Convection Algorithm).
    // - Evidence: `src/model/ThermalZone.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` confirm the same canonical scalar surface and field mapping.
    // - Remaining Parity Work: Keep extending the zone wrapper with the remaining canonical object-level APIs, not more scalar reinterpretations.
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
    bool setZoneInsideConvectionAlgorithm(boost::optional<std::string> zoneInsideConvectionAlgorithm);
    bool setZoneInsideConvectionAlgorithm(const std::string& zoneInsideConvectionAlgorithm);
    void resetZoneInsideConvectionAlgorithm();

    boost::optional<std::string> zoneOutsideConvectionAlgorithm() const;
    bool setZoneOutsideConvectionAlgorithm(boost::optional<std::string> zoneOutsideConvectionAlgorithm);
    bool setZoneOutsideConvectionAlgorithm(const std::string& zoneOutsideConvectionAlgorithm);
    void resetZoneOutsideConvectionAlgorithm();

    // Schema Alignment Notes:
    // - Status: Near Parity. The ideal-air-loads convenience surface preserves canonical zone-facing behavior, including incompatibility with active air-loop attachment.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: `useIdealAirLoads` and `setUseIdealAirLoads` preserve the canonical boolean-facing convenience API and clear active
    //   air-loop attachment before enabling ideal loads.
    // - Documented Delta: epmodel stores this through a `ZoneHVAC:IdealLoadsAirSystem` object because that is the EnergyPlus schema representation.
    // - Field/Storage Mapping: API delegates to a `ZoneHVACIdealLoadsAirSystem` attached to this zone through the zone equipment topology.
    // - Evidence: `src/epmodel/ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.*` and related epmodel tests exercise the zone attachment path.
    // - Remaining Parity Work: None for the boolean convenience API.
    bool useIdealAirLoads() const;
    bool setUseIdealAirLoads(bool useIdealAirLoads);

    boost::optional<Thermostat> thermostat() const;
    bool setThermostat(const Thermostat& thermostat);
    void resetThermostat();

    boost::optional<ThermostatSetpointDualSetpoint> thermostatSetpointDualSetpoint() const;
    /** \deprecated */
    bool setThermostatSetpointDualSetpoint(const ThermostatSetpointDualSetpoint& thermostat);
    /** \deprecated */
    void resetThermostatSetpointDualSetpoint();

    boost::optional<ZoneControlHumidistat> zoneControlHumidistat() const;
    bool setZoneControlHumidistat(const ZoneControlHumidistat& humidistat);
    void resetZoneControlHumidistat();

    boost::optional<ZoneControlContaminantController> zoneControlContaminantController() const;
    bool setZoneControlContaminantController(const ZoneControlContaminantController& contaminantController);
    void resetZoneControlContaminantController();

    OptionalModelObject returnAirModelObject() const;
    std::vector<ModelObject> returnAirModelObjects() const;
    Node zoneAirNode() const;

    bool addEquipment(const ModelObject& equipment);
    bool removeEquipment(const ModelObject& equipment);
    std::vector<ModelObject> equipment() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<HVACComponent> airLoopHVACTerminal() const;
    std::vector<HVACComponent> airLoopHVACTerminals() const;

    // Schema Alignment Notes:
    // - Status: Near Parity. Thermostat control metadata and the canonical thermostat/humidistat/contaminant relationship helpers are exposed for the
    //   thermostat subclasses epmodel currently models.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: The thermostat control-type and cutout/setpoint scalar wrappers preserve the canonical zone metadata surface, and the
    //   canonical thermostat/humidistat/contaminant-controller convenience APIs expose the currently modeled object relationships.
    // - Documented Delta: epmodel still models only a subset of the broader thermostat family, so unsupported thermostat subclasses remain outside this wrapper.
    // - Field/Storage Mapping: The scalar accessors and thermostat convenience read/write the `ZoneControl:Thermostat` fields targeting this zone
    //   (Zone Name == ThermalZone nameString()), while humidistat and contaminant-controller relationships resolve directly from their owning objects.
    // - Evidence: `src/model/ThermalZone.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` show the matching model surface and translator wiring.
    // - Remaining Parity Work: Extend thermostat-family coverage if epmodel later adds additional canonical thermostat subclasses beyond the currently modeled ones.
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
    // - Status: Partial Parity. Zone outdoor-air accessors are preserved, but the object ownership remains indirect through sizing and space-list relationships.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: The DSOA scalar wrappers preserve the canonical zone-facing outdoor-air values used by current model code.
    // - Documented Delta: epmodel still routes these through `SizingZone` and `DesignSpecification:OutdoorAir:SpaceList` ownership rather than exposing a first-class zone-owned DSOA object.
    // - Field/Storage Mapping: ThermalZone DSOA wrappers delegate to DesignSpecification:OutdoorAir scalar fields through ThermalZone -> Sizing:Zone -> DesignSpecification:OutdoorAir:SpaceList -> DesignSpecification:OutdoorAir.
    // - Evidence: `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` and `src/epmodel/ResourceObject/DesignSpecificationOutdoorAir.cpp` show the current storage path and canonicalization behavior.
    // - Remaining Parity Work: Add direct zone-level DSOA ownership only if epmodel later introduces that object model.
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
    // - Status: Partial Parity. Zone ventilation scalars are preserved, but the canonical zone ventilation object model remains implicit.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: The `ZoneVentilation:DesignFlowRate` scalar bundle is exposed with the same values and default behavior as canonical model code.
    // - Documented Delta: epmodel does not yet surface a dedicated zone-ventilation object wrapper for these fields.
    // - Field/Storage Mapping: ThermalZone methods map to the corresponding EnergyPlus `ZoneVentilation:DesignFlowRate` fields (Design Flow Rate, Flow Rate per Zone Floor Area, Flow Rate per Person, Air Changes per Hour, Ventilation Type, Fan performance coefficients, Temperature thresholds, Wind speed, Density basis).
    // - Evidence: `src/model/ThermalZone.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` confirm the same zone-level ventilation semantics.
    // - Remaining Parity Work: Add a direct zone-ventilation wrapper only if epmodel needs to model that object explicitly.
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
    // - Status: Partial Parity. Daylighting scalars are present, but the canonical daylighting object graph is still compressed into zone-level wrappers.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: The primary/secondary daylighting fractions and point-coordinate wrappers preserve the user-facing zone daylighting surface.
    // - Documented Delta: epmodel still relies on group-indexed extensible data instead of dedicated daylighting-control objects and a richer zone daylighting graph.
    // - Field/Storage Mapping: API fractions delegate to Daylighting:Controls extensible field Fraction of Lights Controlled by Reference Point.
    // - Evidence: `src/model/ThermalZone.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp` show the canonical daylighting behavior this wrapper mirrors.
    // - Remaining Parity Work: Replace the group-indexed daylighting proxy with explicit daylighting-control objects when epmodel supports them.
    double fractionofZoneControlledbyPrimaryDaylightingControl() const;
    bool isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted() const;
    bool setFractionofZoneControlledbyPrimaryDaylightingControl(double fractionofZoneControlledbyPrimaryDaylightingControl);
    void resetFractionofZoneControlledbyPrimaryDaylightingControl();

    double fractionofZoneControlledbySecondaryDaylightingControl() const;
    bool isFractionofZoneControlledbySecondaryDaylightingControlDefaulted() const;
    bool setFractionofZoneControlledbySecondaryDaylightingControl(double fractionofZoneControlledbySecondaryDaylightingControl);
    void resetFractionofZoneControlledbySecondaryDaylightingControl();

    double primaryDaylightingControlXCoordinate() const;
    bool setPrimaryDaylightingControlXCoordinate(double primaryDaylightingControlXCoordinate);

    double primaryDaylightingControlYCoordinate() const;
    bool setPrimaryDaylightingControlYCoordinate(double primaryDaylightingControlYCoordinate);

    double primaryDaylightingControlZCoordinate() const;
    bool setPrimaryDaylightingControlZCoordinate(double primaryDaylightingControlZCoordinate);

    double secondaryDaylightingControlXCoordinate() const;
    bool setSecondaryDaylightingControlXCoordinate(double secondaryDaylightingControlXCoordinate);

    double secondaryDaylightingControlYCoordinate() const;
    bool setSecondaryDaylightingControlYCoordinate(double secondaryDaylightingControlYCoordinate);

    double secondaryDaylightingControlZCoordinate() const;
    bool setSecondaryDaylightingControlZCoordinate(double secondaryDaylightingControlZCoordinate);

    // Schema Alignment Notes:
    // - Status: Partial Parity. Illuminance-map scalars are preserved, but the canonical wrapper still exposes the richer IlluminanceMap object convenience surface.
    // - Canonical Counterpart: openstudio::model::ThermalZone.
    // - Implemented Parity: The illuminance-map origin, extents, and grid-point wrappers preserve the zone-facing mapping used by canonical model code.
    // - Documented Delta: epmodel still represents this through zone-level scalar wrappers instead of a first-class `IlluminanceMap` parity object.
    // - Field/Storage Mapping: API delegates to Output:IlluminanceMap by ZoneorSpaceName, with forward mapping from origin and extents into the EnergyPlus grid and coordinate fields.
    // - Evidence: `src/model/ThermalZone.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateThermalZone.cpp`, and `src/epmodel/test/ThermalZone_GTest.cpp` cover the same illuminance-map transformation.
    // - Remaining Parity Work: Replace the wrapper mapping when epmodel adds explicit `IlluminanceMap` object parity.
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
