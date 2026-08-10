/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_LowTemperatureTurnOn_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerLowTemperatureTurnOn::AvailabilityManagerLowTemperatureTurnOn(const Model& model)
    : AvailabilityManager(AvailabilityManagerLowTemperatureTurnOn::iddObjectType(), model) {
    setTemperature(30.0);
  }

  AvailabilityManagerLowTemperatureTurnOn::AvailabilityManagerLowTemperatureTurnOn(
    std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOn_Impl> impl)
    : AvailabilityManager(std::move(impl)) {}

  IddObjectType AvailabilityManagerLowTemperatureTurnOn::iddObjectType() {
    return IddObjectType::AvailabilityManager_LowTemperatureTurnOn;
  }

  boost::optional<Node> AvailabilityManagerLowTemperatureTurnOn::sensorNode() const {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->sensorNode();
  }

  bool AvailabilityManagerLowTemperatureTurnOn::setSensorNode(const Node& node) {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->setSensorNode(node);
  }

  void AvailabilityManagerLowTemperatureTurnOn::resetSensorNode() {
    getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->resetSensorNode();
  }

  double AvailabilityManagerLowTemperatureTurnOn::temperature() const {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->temperature();
  }

  bool AvailabilityManagerLowTemperatureTurnOn::setTemperature(double temperature) {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->setTemperature(temperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<Node> AvailabilityManagerLowTemperatureTurnOn_Impl::sensorNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::SensorNodeName);
    }

    bool AvailabilityManagerLowTemperatureTurnOn_Impl::setSensorNode(const Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return setPointer(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::SensorNodeName, node.handle(), false);
    }

    void AvailabilityManagerLowTemperatureTurnOn_Impl::resetSensorNode() {
      OS_ASSERT(setPointer(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::SensorNodeName, openstudio::Handle(), false));
    }

    double AvailabilityManagerLowTemperatureTurnOn_Impl::temperature() const {
      const auto value = getDouble(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::Temperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerLowTemperatureTurnOn_Impl::setTemperature(double temperature) {
      const bool result = setDouble(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::Temperature, temperature);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
