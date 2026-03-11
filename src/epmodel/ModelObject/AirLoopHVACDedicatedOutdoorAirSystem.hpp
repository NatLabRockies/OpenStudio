/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACDedicatedOutdoorAirSystem_Impl;
}

class EPMODEL_API AirLoopHVACDedicatedOutdoorAirSystem : public ModelObject
{
 public:
  explicit AirLoopHVACDedicatedOutdoorAirSystem(const Model& model);

  virtual ~AirLoopHVACDedicatedOutdoorAirSystem() override = default;
  AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACDedicatedOutdoorAirSystem& other) = default;
  AirLoopHVACDedicatedOutdoorAirSystem(AirLoopHVACDedicatedOutdoorAirSystem&& other) = default;
  AirLoopHVACDedicatedOutdoorAirSystem& operator=(const AirLoopHVACDedicatedOutdoorAirSystem&) = default;
  AirLoopHVACDedicatedOutdoorAirSystem& operator=(AirLoopHVACDedicatedOutdoorAirSystem&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: preheat/precool design temperature and humidity ratio map directly to same-named E+ fields.
  // - Field Mapping: Outdoor air system, schedule, mixer/splitter names, and extensible air-loop references are relationship-like and excluded.
  // - TODO(parity): Add non-scalar relationship APIs incrementally after scalar saturation.
  double preheatDesignTemperature() const;
  bool setPreheatDesignTemperature(double preheatDesignTemperature);

  double preheatDesignHumidityRatio() const;
  bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

  double precoolDesignTemperature() const;
  bool setPrecoolDesignTemperature(double precoolDesignTemperature);

  double precoolDesignHumidityRatio() const;
  bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

 protected:
  using ImplType = detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACDedicatedOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
