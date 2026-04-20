/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ZoneRefrigerationDoorMixing.hpp"
#include "scaffolds/ZoneRefrigerationDoorMixing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneRefrigerationDoorMixing_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneRefrigerationDoorMixing::ZoneRefrigerationDoorMixing(const Model& model) : ModelObject(ZoneRefrigerationDoorMixing::iddObjectType(), model) {}

  ZoneRefrigerationDoorMixing::ZoneRefrigerationDoorMixing(std::shared_ptr<detail::ZoneRefrigerationDoorMixing_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneRefrigerationDoorMixing::iddObjectType() {
    return IddObjectType::ZoneRefrigerationDoorMixing;
  }

  std::vector<std::string> ZoneRefrigerationDoorMixing::doorProtectionTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneRefrigerationDoorMixingFields::DoorProtectionType);
  }

  double ZoneRefrigerationDoorMixing::doorHeight() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->doorHeight();
  }

  bool ZoneRefrigerationDoorMixing::isDoorHeightDefaulted() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->isDoorHeightDefaulted();
  }

  bool ZoneRefrigerationDoorMixing::setDoorHeight(double doorHeight) {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->setDoorHeight(doorHeight);
  }

  void ZoneRefrigerationDoorMixing::resetDoorHeight() {
    getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->resetDoorHeight();
  }

  double ZoneRefrigerationDoorMixing::doorArea() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->doorArea();
  }

  bool ZoneRefrigerationDoorMixing::isDoorAreaDefaulted() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->isDoorAreaDefaulted();
  }

  bool ZoneRefrigerationDoorMixing::setDoorArea(double doorArea) {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->setDoorArea(doorArea);
  }

  void ZoneRefrigerationDoorMixing::resetDoorArea() {
    getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->resetDoorArea();
  }

  std::string ZoneRefrigerationDoorMixing::doorProtectionType() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->doorProtectionType();
  }

  bool ZoneRefrigerationDoorMixing::isDoorProtectionTypeDefaulted() const {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->isDoorProtectionTypeDefaulted();
  }

  bool ZoneRefrigerationDoorMixing::setDoorProtectionType(const std::string& doorProtectionType) {
    return getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->setDoorProtectionType(doorProtectionType);
  }

  void ZoneRefrigerationDoorMixing::resetDoorProtectionType() {
    getImpl<detail::ZoneRefrigerationDoorMixing_Impl>()->resetDoorProtectionType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneRefrigerationDoorMixing_Impl::doorHeight() const {
      if (auto value = getDouble(openstudio::ZoneRefrigerationDoorMixingFields::DoorHeight, true)) {
        return *value;
      }
      return 3.0;
    }

    bool ZoneRefrigerationDoorMixing_Impl::isDoorHeightDefaulted() const {
      return isEmpty(openstudio::ZoneRefrigerationDoorMixingFields::DoorHeight);
    }

    bool ZoneRefrigerationDoorMixing_Impl::setDoorHeight(double doorHeight) {
      return setDouble(openstudio::ZoneRefrigerationDoorMixingFields::DoorHeight, doorHeight);
    }

    void ZoneRefrigerationDoorMixing_Impl::resetDoorHeight() {
      OS_ASSERT(setString(openstudio::ZoneRefrigerationDoorMixingFields::DoorHeight, ""));
    }

    double ZoneRefrigerationDoorMixing_Impl::doorArea() const {
      if (auto value = getDouble(openstudio::ZoneRefrigerationDoorMixingFields::DoorArea, true)) {
        return *value;
      }
      return 9.0;
    }

    bool ZoneRefrigerationDoorMixing_Impl::isDoorAreaDefaulted() const {
      return isEmpty(openstudio::ZoneRefrigerationDoorMixingFields::DoorArea);
    }

    bool ZoneRefrigerationDoorMixing_Impl::setDoorArea(double doorArea) {
      return setDouble(openstudio::ZoneRefrigerationDoorMixingFields::DoorArea, doorArea);
    }

    void ZoneRefrigerationDoorMixing_Impl::resetDoorArea() {
      OS_ASSERT(setString(openstudio::ZoneRefrigerationDoorMixingFields::DoorArea, ""));
    }

    std::string ZoneRefrigerationDoorMixing_Impl::doorProtectionType() const {
      if (auto value = getString(openstudio::ZoneRefrigerationDoorMixingFields::DoorProtectionType, true)) {
        return *value;
      }
      return "None";
    }

    bool ZoneRefrigerationDoorMixing_Impl::isDoorProtectionTypeDefaulted() const {
      return isEmpty(openstudio::ZoneRefrigerationDoorMixingFields::DoorProtectionType);
    }

    bool ZoneRefrigerationDoorMixing_Impl::setDoorProtectionType(const std::string& doorProtectionType) {
      return setString(openstudio::ZoneRefrigerationDoorMixingFields::DoorProtectionType, doorProtectionType);
    }

    void ZoneRefrigerationDoorMixing_Impl::resetDoorProtectionType() {
      OS_ASSERT(setString(openstudio::ZoneRefrigerationDoorMixingFields::DoorProtectionType, ""));
    }

    std::vector<std::string> ZoneRefrigerationDoorMixing_Impl::doorProtectionTypeValues() const {
      return openstudio::epmodel::ZoneRefrigerationDoorMixing::doorProtectionTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
