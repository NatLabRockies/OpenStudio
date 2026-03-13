/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingParameters.hpp"
#include "SizingParameters_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_Parameters_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SizingParameters::SizingParameters(const Model& model) : ModelObject(SizingParameters::iddObjectType(), model) {}

  SizingParameters::SizingParameters(std::shared_ptr<detail::SizingParameters_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SizingParameters::iddObjectType() {
    return IddObjectType::Sizing_Parameters;
  }

  double SizingParameters::heatingSizingFactor() const {
    return getImpl<detail::SizingParameters_Impl>()->heatingSizingFactor();
  }

  bool SizingParameters::isHeatingSizingFactorDefaulted() const {
    return getImpl<detail::SizingParameters_Impl>()->isHeatingSizingFactorDefaulted();
  }

  bool SizingParameters::setHeatingSizingFactor(double heatingSizingFactor) {
    return getImpl<detail::SizingParameters_Impl>()->setHeatingSizingFactor(heatingSizingFactor);
  }

  void SizingParameters::resetHeatingSizingFactor() {
    getImpl<detail::SizingParameters_Impl>()->resetHeatingSizingFactor();
  }

  double SizingParameters::coolingSizingFactor() const {
    return getImpl<detail::SizingParameters_Impl>()->coolingSizingFactor();
  }

  bool SizingParameters::isCoolingSizingFactorDefaulted() const {
    return getImpl<detail::SizingParameters_Impl>()->isCoolingSizingFactorDefaulted();
  }

  bool SizingParameters::setCoolingSizingFactor(double coolingSizingFactor) {
    return getImpl<detail::SizingParameters_Impl>()->setCoolingSizingFactor(coolingSizingFactor);
  }

  void SizingParameters::resetCoolingSizingFactor() {
    getImpl<detail::SizingParameters_Impl>()->resetCoolingSizingFactor();
  }

  boost::optional<int> SizingParameters::timestepsinAveragingWindow() const {
    return getImpl<detail::SizingParameters_Impl>()->timestepsinAveragingWindow();
  }

  bool SizingParameters::setTimestepsinAveragingWindow(int timestepsinAveragingWindow) {
    return getImpl<detail::SizingParameters_Impl>()->setTimestepsinAveragingWindow(timestepsinAveragingWindow);
  }

  void SizingParameters::resetTimestepsinAveragingWindow() {
    getImpl<detail::SizingParameters_Impl>()->resetTimestepsinAveragingWindow();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SizingParameters_Impl::heatingSizingFactor() const {
      const auto value = getDouble(openstudio::Sizing_ParametersFields::HeatingSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingParameters_Impl::isHeatingSizingFactorDefaulted() const {
      return isEmpty(openstudio::Sizing_ParametersFields::HeatingSizingFactor);
    }

    bool SizingParameters_Impl::setHeatingSizingFactor(double heatingSizingFactor) {
      return setDouble(openstudio::Sizing_ParametersFields::HeatingSizingFactor, heatingSizingFactor);
    }

    void SizingParameters_Impl::resetHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::Sizing_ParametersFields::HeatingSizingFactor, ""));
    }

    double SizingParameters_Impl::coolingSizingFactor() const {
      const auto value = getDouble(openstudio::Sizing_ParametersFields::CoolingSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingParameters_Impl::isCoolingSizingFactorDefaulted() const {
      return isEmpty(openstudio::Sizing_ParametersFields::CoolingSizingFactor);
    }

    bool SizingParameters_Impl::setCoolingSizingFactor(double coolingSizingFactor) {
      return setDouble(openstudio::Sizing_ParametersFields::CoolingSizingFactor, coolingSizingFactor);
    }

    void SizingParameters_Impl::resetCoolingSizingFactor() {
      OS_ASSERT(setString(openstudio::Sizing_ParametersFields::CoolingSizingFactor, ""));
    }

    boost::optional<int> SizingParameters_Impl::timestepsinAveragingWindow() const {
      return getInt(openstudio::Sizing_ParametersFields::TimestepsinAveragingWindow, true);
    }

    bool SizingParameters_Impl::setTimestepsinAveragingWindow(boost::optional<int> timestepsinAveragingWindow) {
      if (timestepsinAveragingWindow) {
        return setInt(openstudio::Sizing_ParametersFields::TimestepsinAveragingWindow, *timestepsinAveragingWindow);
      }
      return setString(openstudio::Sizing_ParametersFields::TimestepsinAveragingWindow, "");
    }

    void SizingParameters_Impl::resetTimestepsinAveragingWindow() {
      OS_ASSERT(setString(openstudio::Sizing_ParametersFields::TimestepsinAveragingWindow, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
