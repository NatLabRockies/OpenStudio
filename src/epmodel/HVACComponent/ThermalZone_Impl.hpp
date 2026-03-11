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

namespace openstudio {
namespace epmodel {

  class ZoneHVACEquipmentConnections;
  class ZoneHVACEquipmentList;
  class SizingZone;
  class Space;
  class DesignSpecificationOutdoorAir;

  namespace detail {

    class EPMODEL_API ThermalZone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalZone_Impl() override = default;

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> zoneHVACEquipmentConnections() const;
      openstudio::epmodel::ZoneHVACEquipmentConnections getZoneHVACEquipmentConnections();

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> zoneHVACEquipmentList() const;

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
      boost::optional<std::string> zoneOutsideConvectionAlgorithm() const;
      bool setZoneInsideConvectionAlgorithm(boost::optional<std::string> zoneInsideConvectionAlgorithm);
      bool setZoneInsideConvectionAlgorithm(const std::string& zoneInsideConvectionAlgorithm);
      void resetZoneInsideConvectionAlgorithm();
      bool setZoneOutsideConvectionAlgorithm(boost::optional<std::string> zoneOutsideConvectionAlgorithm);
      bool setZoneOutsideConvectionAlgorithm(const std::string& zoneOutsideConvectionAlgorithm);
      void resetZoneOutsideConvectionAlgorithm();

      bool useIdealAirLoads() const;
      bool setUseIdealAirLoads(bool useIdealAirLoads);

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
      std::vector<openstudio::WorkspaceObject> hvacTemplateZoneIdealLoadsAirSystemsForZone() const;
      boost::optional<double> daylightingFraction(unsigned referencePointIndex) const;
      bool setDaylightingFraction(unsigned referencePointIndex, double value);
      void resetDaylightingFraction(unsigned referencePointIndex);
      double daylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex) const;
      bool setDaylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex, double value);
      std::vector<openstudio::epmodel::Space> spaces() const;
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> zoneSharedDesignSpecificationOutdoorAir() const;
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> getOrCreateZoneSharedDesignSpecificationOutdoorAir();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
