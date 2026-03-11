/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneMixing.hpp"
#include "ZoneMixing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneMixing_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneMixing::ZoneMixing(const Model& model) : ModelObject(ZoneMixing::iddObjectType(), model) {
    OS_ASSERT(setDesignFlowRate(0.0));
  }

  ZoneMixing::ZoneMixing(std::shared_ptr<detail::ZoneMixing_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneMixing::iddObjectType() {
    return IddObjectType::ZoneMixing;
  }

  std::string ZoneMixing::designFlowRateCalculationMethod() const {
    return getImpl<detail::ZoneMixing_Impl>()->designFlowRateCalculationMethod();
  }

  boost::optional<double> ZoneMixing::designFlowRate() const {
    return getImpl<detail::ZoneMixing_Impl>()->designFlowRate();
  }

  bool ZoneMixing::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::ZoneMixing_Impl>()->setDesignFlowRate(designFlowRate);
  }

  void ZoneMixing::resetDesignFlowRate() {
    getImpl<detail::ZoneMixing_Impl>()->resetDesignFlowRate();
  }

  boost::optional<double> ZoneMixing::flowRateperFloorArea() const {
    return getImpl<detail::ZoneMixing_Impl>()->flowRateperFloorArea();
  }

  bool ZoneMixing::setFlowRateperFloorArea(double flowRateperFloorArea) {
    return getImpl<detail::ZoneMixing_Impl>()->setFlowRateperFloorArea(flowRateperFloorArea);
  }

  void ZoneMixing::resetFlowRateperFloorArea() {
    getImpl<detail::ZoneMixing_Impl>()->resetFlowRateperFloorArea();
  }

  boost::optional<double> ZoneMixing::flowRateperPerson() const {
    return getImpl<detail::ZoneMixing_Impl>()->flowRateperPerson();
  }

  bool ZoneMixing::setFlowRateperPerson(double flowRateperPerson) {
    return getImpl<detail::ZoneMixing_Impl>()->setFlowRateperPerson(flowRateperPerson);
  }

  void ZoneMixing::resetFlowRateperPerson() {
    getImpl<detail::ZoneMixing_Impl>()->resetFlowRateperPerson();
  }

  boost::optional<double> ZoneMixing::airChangesperHour() const {
    return getImpl<detail::ZoneMixing_Impl>()->airChangesperHour();
  }

  bool ZoneMixing::setAirChangesperHour(double airChangesperHour) {
    return getImpl<detail::ZoneMixing_Impl>()->setAirChangesperHour(airChangesperHour);
  }

  void ZoneMixing::resetAirChangesperHour() {
    getImpl<detail::ZoneMixing_Impl>()->resetAirChangesperHour();
  }

  boost::optional<double> ZoneMixing::deltaTemperature() const {
    return getImpl<detail::ZoneMixing_Impl>()->deltaTemperature();
  }

  bool ZoneMixing::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ZoneMixing_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  void ZoneMixing::resetDeltaTemperature() {
    getImpl<detail::ZoneMixing_Impl>()->resetDeltaTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneMixing_Impl::designFlowRateCalculationMethod() const {
      const auto value = getString(openstudio::ZoneMixingFields::DesignFlowRateCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> ZoneMixing_Impl::designFlowRate() const {
      return getDouble(openstudio::ZoneMixingFields::DesignFlowRate, true);
    }

    bool ZoneMixing_Impl::setDesignFlowRate(double designFlowRate) {
      bool result = setDouble(openstudio::ZoneMixingFields::DesignFlowRate, designFlowRate);
      if (result) {
        result = setString(openstudio::ZoneMixingFields::DesignFlowRateCalculationMethod, "Flow/Zone");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperFloorArea, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperPerson, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::AirChangesperHour, "");
        OS_ASSERT(result);
      }
      return result;
    }

    void ZoneMixing_Impl::resetDesignFlowRate() {
      const bool result = setString(openstudio::ZoneMixingFields::DesignFlowRate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneMixing_Impl::flowRateperFloorArea() const {
      return getDouble(openstudio::ZoneMixingFields::FlowRateperFloorArea, true);
    }

    bool ZoneMixing_Impl::setFlowRateperFloorArea(double flowRateperFloorArea) {
      bool result = setDouble(openstudio::ZoneMixingFields::FlowRateperFloorArea, flowRateperFloorArea);
      if (result) {
        result = setString(openstudio::ZoneMixingFields::DesignFlowRateCalculationMethod, "Flow/Area");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::DesignFlowRate, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperPerson, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::AirChangesperHour, "");
        OS_ASSERT(result);
      }
      return result;
    }

    void ZoneMixing_Impl::resetFlowRateperFloorArea() {
      const bool result = setString(openstudio::ZoneMixingFields::FlowRateperFloorArea, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneMixing_Impl::flowRateperPerson() const {
      return getDouble(openstudio::ZoneMixingFields::FlowRateperPerson, true);
    }

    bool ZoneMixing_Impl::setFlowRateperPerson(double flowRateperPerson) {
      bool result = setDouble(openstudio::ZoneMixingFields::FlowRateperPerson, flowRateperPerson);
      if (result) {
        result = setString(openstudio::ZoneMixingFields::DesignFlowRateCalculationMethod, "Flow/Person");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::DesignFlowRate, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperFloorArea, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::AirChangesperHour, "");
        OS_ASSERT(result);
      }
      return result;
    }

    void ZoneMixing_Impl::resetFlowRateperPerson() {
      const bool result = setString(openstudio::ZoneMixingFields::FlowRateperPerson, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneMixing_Impl::airChangesperHour() const {
      return getDouble(openstudio::ZoneMixingFields::AirChangesperHour, true);
    }

    bool ZoneMixing_Impl::setAirChangesperHour(double airChangesperHour) {
      bool result = setDouble(openstudio::ZoneMixingFields::AirChangesperHour, airChangesperHour);
      if (result) {
        result = setString(openstudio::ZoneMixingFields::DesignFlowRateCalculationMethod, "AirChanges/Hour");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::DesignFlowRate, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperFloorArea, "");
        OS_ASSERT(result);
        result = setString(openstudio::ZoneMixingFields::FlowRateperPerson, "");
        OS_ASSERT(result);
      }
      return result;
    }

    void ZoneMixing_Impl::resetAirChangesperHour() {
      const bool result = setString(openstudio::ZoneMixingFields::AirChangesperHour, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneMixing_Impl::deltaTemperature() const {
      return getDouble(openstudio::ZoneMixingFields::DeltaTemperature);
    }

    bool ZoneMixing_Impl::setDeltaTemperature(double deltaTemperature) {
      bool result = setDouble(openstudio::ZoneMixingFields::DeltaTemperature, deltaTemperature);
      OS_ASSERT(result);
      result = setString(openstudio::ZoneMixingFields::DeltaTemperatureScheduleName, "");
      OS_ASSERT(result);
      return result;
    }

    void ZoneMixing_Impl::resetDeltaTemperature() {
      const bool result = setString(openstudio::ZoneMixingFields::DeltaTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
