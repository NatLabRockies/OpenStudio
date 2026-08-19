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

  /** \brief Represents a thermal zone and its EnergyPlus zone-level HVAC data.
   *
   * \par EnergyPlus object
   * \epobject{group-thermal-zone-description-geometry.html#zone,Zone}.
   *
   * \par Important behavior
   * Enabling ideal air loads removes active air-loop attachment. Zone-level ventilation, outdoor-air, and daylighting accessors project fields from EnergyPlus companion objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ThermalZone</code>.
   * <b>Not yet available: broad space/geometry and equipment convenience methods, airflow-network and multi-air-loop helpers, and SQL autosized-result methods such as <code>airVolume()</code>, <code>spaces()</code>, <code>airLoopHVACs()</code>, <code>equipmentInCoolingOrder()</code>, <code>autosizedCoolingDesignLoad()</code>, and <code>disconnect()</code>. Added: explicit accessors for EnergyPlus zone-sizing, ventilation, infiltration, daylighting-field, and zone-mixing data.</b>
   *
   * \par Known limitations
   * Some Model companion objects, including daylighting and design-specification objects, are represented through zone-level projections rather than standalone public EPModel wrappers.
   */
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

    bool setSupplyPlenum(const ThermalZone& plenumZone);
    bool setSupplyPlenum(const ThermalZone& plenumZone, unsigned branchIndex);
    void removeSupplyPlenum();
    void removeSupplyPlenum(const AirLoopHVAC& airLoop);
    void removeSupplyPlenum(unsigned branchIndex);
    void removeSupplyPlenum(const AirLoopHVAC& airLoop, unsigned branchIndex);
    bool setReturnPlenum(const ThermalZone& plenumZone);
    bool setReturnPlenum(const ThermalZone& plenumZone, AirLoopHVAC& airLoop);
    void removeReturnPlenum();
    void removeReturnPlenum(AirLoopHVAC& airLoop);

    bool addEquipment(const ModelObject& equipment);
    bool removeEquipment(const ModelObject& equipment);
    std::vector<ModelObject> equipment() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<HVACComponent> airLoopHVACTerminal() const;
    std::vector<HVACComponent> airLoopHVACTerminals() const;

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
    friend class Model;

    explicit ThermalZone(std::shared_ptr<detail::ThermalZone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
