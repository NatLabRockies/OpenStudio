/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Timestep.hpp"
#include "Timestep_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/OS_Timestep_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Timestep::Timestep(const Model& model) : ModelObject(Timestep::iddObjectType(), model) {
    OS_ASSERT(setNumberOfTimestepsPerHour(6));
  }

  Timestep::Timestep(std::shared_ptr<detail::Timestep_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Timestep::iddObjectType() {
    return IddObjectType::OS_Timestep;
  }

  int Timestep::numberOfTimestepsPerHour() const {
    return getImpl<detail::Timestep_Impl>()->numberOfTimestepsPerHour();
  }

  bool Timestep::isNumberOfTimestepsPerHourDefaulted() const {
    return getImpl<detail::Timestep_Impl>()->isNumberOfTimestepsPerHourDefaulted();
  }

  bool Timestep::setNumberOfTimestepsPerHour(int numberOfTimestepsPerHour) {
    return getImpl<detail::Timestep_Impl>()->setNumberOfTimestepsPerHour(numberOfTimestepsPerHour);
  }

  void Timestep::resetNumberOfTimestepsPerHour() {
    getImpl<detail::Timestep_Impl>()->resetNumberOfTimestepsPerHour();
  }

  namespace detail {

    int Timestep_Impl::numberOfTimestepsPerHour() const {
      const auto value = getInt(openstudio::OS_TimestepFields::NumberofTimestepsperHour, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Timestep_Impl::isNumberOfTimestepsPerHourDefaulted() const {
      return isEmpty(openstudio::OS_TimestepFields::NumberofTimestepsperHour);
    }

    bool Timestep_Impl::setNumberOfTimestepsPerHour(int numberOfTimestepsPerHour) {
      return setInt(openstudio::OS_TimestepFields::NumberofTimestepsperHour, numberOfTimestepsPerHour);
    }

    void Timestep_Impl::resetNumberOfTimestepsPerHour() {
      const bool result = setString(openstudio::OS_TimestepFields::NumberofTimestepsperHour, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
