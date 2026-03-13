/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PlantComponentTemperatureSource.hpp"
#include "StraightComponent/PlantComponentTemperatureSource_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/PlantComponent_TemperatureSource_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantComponentTemperatureSource::PlantComponentTemperatureSource(const Model& model)
    : StraightComponent(PlantComponentTemperatureSource::iddObjectType(), model) {
    autosizeDesignVolumeFlowRate();
    OS_ASSERT(setTemperatureSpecificationType("Constant"));
    OS_ASSERT(setSourceTemperature(8.0));
  }

  PlantComponentTemperatureSource::PlantComponentTemperatureSource(std::shared_ptr<detail::PlantComponentTemperatureSource_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType PlantComponentTemperatureSource::iddObjectType() {
    return IddObjectType::PlantComponent_TemperatureSource;
  }

  std::vector<std::string> PlantComponentTemperatureSource::temperatureSpecificationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_TemperatureSourceFields::TemperatureSpecificationType);
  }

  boost::optional<double> PlantComponentTemperatureSource::designVolumeFlowRate() const {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->designVolumeFlowRate();
  }

  bool PlantComponentTemperatureSource::isDesignVolumeFlowRateAutosized() const {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->isDesignVolumeFlowRateAutosized();
  }

  boost::optional<double> PlantComponentTemperatureSource::autosizedDesignVolumeFlowRate() const {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->autosizedDesignVolumeFlowRate();
  }

  bool PlantComponentTemperatureSource::setDesignVolumeFlowRate(double designVolumeFlowRate) {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->setDesignVolumeFlowRate(designVolumeFlowRate);
  }

  void PlantComponentTemperatureSource::autosizeDesignVolumeFlowRate() {
    getImpl<detail::PlantComponentTemperatureSource_Impl>()->autosizeDesignVolumeFlowRate();
  }

  std::string PlantComponentTemperatureSource::temperatureSpecificationType() const {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->temperatureSpecificationType();
  }

  bool PlantComponentTemperatureSource::setTemperatureSpecificationType(const std::string& temperatureSpecificationType) {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->setTemperatureSpecificationType(temperatureSpecificationType);
  }

  boost::optional<double> PlantComponentTemperatureSource::sourceTemperature() const {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->sourceTemperature();
  }

  bool PlantComponentTemperatureSource::setSourceTemperature(double sourceTemperature) {
    return getImpl<detail::PlantComponentTemperatureSource_Impl>()->setSourceTemperature(sourceTemperature);
  }

  void PlantComponentTemperatureSource::resetSourceTemperature() {
    getImpl<detail::PlantComponentTemperatureSource_Impl>()->resetSourceTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned PlantComponentTemperatureSource_Impl::inletPort() const {
      return openstudio::PlantComponent_TemperatureSourceFields::InletNode;
    }

    unsigned PlantComponentTemperatureSource_Impl::outletPort() const {
      return openstudio::PlantComponent_TemperatureSourceFields::OutletNode;
    }

    boost::optional<double> PlantComponentTemperatureSource_Impl::designVolumeFlowRate() const {
      return getDouble(openstudio::PlantComponent_TemperatureSourceFields::DesignVolumeFlowRate, true);
    }

    bool PlantComponentTemperatureSource_Impl::isDesignVolumeFlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantComponent_TemperatureSourceFields::DesignVolumeFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> PlantComponentTemperatureSource_Impl::autosizedDesignVolumeFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool PlantComponentTemperatureSource_Impl::setDesignVolumeFlowRate(double designVolumeFlowRate) {
      return setDouble(openstudio::PlantComponent_TemperatureSourceFields::DesignVolumeFlowRate, designVolumeFlowRate);
    }

    void PlantComponentTemperatureSource_Impl::autosizeDesignVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::PlantComponent_TemperatureSourceFields::DesignVolumeFlowRate, "Autosize"));
    }

    std::string PlantComponentTemperatureSource_Impl::temperatureSpecificationType() const {
      auto value = getString(openstudio::PlantComponent_TemperatureSourceFields::TemperatureSpecificationType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantComponentTemperatureSource_Impl::setTemperatureSpecificationType(const std::string& temperatureSpecificationType) {
      return setString(openstudio::PlantComponent_TemperatureSourceFields::TemperatureSpecificationType, temperatureSpecificationType);
    }

    std::vector<std::string> PlantComponentTemperatureSource_Impl::temperatureSpecificationTypeValues() const {
      return openstudio::epmodel::PlantComponentTemperatureSource::temperatureSpecificationTypeValues();
    }

    boost::optional<double> PlantComponentTemperatureSource_Impl::sourceTemperature() const {
      return getDouble(openstudio::PlantComponent_TemperatureSourceFields::SourceTemperature, true);
    }

    bool PlantComponentTemperatureSource_Impl::setSourceTemperature(double sourceTemperature) {
      return setDouble(openstudio::PlantComponent_TemperatureSourceFields::SourceTemperature, sourceTemperature);
    }

    void PlantComponentTemperatureSource_Impl::resetSourceTemperature() {
      OS_ASSERT(setString(openstudio::PlantComponent_TemperatureSourceFields::SourceTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
