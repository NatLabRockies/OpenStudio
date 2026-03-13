/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateZoneBaseboardHeat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateZoneBaseboardHeat_Impl() override = default;

      boost::optional<double> zoneHeatingSizingFactor() const;
      bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
      void resetZoneHeatingSizingFactor();

      std::string baseboardHeatingType() const;
      bool isBaseboardHeatingTypeDefaulted() const;
      bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
      void resetBaseboardHeatingType();

      boost::optional<double> baseboardHeatingCapacity() const;
      bool isBaseboardHeatingCapacityDefaulted() const;
      bool isBaseboardHeatingCapacityAutosized() const;
      bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
      void resetBaseboardHeatingCapacity();
      void autosizeBaseboardHeatingCapacity();

      std::string outdoorAirMethod() const;
      bool isOutdoorAirMethodDefaulted() const;
      bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
      void resetOutdoorAirMethod();

      double outdoorAirFlowRateperPerson() const;
      bool isOutdoorAirFlowRateperPersonDefaulted() const;
      bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
      void resetOutdoorAirFlowRateperPerson();

      double outdoorAirFlowRateperZoneFloorArea() const;
      bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
      bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
      void resetOutdoorAirFlowRateperZoneFloorArea();

      double outdoorAirFlowRateperZone() const;
      bool isOutdoorAirFlowRateperZoneDefaulted() const;
      bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
      void resetOutdoorAirFlowRateperZone();

      std::vector<std::string> baseboardHeatingTypeValues() const;
      std::vector<std::string> outdoorAirMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
