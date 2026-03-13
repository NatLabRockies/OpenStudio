/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/HeatBalanceSettingsConductionFiniteDifference.hpp"
#include "ModelObject/HeatBalanceSettingsConductionFiniteDifference_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatBalanceSettings_ConductionFiniteDifference_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HeatBalanceSettingsConductionFiniteDifference::HeatBalanceSettingsConductionFiniteDifference(const Model& model)
    : ModelObject(HeatBalanceSettingsConductionFiniteDifference::iddObjectType(), model) {}

  HeatBalanceSettingsConductionFiniteDifference::HeatBalanceSettingsConductionFiniteDifference(
    std::shared_ptr<detail::HeatBalanceSettingsConductionFiniteDifference_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HeatBalanceSettingsConductionFiniteDifference::iddObjectType() {
    return IddObjectType::HeatBalanceSettings_ConductionFiniteDifference;
  }

  std::vector<std::string> HeatBalanceSettingsConductionFiniteDifference::differenceSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::DifferenceScheme);
  }

  std::string HeatBalanceSettingsConductionFiniteDifference::differenceScheme() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->differenceScheme();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::isDifferenceSchemeDefaulted() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->isDifferenceSchemeDefaulted();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::setDifferenceScheme(const std::string& differenceScheme) {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->setDifferenceScheme(differenceScheme);
  }

  void HeatBalanceSettingsConductionFiniteDifference::resetDifferenceScheme() {
    getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->resetDifferenceScheme();
  }

  double HeatBalanceSettingsConductionFiniteDifference::spaceDiscretizationConstant() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->spaceDiscretizationConstant();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::isSpaceDiscretizationConstantDefaulted() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->isSpaceDiscretizationConstantDefaulted();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::setSpaceDiscretizationConstant(double spaceDiscretizationConstant) {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->setSpaceDiscretizationConstant(spaceDiscretizationConstant);
  }

  void HeatBalanceSettingsConductionFiniteDifference::resetSpaceDiscretizationConstant() {
    getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->resetSpaceDiscretizationConstant();
  }

  double HeatBalanceSettingsConductionFiniteDifference::relaxationFactor() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->relaxationFactor();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::isRelaxationFactorDefaulted() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->isRelaxationFactorDefaulted();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::setRelaxationFactor(double relaxationFactor) {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->setRelaxationFactor(relaxationFactor);
  }

  void HeatBalanceSettingsConductionFiniteDifference::resetRelaxationFactor() {
    getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->resetRelaxationFactor();
  }

  double HeatBalanceSettingsConductionFiniteDifference::insideFaceSurfaceTemperatureConvergenceCriteria() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->insideFaceSurfaceTemperatureConvergenceCriteria();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted() const {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted();
  }

  bool HeatBalanceSettingsConductionFiniteDifference::setInsideFaceSurfaceTemperatureConvergenceCriteria(
    double insideFaceSurfaceTemperatureConvergenceCriteria) {
    return getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->setInsideFaceSurfaceTemperatureConvergenceCriteria(
      insideFaceSurfaceTemperatureConvergenceCriteria);
  }

  void HeatBalanceSettingsConductionFiniteDifference::resetInsideFaceSurfaceTemperatureConvergenceCriteria() {
    getImpl<detail::HeatBalanceSettingsConductionFiniteDifference_Impl>()->resetInsideFaceSurfaceTemperatureConvergenceCriteria();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HeatBalanceSettingsConductionFiniteDifference_Impl::differenceScheme() const {
      const auto value = getString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::DifferenceScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::isDifferenceSchemeDefaulted() const {
      return isEmpty(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::DifferenceScheme);
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::setDifferenceScheme(const std::string& differenceScheme) {
      return setString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::DifferenceScheme, differenceScheme);
    }

    void HeatBalanceSettingsConductionFiniteDifference_Impl::resetDifferenceScheme() {
      OS_ASSERT(setString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::DifferenceScheme, ""));
    }

    double HeatBalanceSettingsConductionFiniteDifference_Impl::spaceDiscretizationConstant() const {
      const auto value = getDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::SpaceDiscretizationConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::isSpaceDiscretizationConstantDefaulted() const {
      return isEmpty(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::SpaceDiscretizationConstant);
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::setSpaceDiscretizationConstant(double spaceDiscretizationConstant) {
      const bool result =
        setDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::SpaceDiscretizationConstant, spaceDiscretizationConstant);
      OS_ASSERT(result);
      return result;
    }

    void HeatBalanceSettingsConductionFiniteDifference_Impl::resetSpaceDiscretizationConstant() {
      OS_ASSERT(setString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::SpaceDiscretizationConstant, ""));
    }

    double HeatBalanceSettingsConductionFiniteDifference_Impl::relaxationFactor() const {
      const auto value = getDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::RelaxationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::isRelaxationFactorDefaulted() const {
      return isEmpty(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::RelaxationFactor);
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::setRelaxationFactor(double relaxationFactor) {
      return setDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::RelaxationFactor, relaxationFactor);
    }

    void HeatBalanceSettingsConductionFiniteDifference_Impl::resetRelaxationFactor() {
      OS_ASSERT(setString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::RelaxationFactor, ""));
    }

    double HeatBalanceSettingsConductionFiniteDifference_Impl::insideFaceSurfaceTemperatureConvergenceCriteria() const {
      const auto value =
        getDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::InsideFaceSurfaceTemperatureConvergenceCriteria, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted() const {
      return isEmpty(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::InsideFaceSurfaceTemperatureConvergenceCriteria);
    }

    bool HeatBalanceSettingsConductionFiniteDifference_Impl::setInsideFaceSurfaceTemperatureConvergenceCriteria(
      double insideFaceSurfaceTemperatureConvergenceCriteria) {
      return setDouble(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::InsideFaceSurfaceTemperatureConvergenceCriteria,
                       insideFaceSurfaceTemperatureConvergenceCriteria);
    }

    void HeatBalanceSettingsConductionFiniteDifference_Impl::resetInsideFaceSurfaceTemperatureConvergenceCriteria() {
      OS_ASSERT(setString(openstudio::HeatBalanceSettings_ConductionFiniteDifferenceFields::InsideFaceSurfaceTemperatureConvergenceCriteria, ""));
    }

    std::vector<std::string> HeatBalanceSettingsConductionFiniteDifference_Impl::differenceSchemeValues() const {
      return openstudio::epmodel::HeatBalanceSettingsConductionFiniteDifference::differenceSchemeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
