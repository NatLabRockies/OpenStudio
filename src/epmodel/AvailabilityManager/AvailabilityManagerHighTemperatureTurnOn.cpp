/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_HighTemperatureTurnOn_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerHighTemperatureTurnOn::AvailabilityManagerHighTemperatureTurnOn(const Model& model)
    : ModelObject(AvailabilityManagerHighTemperatureTurnOn::iddObjectType(), model) {
    setTemperature(30.0);
  }

  AvailabilityManagerHighTemperatureTurnOn::AvailabilityManagerHighTemperatureTurnOn(
    std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOn_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AvailabilityManagerHighTemperatureTurnOn::iddObjectType() {
    return IddObjectType::AvailabilityManager_HighTemperatureTurnOn;
  }

  double AvailabilityManagerHighTemperatureTurnOn::temperature() const {
    return getImpl<detail::AvailabilityManagerHighTemperatureTurnOn_Impl>()->temperature();
  }

  bool AvailabilityManagerHighTemperatureTurnOn::setTemperature(double temperature) {
    return getImpl<detail::AvailabilityManagerHighTemperatureTurnOn_Impl>()->setTemperature(temperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AvailabilityManagerHighTemperatureTurnOn_Impl::temperature() const {
      const auto value = getDouble(openstudio::AvailabilityManager_HighTemperatureTurnOnFields::Temperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerHighTemperatureTurnOn_Impl::setTemperature(double temperature) {
      const bool result = setDouble(openstudio::AvailabilityManager_HighTemperatureTurnOnFields::Temperature, temperature);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
