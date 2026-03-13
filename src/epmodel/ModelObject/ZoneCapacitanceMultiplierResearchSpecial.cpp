/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneCapacitanceMultiplierResearchSpecial.hpp"
#include "ZoneCapacitanceMultiplierResearchSpecial_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneCapacitanceMultiplier_ResearchSpecial_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneCapacitanceMultiplierResearchSpecial::ZoneCapacitanceMultiplierResearchSpecial(const Model& model)
    : ModelObject(ZoneCapacitanceMultiplierResearchSpecial::iddObjectType(), model) {}

  ZoneCapacitanceMultiplierResearchSpecial::ZoneCapacitanceMultiplierResearchSpecial(
    std::shared_ptr<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneCapacitanceMultiplierResearchSpecial::iddObjectType() {
    return IddObjectType::ZoneCapacitanceMultiplier_ResearchSpecial;
  }

  double ZoneCapacitanceMultiplierResearchSpecial::temperatureCapacityMultiplier() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->temperatureCapacityMultiplier();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::isTemperatureCapacityMultiplierDefaulted() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->isTemperatureCapacityMultiplierDefaulted();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::setTemperatureCapacityMultiplier(double temperatureCapacityMultiplier) {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->setTemperatureCapacityMultiplier(temperatureCapacityMultiplier);
  }

  void ZoneCapacitanceMultiplierResearchSpecial::resetTemperatureCapacityMultiplier() {
    getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->resetTemperatureCapacityMultiplier();
  }

  double ZoneCapacitanceMultiplierResearchSpecial::humidityCapacityMultiplier() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->humidityCapacityMultiplier();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::isHumidityCapacityMultiplierDefaulted() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->isHumidityCapacityMultiplierDefaulted();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::setHumidityCapacityMultiplier(double humidityCapacityMultiplier) {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->setHumidityCapacityMultiplier(humidityCapacityMultiplier);
  }

  void ZoneCapacitanceMultiplierResearchSpecial::resetHumidityCapacityMultiplier() {
    getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->resetHumidityCapacityMultiplier();
  }

  double ZoneCapacitanceMultiplierResearchSpecial::carbonDioxideCapacityMultiplier() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->carbonDioxideCapacityMultiplier();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::isCarbonDioxideCapacityMultiplierDefaulted() const {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->isCarbonDioxideCapacityMultiplierDefaulted();
  }

  bool ZoneCapacitanceMultiplierResearchSpecial::setCarbonDioxideCapacityMultiplier(double carbonDioxideCapacityMultiplier) {
    return getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->setCarbonDioxideCapacityMultiplier(carbonDioxideCapacityMultiplier);
  }

  void ZoneCapacitanceMultiplierResearchSpecial::resetCarbonDioxideCapacityMultiplier() {
    getImpl<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl>()->resetCarbonDioxideCapacityMultiplier();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneCapacitanceMultiplierResearchSpecial_Impl::temperatureCapacityMultiplier() const {
      const auto value = getDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::TemperatureCapacityMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::isTemperatureCapacityMultiplierDefaulted() const {
      return isEmpty(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::TemperatureCapacityMultiplier);
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::setTemperatureCapacityMultiplier(double temperatureCapacityMultiplier) {
      const bool result =
        setDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::TemperatureCapacityMultiplier, temperatureCapacityMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void ZoneCapacitanceMultiplierResearchSpecial_Impl::resetTemperatureCapacityMultiplier() {
      OS_ASSERT(setString(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::TemperatureCapacityMultiplier, ""));
    }

    double ZoneCapacitanceMultiplierResearchSpecial_Impl::humidityCapacityMultiplier() const {
      const auto value = getDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::HumidityCapacityMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::isHumidityCapacityMultiplierDefaulted() const {
      return isEmpty(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::HumidityCapacityMultiplier);
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::setHumidityCapacityMultiplier(double humidityCapacityMultiplier) {
      const bool result =
        setDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::HumidityCapacityMultiplier, humidityCapacityMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void ZoneCapacitanceMultiplierResearchSpecial_Impl::resetHumidityCapacityMultiplier() {
      OS_ASSERT(setString(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::HumidityCapacityMultiplier, ""));
    }

    double ZoneCapacitanceMultiplierResearchSpecial_Impl::carbonDioxideCapacityMultiplier() const {
      const auto value = getDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::CarbonDioxideCapacityMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::isCarbonDioxideCapacityMultiplierDefaulted() const {
      return isEmpty(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::CarbonDioxideCapacityMultiplier);
    }

    bool ZoneCapacitanceMultiplierResearchSpecial_Impl::setCarbonDioxideCapacityMultiplier(double carbonDioxideCapacityMultiplier) {
      const bool result =
        setDouble(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::CarbonDioxideCapacityMultiplier, carbonDioxideCapacityMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void ZoneCapacitanceMultiplierResearchSpecial_Impl::resetCarbonDioxideCapacityMultiplier() {
      OS_ASSERT(setString(openstudio::ZoneCapacitanceMultiplier_ResearchSpecialFields::CarbonDioxideCapacityMultiplier, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
