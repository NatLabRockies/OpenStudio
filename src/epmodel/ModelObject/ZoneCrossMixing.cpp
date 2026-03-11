/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneCrossMixing.hpp"
#include "ZoneCrossMixing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneCrossMixing_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ZoneCrossMixing::ZoneCrossMixing(const Model& model) : ModelObject(ZoneCrossMixing::iddObjectType(), model) {}

  ZoneCrossMixing::ZoneCrossMixing(std::shared_ptr<detail::ZoneCrossMixing_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneCrossMixing::iddObjectType() {
    return IddObjectType::ZoneCrossMixing;
  }

  std::vector<std::string> ZoneCrossMixing::designFlowRateCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneCrossMixingFields::DesignFlowRateCalculationMethod);
  }

  std::string ZoneCrossMixing::designFlowRateCalculationMethod() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->designFlowRateCalculationMethod();
  }

  bool ZoneCrossMixing::isDesignFlowRateCalculationMethodDefaulted() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->isDesignFlowRateCalculationMethodDefaulted();
  }

  bool ZoneCrossMixing::setDesignFlowRateCalculationMethod(const std::string& designFlowRateCalculationMethod) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setDesignFlowRateCalculationMethod(designFlowRateCalculationMethod);
  }

  void ZoneCrossMixing::resetDesignFlowRateCalculationMethod() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetDesignFlowRateCalculationMethod();
  }

  boost::optional<double> ZoneCrossMixing::designFlowRate() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->designFlowRate();
  }

  bool ZoneCrossMixing::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setDesignFlowRate(designFlowRate);
  }

  void ZoneCrossMixing::resetDesignFlowRate() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetDesignFlowRate();
  }

  boost::optional<double> ZoneCrossMixing::flowRateperFloorArea() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->flowRateperFloorArea();
  }

  bool ZoneCrossMixing::setFlowRateperFloorArea(double flowRateperFloorArea) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setFlowRateperFloorArea(flowRateperFloorArea);
  }

  void ZoneCrossMixing::resetFlowRateperFloorArea() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetFlowRateperFloorArea();
  }

  boost::optional<double> ZoneCrossMixing::flowRateperPerson() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->flowRateperPerson();
  }

  bool ZoneCrossMixing::setFlowRateperPerson(double flowRateperPerson) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setFlowRateperPerson(flowRateperPerson);
  }

  void ZoneCrossMixing::resetFlowRateperPerson() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetFlowRateperPerson();
  }

  boost::optional<double> ZoneCrossMixing::airChangesperHour() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->airChangesperHour();
  }

  bool ZoneCrossMixing::setAirChangesperHour(double airChangesperHour) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setAirChangesperHour(airChangesperHour);
  }

  void ZoneCrossMixing::resetAirChangesperHour() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetAirChangesperHour();
  }

  double ZoneCrossMixing::deltaTemperature() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->deltaTemperature();
  }

  bool ZoneCrossMixing::isDeltaTemperatureDefaulted() const {
    return getImpl<detail::ZoneCrossMixing_Impl>()->isDeltaTemperatureDefaulted();
  }

  bool ZoneCrossMixing::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ZoneCrossMixing_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  void ZoneCrossMixing::resetDeltaTemperature() {
    getImpl<detail::ZoneCrossMixing_Impl>()->resetDeltaTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneCrossMixing_Impl::designFlowRateCalculationMethod() const {
      if (auto value = getString(openstudio::ZoneCrossMixingFields::DesignFlowRateCalculationMethod, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Flow/Zone";
    }

    bool ZoneCrossMixing_Impl::isDesignFlowRateCalculationMethodDefaulted() const {
      return isEmpty(openstudio::ZoneCrossMixingFields::DesignFlowRateCalculationMethod);
    }

    bool ZoneCrossMixing_Impl::setDesignFlowRateCalculationMethod(const std::string& designFlowRateCalculationMethod) {
      return setString(openstudio::ZoneCrossMixingFields::DesignFlowRateCalculationMethod, designFlowRateCalculationMethod);
    }

    void ZoneCrossMixing_Impl::resetDesignFlowRateCalculationMethod() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::DesignFlowRateCalculationMethod, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneCrossMixing_Impl::designFlowRate() const {
      return getDouble(openstudio::ZoneCrossMixingFields::DesignFlowRate, true);
    }

    bool ZoneCrossMixing_Impl::setDesignFlowRate(double designFlowRate) {
      return setDouble(openstudio::ZoneCrossMixingFields::DesignFlowRate, designFlowRate);
    }

    void ZoneCrossMixing_Impl::resetDesignFlowRate() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::DesignFlowRate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneCrossMixing_Impl::flowRateperFloorArea() const {
      return getDouble(openstudio::ZoneCrossMixingFields::FlowRateperFloorArea, true);
    }

    bool ZoneCrossMixing_Impl::setFlowRateperFloorArea(double flowRateperFloorArea) {
      return setDouble(openstudio::ZoneCrossMixingFields::FlowRateperFloorArea, flowRateperFloorArea);
    }

    void ZoneCrossMixing_Impl::resetFlowRateperFloorArea() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::FlowRateperFloorArea, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneCrossMixing_Impl::flowRateperPerson() const {
      return getDouble(openstudio::ZoneCrossMixingFields::FlowRateperPerson, true);
    }

    bool ZoneCrossMixing_Impl::setFlowRateperPerson(double flowRateperPerson) {
      return setDouble(openstudio::ZoneCrossMixingFields::FlowRateperPerson, flowRateperPerson);
    }

    void ZoneCrossMixing_Impl::resetFlowRateperPerson() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::FlowRateperPerson, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneCrossMixing_Impl::airChangesperHour() const {
      return getDouble(openstudio::ZoneCrossMixingFields::AirChangesperHour, true);
    }

    bool ZoneCrossMixing_Impl::setAirChangesperHour(double airChangesperHour) {
      return setDouble(openstudio::ZoneCrossMixingFields::AirChangesperHour, airChangesperHour);
    }

    void ZoneCrossMixing_Impl::resetAirChangesperHour() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::AirChangesperHour, "");
      OS_ASSERT(result);
    }

    double ZoneCrossMixing_Impl::deltaTemperature() const {
      if (auto value = getDouble(openstudio::ZoneCrossMixingFields::DeltaTemperature, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneCrossMixing_Impl::isDeltaTemperatureDefaulted() const {
      return isEmpty(openstudio::ZoneCrossMixingFields::DeltaTemperature);
    }

    bool ZoneCrossMixing_Impl::setDeltaTemperature(double deltaTemperature) {
      return setDouble(openstudio::ZoneCrossMixingFields::DeltaTemperature, deltaTemperature);
    }

    void ZoneCrossMixing_Impl::resetDeltaTemperature() {
      const bool result = setString(openstudio::ZoneCrossMixingFields::DeltaTemperature, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> ZoneCrossMixing_Impl::designFlowRateCalculationMethodValues() const {
      return openstudio::epmodel::ZoneCrossMixing::designFlowRateCalculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
