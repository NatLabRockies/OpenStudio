/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_LowTemperatureTurnOff_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerLowTemperatureTurnOff::AvailabilityManagerLowTemperatureTurnOff(const Model& model)
    : ModelObject(AvailabilityManagerLowTemperatureTurnOff::iddObjectType(), model) {
    setTemperature(30.0);
  }

  AvailabilityManagerLowTemperatureTurnOff::AvailabilityManagerLowTemperatureTurnOff(
    std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOff_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AvailabilityManagerLowTemperatureTurnOff::iddObjectType() {
    return IddObjectType::AvailabilityManager_LowTemperatureTurnOff;
  }

  /** @name Temperature Accessors */
  //@{
  double AvailabilityManagerLowTemperatureTurnOff::temperature() const {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOff_Impl>()->temperature();
  }

  bool AvailabilityManagerLowTemperatureTurnOff::setTemperature(double temperature) {
    return getImpl<detail::AvailabilityManagerLowTemperatureTurnOff_Impl>()->setTemperature(temperature);
  }
  //@}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    /** @name Temperature Accessors */
    //@{
    double AvailabilityManagerLowTemperatureTurnOff_Impl::temperature() const {
      const auto value = getDouble(openstudio::AvailabilityManager_LowTemperatureTurnOffFields::Temperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AvailabilityManagerLowTemperatureTurnOff_Impl::setTemperature(double temperature) {
      const bool result = setDouble(openstudio::AvailabilityManager_LowTemperatureTurnOffFields::Temperature, temperature);
      OS_ASSERT(result);
      return result;
    }
    //@}

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
