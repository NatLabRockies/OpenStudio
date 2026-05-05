/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentTerminalUnit.hpp"
#include "AirflowNetworkDistributionComponentTerminalUnit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_TerminalUnit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionComponentTerminalUnit::AirflowNetworkDistributionComponentTerminalUnit(const Model& model)
    : ModelObject(AirflowNetworkDistributionComponentTerminalUnit::iddObjectType(), model) {}

  AirflowNetworkDistributionComponentTerminalUnit::AirflowNetworkDistributionComponentTerminalUnit(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionComponentTerminalUnit::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Component_TerminalUnit;
  }

  std::vector<std::string> AirflowNetworkDistributionComponentTerminalUnit::terminalUnitObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::TerminalUnitObjectType);
  }

  std::string AirflowNetworkDistributionComponentTerminalUnit::terminalUnitObjectType() const {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->terminalUnitObjectType();
  }

  bool AirflowNetworkDistributionComponentTerminalUnit::setTerminalUnitObjectType(const std::string& terminalUnitObjectType) {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->setTerminalUnitObjectType(terminalUnitObjectType);
  }

  double AirflowNetworkDistributionComponentTerminalUnit::airPathLength() const {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->airPathLength();
  }

  bool AirflowNetworkDistributionComponentTerminalUnit::setAirPathLength(double airPathLength) {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->setAirPathLength(airPathLength);
  }

  double AirflowNetworkDistributionComponentTerminalUnit::airPathHydraulicDiameter() const {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->airPathHydraulicDiameter();
  }

  bool AirflowNetworkDistributionComponentTerminalUnit::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
    return getImpl<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl>()->setAirPathHydraulicDiameter(airPathHydraulicDiameter);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirflowNetworkDistributionComponentTerminalUnit_Impl::terminalUnitObjectType() const {
      const auto value = getString(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::TerminalUnitObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentTerminalUnit_Impl::setTerminalUnitObjectType(const std::string& terminalUnitObjectType) {
      return setString(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::TerminalUnitObjectType, terminalUnitObjectType);
    }

    double AirflowNetworkDistributionComponentTerminalUnit_Impl::airPathLength() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::AirPathLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentTerminalUnit_Impl::setAirPathLength(double airPathLength) {
      return setDouble(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::AirPathLength, airPathLength);
    }

    double AirflowNetworkDistributionComponentTerminalUnit_Impl::airPathHydraulicDiameter() const {
      const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::AirPathHydraulicDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentTerminalUnit_Impl::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
      return setDouble(openstudio::AirflowNetwork_Distribution_Component_TerminalUnitFields::AirPathHydraulicDiameter, airPathHydraulicDiameter);
    }

    std::vector<std::string> AirflowNetworkDistributionComponentTerminalUnit_Impl::terminalUnitObjectTypeValues() const {
      return openstudio::epmodel::AirflowNetworkDistributionComponentTerminalUnit::terminalUnitObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
