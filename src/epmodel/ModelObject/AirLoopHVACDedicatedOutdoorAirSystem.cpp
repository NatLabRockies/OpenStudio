/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_DedicatedOutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirLoopHVACDedicatedOutdoorAirSystem::AirLoopHVACDedicatedOutdoorAirSystem(const Model& model)
    : ModelObject(AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType(), model) {
    // Keep required scalar fields populated for strict non-optional getters.
    OS_ASSERT(setPreheatDesignTemperature(4.5));
    OS_ASSERT(setPreheatDesignHumidityRatio(0.004));
    OS_ASSERT(setPrecoolDesignTemperature(17.5));
    OS_ASSERT(setPrecoolDesignHumidityRatio(0.012));
  }

  AirLoopHVACDedicatedOutdoorAirSystem::AirLoopHVACDedicatedOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem;
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::preheatDesignTemperature() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->preheatDesignTemperature();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPreheatDesignTemperature(double preheatDesignTemperature) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPreheatDesignTemperature(preheatDesignTemperature);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::preheatDesignHumidityRatio() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->preheatDesignHumidityRatio();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPreheatDesignHumidityRatio(preheatDesignHumidityRatio);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::precoolDesignTemperature() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->precoolDesignTemperature();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPrecoolDesignTemperature(double precoolDesignTemperature) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPrecoolDesignTemperature(precoolDesignTemperature);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::precoolDesignHumidityRatio() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->precoolDesignHumidityRatio();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPrecoolDesignHumidityRatio(precoolDesignHumidityRatio);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::preheatDesignTemperature() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPreheatDesignTemperature(double preheatDesignTemperature) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, preheatDesignTemperature);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::preheatDesignHumidityRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, preheatDesignHumidityRatio);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::precoolDesignTemperature() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPrecoolDesignTemperature(double precoolDesignTemperature) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, precoolDesignTemperature);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::precoolDesignHumidityRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, precoolDesignHumidityRatio);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
