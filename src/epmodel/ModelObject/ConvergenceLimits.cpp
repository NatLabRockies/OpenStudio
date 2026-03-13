/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ConvergenceLimits.hpp"
#include "ModelObject/ConvergenceLimits_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ConvergenceLimits_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ConvergenceLimits::ConvergenceLimits(const Model& model) : ModelObject(ConvergenceLimits::iddObjectType(), model) {
    // ForwardTranslator emits 1 when this field is blank.
    OS_ASSERT(setMinimumSystemTimestep(1));
  }

  ConvergenceLimits::ConvergenceLimits(std::shared_ptr<detail::ConvergenceLimits_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ConvergenceLimits::iddObjectType() {
    return IddObjectType::ConvergenceLimits;
  }

  boost::optional<int> ConvergenceLimits::minimumSystemTimestep() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->minimumSystemTimestep();
  }

  bool ConvergenceLimits::setMinimumSystemTimestep(int minimumSystemTimestep) {
    return getImpl<detail::ConvergenceLimits_Impl>()->setMinimumSystemTimestep(minimumSystemTimestep);
  }

  void ConvergenceLimits::resetMinimumSystemTimestep() {
    getImpl<detail::ConvergenceLimits_Impl>()->resetMinimumSystemTimestep();
  }

  int ConvergenceLimits::maximumHVACIterations() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->maximumHVACIterations();
  }

  bool ConvergenceLimits::isMaximumHVACIterationsDefaulted() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->isMaximumHVACIterationsDefaulted();
  }

  bool ConvergenceLimits::setMaximumHVACIterations(int maximumHVACIterations) {
    return getImpl<detail::ConvergenceLimits_Impl>()->setMaximumHVACIterations(maximumHVACIterations);
  }

  void ConvergenceLimits::resetMaximumHVACIterations() {
    getImpl<detail::ConvergenceLimits_Impl>()->resetMaximumHVACIterations();
  }

  int ConvergenceLimits::minimumPlantIterations() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->minimumPlantIterations();
  }

  bool ConvergenceLimits::isMinimumPlantIterationsDefaulted() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->isMinimumPlantIterationsDefaulted();
  }

  bool ConvergenceLimits::setMinimumPlantIterations(int minimumPlantIterations) {
    return getImpl<detail::ConvergenceLimits_Impl>()->setMinimumPlantIterations(minimumPlantIterations);
  }

  void ConvergenceLimits::resetMinimumPlantIterations() {
    getImpl<detail::ConvergenceLimits_Impl>()->resetMinimumPlantIterations();
  }

  int ConvergenceLimits::maximumPlantIterations() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->maximumPlantIterations();
  }

  bool ConvergenceLimits::isMaximumPlantIterationsDefaulted() const {
    return getImpl<detail::ConvergenceLimits_Impl>()->isMaximumPlantIterationsDefaulted();
  }

  bool ConvergenceLimits::setMaximumPlantIterations(int maximumPlantIterations) {
    return getImpl<detail::ConvergenceLimits_Impl>()->setMaximumPlantIterations(maximumPlantIterations);
  }

  void ConvergenceLimits::resetMaximumPlantIterations() {
    getImpl<detail::ConvergenceLimits_Impl>()->resetMaximumPlantIterations();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<int> ConvergenceLimits_Impl::minimumSystemTimestep() const {
      return getInt(openstudio::ConvergenceLimitsFields::MinimumSystemTimestep, true);
    }

    bool ConvergenceLimits_Impl::setMinimumSystemTimestep(int minimumSystemTimestep) {
      return setInt(openstudio::ConvergenceLimitsFields::MinimumSystemTimestep, minimumSystemTimestep);
    }

    void ConvergenceLimits_Impl::resetMinimumSystemTimestep() {
      OS_ASSERT(setString(openstudio::ConvergenceLimitsFields::MinimumSystemTimestep, ""));
    }

    int ConvergenceLimits_Impl::maximumHVACIterations() const {
      const auto value = getInt(openstudio::ConvergenceLimitsFields::MaximumHVACIterations, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConvergenceLimits_Impl::isMaximumHVACIterationsDefaulted() const {
      return !getInt(openstudio::ConvergenceLimitsFields::MaximumHVACIterations, false);
    }

    bool ConvergenceLimits_Impl::setMaximumHVACIterations(int maximumHVACIterations) {
      return setInt(openstudio::ConvergenceLimitsFields::MaximumHVACIterations, maximumHVACIterations);
    }

    void ConvergenceLimits_Impl::resetMaximumHVACIterations() {
      OS_ASSERT(setString(openstudio::ConvergenceLimitsFields::MaximumHVACIterations, ""));
    }

    int ConvergenceLimits_Impl::minimumPlantIterations() const {
      const auto value = getInt(openstudio::ConvergenceLimitsFields::MinimumPlantIterations, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConvergenceLimits_Impl::isMinimumPlantIterationsDefaulted() const {
      return !getInt(openstudio::ConvergenceLimitsFields::MinimumPlantIterations, false);
    }

    bool ConvergenceLimits_Impl::setMinimumPlantIterations(int minimumPlantIterations) {
      return setInt(openstudio::ConvergenceLimitsFields::MinimumPlantIterations, minimumPlantIterations);
    }

    void ConvergenceLimits_Impl::resetMinimumPlantIterations() {
      OS_ASSERT(setString(openstudio::ConvergenceLimitsFields::MinimumPlantIterations, ""));
    }

    int ConvergenceLimits_Impl::maximumPlantIterations() const {
      const auto value = getInt(openstudio::ConvergenceLimitsFields::MaximumPlantIterations, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConvergenceLimits_Impl::isMaximumPlantIterationsDefaulted() const {
      return !getInt(openstudio::ConvergenceLimitsFields::MaximumPlantIterations, false);
    }

    bool ConvergenceLimits_Impl::setMaximumPlantIterations(int maximumPlantIterations) {
      return setInt(openstudio::ConvergenceLimitsFields::MaximumPlantIterations, maximumPlantIterations);
    }

    void ConvergenceLimits_Impl::resetMaximumPlantIterations() {
      OS_ASSERT(setString(openstudio::ConvergenceLimitsFields::MaximumPlantIterations, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
