/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionDuctSizing.hpp"
#include "AirflowNetworkDistributionDuctSizing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_DuctSizing_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionDuctSizing::AirflowNetworkDistributionDuctSizing(const Model& model)
    : ModelObject(AirflowNetworkDistributionDuctSizing::iddObjectType(), model) {}

  AirflowNetworkDistributionDuctSizing::AirflowNetworkDistributionDuctSizing(std::shared_ptr<detail::AirflowNetworkDistributionDuctSizing_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionDuctSizing::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_DuctSizing;
  }

  std::vector<std::string> AirflowNetworkDistributionDuctSizing::ductSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingMethod);
  }

  std::string AirflowNetworkDistributionDuctSizing::ductSizingMethod() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->ductSizingMethod();
  }

  bool AirflowNetworkDistributionDuctSizing::isDuctSizingMethodDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->isDuctSizingMethodDefaulted();
  }

  bool AirflowNetworkDistributionDuctSizing::setDuctSizingMethod(const std::string& ductSizingMethod) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setDuctSizingMethod(ductSizingMethod);
  }

  void AirflowNetworkDistributionDuctSizing::resetDuctSizingMethod() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetDuctSizingMethod();
  }

  double AirflowNetworkDistributionDuctSizing::ductSizingFactor() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->ductSizingFactor();
  }

  bool AirflowNetworkDistributionDuctSizing::isDuctSizingFactorDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->isDuctSizingFactorDefaulted();
  }

  bool AirflowNetworkDistributionDuctSizing::setDuctSizingFactor(double ductSizingFactor) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setDuctSizingFactor(ductSizingFactor);
  }

  void AirflowNetworkDistributionDuctSizing::resetDuctSizingFactor() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetDuctSizingFactor();
  }

  double AirflowNetworkDistributionDuctSizing::maximumAirflowVelocity() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->maximumAirflowVelocity();
  }

  bool AirflowNetworkDistributionDuctSizing::isMaximumAirflowVelocityDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->isMaximumAirflowVelocityDefaulted();
  }

  bool AirflowNetworkDistributionDuctSizing::setMaximumAirflowVelocity(double maximumAirflowVelocity) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setMaximumAirflowVelocity(maximumAirflowVelocity);
  }

  void AirflowNetworkDistributionDuctSizing::resetMaximumAirflowVelocity() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetMaximumAirflowVelocity();
  }

  boost::optional<double> AirflowNetworkDistributionDuctSizing::totalPressureLossAcrossSupplyTrunk() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->totalPressureLossAcrossSupplyTrunk();
  }

  bool AirflowNetworkDistributionDuctSizing::setTotalPressureLossAcrossSupplyTrunk(double totalPressureLossAcrossSupplyTrunk) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setTotalPressureLossAcrossSupplyTrunk(totalPressureLossAcrossSupplyTrunk);
  }

  void AirflowNetworkDistributionDuctSizing::resetTotalPressureLossAcrossSupplyTrunk() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetTotalPressureLossAcrossSupplyTrunk();
  }

  boost::optional<double> AirflowNetworkDistributionDuctSizing::totalPressureLossAcrossSupplyBranch() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->totalPressureLossAcrossSupplyBranch();
  }

  bool AirflowNetworkDistributionDuctSizing::setTotalPressureLossAcrossSupplyBranch(double totalPressureLossAcrossSupplyBranch) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setTotalPressureLossAcrossSupplyBranch(totalPressureLossAcrossSupplyBranch);
  }

  void AirflowNetworkDistributionDuctSizing::resetTotalPressureLossAcrossSupplyBranch() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetTotalPressureLossAcrossSupplyBranch();
  }

  boost::optional<double> AirflowNetworkDistributionDuctSizing::totalPressureLossAcrossReturnTrunk() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->totalPressureLossAcrossReturnTrunk();
  }

  bool AirflowNetworkDistributionDuctSizing::setTotalPressureLossAcrossReturnTrunk(double totalPressureLossAcrossReturnTrunk) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setTotalPressureLossAcrossReturnTrunk(totalPressureLossAcrossReturnTrunk);
  }

  void AirflowNetworkDistributionDuctSizing::resetTotalPressureLossAcrossReturnTrunk() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetTotalPressureLossAcrossReturnTrunk();
  }

  boost::optional<double> AirflowNetworkDistributionDuctSizing::totalPressureLossAcrossReturnBranch() const {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->totalPressureLossAcrossReturnBranch();
  }

  bool AirflowNetworkDistributionDuctSizing::setTotalPressureLossAcrossReturnBranch(double totalPressureLossAcrossReturnBranch) {
    return getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->setTotalPressureLossAcrossReturnBranch(totalPressureLossAcrossReturnBranch);
  }

  void AirflowNetworkDistributionDuctSizing::resetTotalPressureLossAcrossReturnBranch() {
    getImpl<detail::AirflowNetworkDistributionDuctSizing_Impl>()->resetTotalPressureLossAcrossReturnBranch();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirflowNetworkDistributionDuctSizing_Impl::ductSizingMethod() const {
      const auto value = getString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::isDuctSizingMethodDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingMethod);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setDuctSizingMethod(const std::string& ductSizingMethod) {
      return setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingMethod, ductSizingMethod);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetDuctSizingMethod() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingMethod, ""));
    }

    double AirflowNetworkDistributionDuctSizing_Impl::ductSizingFactor() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::isDuctSizingFactorDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingFactor);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setDuctSizingFactor(double ductSizingFactor) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingFactor, ductSizingFactor);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetDuctSizingFactor() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::DuctSizingFactor, ""));
    }

    double AirflowNetworkDistributionDuctSizing_Impl::maximumAirflowVelocity() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::MaximumAirflowVelocity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::isMaximumAirflowVelocityDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_DuctSizingFields::MaximumAirflowVelocity);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setMaximumAirflowVelocity(double maximumAirflowVelocity) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::MaximumAirflowVelocity, maximumAirflowVelocity);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetMaximumAirflowVelocity() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::MaximumAirflowVelocity, ""));
    }

    boost::optional<double> AirflowNetworkDistributionDuctSizing_Impl::totalPressureLossAcrossSupplyTrunk() const {
      return getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyTrunk, true);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setTotalPressureLossAcrossSupplyTrunk(double totalPressureLossAcrossSupplyTrunk) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyTrunk,
                       totalPressureLossAcrossSupplyTrunk);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetTotalPressureLossAcrossSupplyTrunk() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyTrunk, ""));
    }

    boost::optional<double> AirflowNetworkDistributionDuctSizing_Impl::totalPressureLossAcrossSupplyBranch() const {
      return getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyBranch, true);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setTotalPressureLossAcrossSupplyBranch(double totalPressureLossAcrossSupplyBranch) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyBranch,
                       totalPressureLossAcrossSupplyBranch);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetTotalPressureLossAcrossSupplyBranch() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossSupplyBranch, ""));
    }

    boost::optional<double> AirflowNetworkDistributionDuctSizing_Impl::totalPressureLossAcrossReturnTrunk() const {
      return getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnTrunk, true);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setTotalPressureLossAcrossReturnTrunk(double totalPressureLossAcrossReturnTrunk) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnTrunk,
                       totalPressureLossAcrossReturnTrunk);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetTotalPressureLossAcrossReturnTrunk() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnTrunk, ""));
    }

    boost::optional<double> AirflowNetworkDistributionDuctSizing_Impl::totalPressureLossAcrossReturnBranch() const {
      return getDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnBranch, true);
    }

    bool AirflowNetworkDistributionDuctSizing_Impl::setTotalPressureLossAcrossReturnBranch(double totalPressureLossAcrossReturnBranch) {
      return setDouble(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnBranch,
                       totalPressureLossAcrossReturnBranch);
    }

    void AirflowNetworkDistributionDuctSizing_Impl::resetTotalPressureLossAcrossReturnBranch() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_DuctSizingFields::TotalPressureLossAcrossReturnBranch, ""));
    }

    std::vector<std::string> AirflowNetworkDistributionDuctSizing_Impl::ductSizingMethodValues() const {
      return openstudio::epmodel::AirflowNetworkDistributionDuctSizing::ductSizingMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
