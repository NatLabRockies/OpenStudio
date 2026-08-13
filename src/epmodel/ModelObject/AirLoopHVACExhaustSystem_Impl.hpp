/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVACExhaustSystem;
  class AirLoopHVACZoneMixer;
  class FanComponentModel;
  class FanSystemModel;
  class HVACComponent;
  class ThermalZone;
  class ZoneHVACExhaustControl;

  namespace detail {

    class EPMODEL_API AirLoopHVACExhaustSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACExhaustSystem_Impl() override = default;

      boost::optional<AirLoopHVACZoneMixer> zoneMixer() const;
      boost::optional<HVACComponent> fan() const;
      std::vector<ZoneHVACExhaustControl> zoneHVACExhaustControls() const;
      boost::optional<ZoneHVACExhaustControl> addZone(ThermalZone& thermalZone);
      bool removeZoneHVACExhaustControl(ZoneHVACExhaustControl& control);
      std::vector<openstudio::IdfObject> removeZoneHVACExhaustControlObjects(ZoneHVACExhaustControl& control);
      std::vector<openstudio::IdfObject> remove() override;

     private:
      bool initialize(FanSystemModel& fan);
      bool initialize(FanComponentModel& fan);
      bool initializeFan(HVACComponent& fan, const std::string& fanObjectType);
      bool canRemoveZoneHVACExhaustControl(const ZoneHVACExhaustControl& control) const;

      friend class openstudio::epmodel::AirLoopHVACExhaustSystem;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
