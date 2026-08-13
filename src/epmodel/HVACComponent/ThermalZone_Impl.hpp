/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALZONE_IMPL_HPP
#define EPMODEL_THERMALZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>
#include <utilities/idf/WorkspaceObject.hpp>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class HVACComponent;
  class Node;
  class ZoneHVACEquipmentConnections;
  class ZoneHVACEquipmentList;
  class ZoneHVACIdealLoadsAirSystem;
  class SizingZone;
  class Space;
  class DesignSpecificationOutdoorAir;
  class Thermostat;
  class ThermostatSetpointDualSetpoint;
  class ZoneControlContaminantController;
  class ZoneControlHumidistat;

  namespace detail {

    class EPMODEL_API ThermalZone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalZone_Impl() override = default;

      // Schema Alignment Notes:
      // - Field Mapping: Mirrors the EnergyPlus `ZoneHVAC:EquipmentConnections` object that tracks a zone's inlet/return nodes and linked equipment list.
      // - ForwardTranslator Evidence: `ForwardTranslateThermalZone::translateThermalZone` emits the same connections object so this helper keeps the
      //   epmodel representation aligned with the translator output.
      boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> zoneHVACEquipmentConnections() const;
      openstudio::epmodel::ZoneHVACEquipmentConnections getZoneHVACEquipmentConnections();

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> zoneHVACEquipmentList() const;
      openstudio::epmodel::ZoneHVACEquipmentList getZoneHVACEquipmentList();

      bool addToNode(openstudio::epmodel::Node& node);

      boost::optional<openstudio::epmodel::SizingZone> optionalSizingZone() const;
      openstudio::epmodel::SizingZone sizingZone();

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

      std::vector<openstudio::epmodel::ZoneHVACIdealLoadsAirSystem> idealAirLoadsObjects() const;
      bool useIdealAirLoads() const;
      bool setUseIdealAirLoads(bool useIdealAirLoads);

      boost::optional<openstudio::epmodel::Thermostat> thermostat() const;
      bool setThermostat(const openstudio::epmodel::Thermostat& thermostat);
      void resetThermostat();

      boost::optional<openstudio::epmodel::ThermostatSetpointDualSetpoint> thermostatSetpointDualSetpoint() const;
      bool setThermostatSetpointDualSetpoint(const openstudio::epmodel::ThermostatSetpointDualSetpoint& thermostat);
      void resetThermostatSetpointDualSetpoint();

      boost::optional<openstudio::epmodel::ZoneControlHumidistat> zoneControlHumidistat() const;
      bool setZoneControlHumidistat(const openstudio::epmodel::ZoneControlHumidistat& humidistat);
      void resetZoneControlHumidistat();

      boost::optional<openstudio::epmodel::ZoneControlContaminantController> zoneControlContaminantController() const;
      bool setZoneControlContaminantController(const openstudio::epmodel::ZoneControlContaminantController& contaminantController);
      void resetZoneControlContaminantController();

      boost::optional<openstudio::epmodel::ModelObject> returnAirModelObject() const;
      std::vector<openstudio::epmodel::ModelObject> returnAirModelObjects() const;
      openstudio::epmodel::Node zoneAirNode() const;

      bool setReturnPlenum(const openstudio::epmodel::ThermalZone& plenumZone);
      bool setReturnPlenum(const openstudio::epmodel::ThermalZone& plenumZone, openstudio::epmodel::AirLoopHVAC& airLoop);
      void removeReturnPlenum();
      void removeReturnPlenum(openstudio::epmodel::AirLoopHVAC& airLoop);

      bool addEquipment(const openstudio::epmodel::ModelObject& equipment);
      bool removeEquipment(const openstudio::epmodel::ModelObject& equipment);
      std::vector<openstudio::epmodel::ModelObject> equipment() const;
      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
      boost::optional<openstudio::epmodel::HVACComponent> airLoopHVACTerminal() const;
      std::vector<openstudio::epmodel::HVACComponent> airLoopHVACTerminals() const;

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

      void doCanonicalize(LoadContext& context) override;

     private:
      boost::optional<double> daylightingFraction(unsigned referencePointIndex) const;
      bool setDaylightingFraction(unsigned referencePointIndex, double value);
      void resetDaylightingFraction(unsigned referencePointIndex);
      double daylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex) const;
      bool setDaylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex, double value);
      std::vector<openstudio::epmodel::Space> spaces() const;
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> zoneSharedDesignSpecificationOutdoorAir() const;
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> getOrCreateZoneSharedDesignSpecificationOutdoorAir();
      boost::optional<openstudio::WorkspaceObject> zoneControlThermostatObject() const;
      openstudio::WorkspaceObject getOrCreateZoneControlThermostatObject();
      boost::optional<openstudio::WorkspaceObject> zoneVentilationObject() const;
      openstudio::WorkspaceObject getOrCreateZoneVentilationObject();
      void applyZoneVentilationDefaults(openstudio::WorkspaceObject& zoneVentilation);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
