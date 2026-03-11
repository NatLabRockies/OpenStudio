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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
