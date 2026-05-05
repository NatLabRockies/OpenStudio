/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerElectricEquipment.hpp"
#include "DemandManagerElectricEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManager_ElectricEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  DemandManagerElectricEquipment::DemandManagerElectricEquipment(const Model& model)
    : ModelObject(DemandManagerElectricEquipment::iddObjectType(), model) {}

  DemandManagerElectricEquipment::DemandManagerElectricEquipment(std::shared_ptr<detail::DemandManagerElectricEquipment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType DemandManagerElectricEquipment::iddObjectType() {
    return IddObjectType::DemandManager_ElectricEquipment;
  }

  std::vector<std::string> DemandManagerElectricEquipment::limitControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_ElectricEquipmentFields::LimitControl);
  }

  std::vector<std::string> DemandManagerElectricEquipment::selectionControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::DemandManager_ElectricEquipmentFields::SelectionControl);
  }

  std::string DemandManagerElectricEquipment::limitControl() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->limitControl();
  }

  bool DemandManagerElectricEquipment::setLimitControl(const std::string& limitControl) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setLimitControl(limitControl);
  }

  boost::optional<int> DemandManagerElectricEquipment::minimumLimitDuration() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->minimumLimitDuration();
  }

  bool DemandManagerElectricEquipment::setMinimumLimitDuration(int minimumLimitDuration) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setMinimumLimitDuration(minimumLimitDuration);
  }

  void DemandManagerElectricEquipment::resetMinimumLimitDuration() {
    getImpl<detail::DemandManagerElectricEquipment_Impl>()->resetMinimumLimitDuration();
  }

  boost::optional<double> DemandManagerElectricEquipment::maximumLimitFraction() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->maximumLimitFraction();
  }

  bool DemandManagerElectricEquipment::setMaximumLimitFraction(double maximumLimitFraction) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setMaximumLimitFraction(maximumLimitFraction);
  }

  void DemandManagerElectricEquipment::resetMaximumLimitFraction() {
    getImpl<detail::DemandManagerElectricEquipment_Impl>()->resetMaximumLimitFraction();
  }

  boost::optional<double> DemandManagerElectricEquipment::limitStepChange() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->limitStepChange();
  }

  bool DemandManagerElectricEquipment::setLimitStepChange(double limitStepChange) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setLimitStepChange(limitStepChange);
  }

  void DemandManagerElectricEquipment::resetLimitStepChange() {
    getImpl<detail::DemandManagerElectricEquipment_Impl>()->resetLimitStepChange();
  }

  std::string DemandManagerElectricEquipment::selectionControl() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->selectionControl();
  }

  bool DemandManagerElectricEquipment::setSelectionControl(const std::string& selectionControl) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setSelectionControl(selectionControl);
  }

  boost::optional<int> DemandManagerElectricEquipment::rotationDuration() const {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->rotationDuration();
  }

  bool DemandManagerElectricEquipment::setRotationDuration(int rotationDuration) {
    return getImpl<detail::DemandManagerElectricEquipment_Impl>()->setRotationDuration(rotationDuration);
  }

  void DemandManagerElectricEquipment::resetRotationDuration() {
    getImpl<detail::DemandManagerElectricEquipment_Impl>()->resetRotationDuration();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string DemandManagerElectricEquipment_Impl::limitControl() const {
      const auto value = getString(openstudio::DemandManager_ElectricEquipmentFields::LimitControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerElectricEquipment_Impl::setLimitControl(const std::string& limitControl) {
      return setString(openstudio::DemandManager_ElectricEquipmentFields::LimitControl, limitControl);
    }

    boost::optional<int> DemandManagerElectricEquipment_Impl::minimumLimitDuration() const {
      return getInt(openstudio::DemandManager_ElectricEquipmentFields::MinimumLimitDuration, true);
    }

    bool DemandManagerElectricEquipment_Impl::setMinimumLimitDuration(int minimumLimitDuration) {
      return setInt(openstudio::DemandManager_ElectricEquipmentFields::MinimumLimitDuration, minimumLimitDuration);
    }

    void DemandManagerElectricEquipment_Impl::resetMinimumLimitDuration() {
      OS_ASSERT(setString(openstudio::DemandManager_ElectricEquipmentFields::MinimumLimitDuration, ""));
    }

    boost::optional<double> DemandManagerElectricEquipment_Impl::maximumLimitFraction() const {
      return getDouble(openstudio::DemandManager_ElectricEquipmentFields::MaximumLimitFraction, true);
    }

    bool DemandManagerElectricEquipment_Impl::setMaximumLimitFraction(double maximumLimitFraction) {
      return setDouble(openstudio::DemandManager_ElectricEquipmentFields::MaximumLimitFraction, maximumLimitFraction);
    }

    void DemandManagerElectricEquipment_Impl::resetMaximumLimitFraction() {
      OS_ASSERT(setString(openstudio::DemandManager_ElectricEquipmentFields::MaximumLimitFraction, ""));
    }

    boost::optional<double> DemandManagerElectricEquipment_Impl::limitStepChange() const {
      return getDouble(openstudio::DemandManager_ElectricEquipmentFields::LimitStepChange, true);
    }

    bool DemandManagerElectricEquipment_Impl::setLimitStepChange(double limitStepChange) {
      const bool result = setDouble(openstudio::DemandManager_ElectricEquipmentFields::LimitStepChange, limitStepChange);
      OS_ASSERT(result);
      return result;
    }

    void DemandManagerElectricEquipment_Impl::resetLimitStepChange() {
      OS_ASSERT(setString(openstudio::DemandManager_ElectricEquipmentFields::LimitStepChange, ""));
    }

    std::string DemandManagerElectricEquipment_Impl::selectionControl() const {
      const auto value = getString(openstudio::DemandManager_ElectricEquipmentFields::SelectionControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerElectricEquipment_Impl::setSelectionControl(const std::string& selectionControl) {
      return setString(openstudio::DemandManager_ElectricEquipmentFields::SelectionControl, selectionControl);
    }

    boost::optional<int> DemandManagerElectricEquipment_Impl::rotationDuration() const {
      return getInt(openstudio::DemandManager_ElectricEquipmentFields::RotationDuration, true);
    }

    bool DemandManagerElectricEquipment_Impl::setRotationDuration(int rotationDuration) {
      return setInt(openstudio::DemandManager_ElectricEquipmentFields::RotationDuration, rotationDuration);
    }

    void DemandManagerElectricEquipment_Impl::resetRotationDuration() {
      OS_ASSERT(setString(openstudio::DemandManager_ElectricEquipmentFields::RotationDuration, ""));
    }

    std::vector<std::string> DemandManagerElectricEquipment_Impl::limitControlValues() const {
      return openstudio::epmodel::DemandManagerElectricEquipment::limitControlValues();
    }

    std::vector<std::string> DemandManagerElectricEquipment_Impl::selectionControlValues() const {
      return openstudio::epmodel::DemandManagerElectricEquipment::selectionControlValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
