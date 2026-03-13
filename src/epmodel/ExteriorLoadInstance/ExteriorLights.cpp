/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExteriorLoadInstance/ExteriorLights.hpp"
#include "ExteriorLoadInstance/ExteriorLights_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Exterior_Lights_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ExteriorLights::ExteriorLights(const Model& model) : ModelObject(ExteriorLights::iddObjectType(), model) {}

  ExteriorLights::ExteriorLights(std::shared_ptr<detail::ExteriorLights_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ExteriorLights::iddObjectType() {
    return IddObjectType::Exterior_Lights;
  }

  std::vector<std::string> ExteriorLights::controlOptionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Exterior_LightsFields::ControlOption);
  }

  std::vector<std::string> ExteriorLights::validControlOptionValues() {
    return ExteriorLights::controlOptionValues();
  }

  std::string ExteriorLights::controlOption() const {
    return getImpl<detail::ExteriorLights_Impl>()->controlOption();
  }

  bool ExteriorLights::isControlOptionDefaulted() const {
    return getImpl<detail::ExteriorLights_Impl>()->isControlOptionDefaulted();
  }

  double ExteriorLights::multiplier() const {
    return getImpl<detail::ExteriorLights_Impl>()->multiplier();
  }

  bool ExteriorLights::isMultiplierDefaulted() const {
    return getImpl<detail::ExteriorLights_Impl>()->isMultiplierDefaulted();
  }

  std::string ExteriorLights::endUseSubcategory() const {
    return getImpl<detail::ExteriorLights_Impl>()->endUseSubcategory();
  }

  bool ExteriorLights::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::ExteriorLights_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool ExteriorLights::setControlOption(const std::string& controlOption) {
    return getImpl<detail::ExteriorLights_Impl>()->setControlOption(controlOption);
  }

  void ExteriorLights::resetControlOption() {
    getImpl<detail::ExteriorLights_Impl>()->resetControlOption();
  }

  bool ExteriorLights::setMultiplier(double multiplier) {
    return getImpl<detail::ExteriorLights_Impl>()->setMultiplier(multiplier);
  }

  void ExteriorLights::resetMultiplier() {
    getImpl<detail::ExteriorLights_Impl>()->resetMultiplier();
  }

  bool ExteriorLights::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::ExteriorLights_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void ExteriorLights::resetEndUseSubcategory() {
    getImpl<detail::ExteriorLights_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ExteriorLights_Impl::controlOption() const {
      const auto value = getString(openstudio::Exterior_LightsFields::ControlOption, true);
      if (value) {
        return *value;
      }
      return "ScheduleNameOnly";
    }

    bool ExteriorLights_Impl::isControlOptionDefaulted() const {
      return isEmpty(openstudio::Exterior_LightsFields::ControlOption);
    }

    double ExteriorLights_Impl::multiplier() const {
      const auto value = getDouble(openstudio::Exterior_LightsFields::DesignLevel, true);
      if (value) {
        return *value;
      }
      return 1.0;
    }

    bool ExteriorLights_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::Exterior_LightsFields::DesignLevel);
    }

    std::string ExteriorLights_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Exterior_LightsFields::EndUseSubcategory, true);
      if (value) {
        return *value;
      }
      return "General";
    }

    bool ExteriorLights_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Exterior_LightsFields::EndUseSubcategory);
    }

    bool ExteriorLights_Impl::setControlOption(const std::string& controlOption) {
      return setString(openstudio::Exterior_LightsFields::ControlOption, controlOption);
    }

    void ExteriorLights_Impl::resetControlOption() {
      OS_ASSERT(setString(openstudio::Exterior_LightsFields::ControlOption, ""));
    }

    bool ExteriorLights_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::Exterior_LightsFields::DesignLevel, multiplier);
    }

    void ExteriorLights_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::Exterior_LightsFields::DesignLevel, ""));
    }

    bool ExteriorLights_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Exterior_LightsFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void ExteriorLights_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::Exterior_LightsFields::EndUseSubcategory, ""));
    }

    std::vector<std::string> ExteriorLights_Impl::controlOptionValues() const {
      return openstudio::epmodel::ExteriorLights::controlOptionValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
