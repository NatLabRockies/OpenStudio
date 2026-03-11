/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/RefrigerationSystem.hpp"
#include "ModelObject/RefrigerationSystem_Impl.hpp"

#include "Model.hpp"

#include <utility>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_System_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  // Schema Alignment Note: Refrigeration:TransferLoadList objects contain only a name entry, so the only scalar coverage
  // is provided indirectly by the base ModelObject name APIs while relationships feed into the energyplus transfer list.

  RefrigerationSystem::RefrigerationSystem(const Model& model) : ModelObject(RefrigerationSystem::iddObjectType(), model) {
    OS_ASSERT(setMinimumCondensingTemperature(21.0));
    OS_ASSERT(setSuctionTemperatureControlType("ConstantSuctionTemperature"));
  }

  RefrigerationSystem::RefrigerationSystem(std::shared_ptr<detail::RefrigerationSystem_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationSystem::iddObjectType() {
    return IddObjectType::Refrigeration_System;
  }

  std::vector<std::string> RefrigerationSystem::refrigerationSystemWorkingFluidTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Refrigeration_SystemFields::RefrigerationSystemWorkingFluidType);
  }

  std::vector<std::string> RefrigerationSystem::suctionTemperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Refrigeration_SystemFields::SuctionTemperatureControlType);
  }

  std::vector<std::string> RefrigerationSystem::intercoolerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Refrigeration_SystemFields::IntercoolerType);
  }

  double RefrigerationSystem::minimumCondensingTemperature() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->minimumCondensingTemperature();
  }

  bool RefrigerationSystem::setMinimumCondensingTemperature(double minimumCondensingTemperature) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setMinimumCondensingTemperature(minimumCondensingTemperature);
  }

  std::string RefrigerationSystem::refrigerationSystemWorkingFluidType() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->refrigerationSystemWorkingFluidType();
  }

  bool RefrigerationSystem::setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setRefrigerationSystemWorkingFluidType(refrigerationSystemWorkingFluidType);
  }

  std::string RefrigerationSystem::suctionTemperatureControlType() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->suctionTemperatureControlType();
  }

  bool RefrigerationSystem::setSuctionTemperatureControlType(const std::string& suctionTemperatureControlType) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setSuctionTemperatureControlType(suctionTemperatureControlType);
  }

  bool RefrigerationSystem::isSuctionTemperatureControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->isSuctionTemperatureControlTypeDefaulted();
  }

  void RefrigerationSystem::resetSuctionTemperatureControlType() {
    getImpl<detail::RefrigerationSystem_Impl>()->resetSuctionTemperatureControlType();
  }

  double RefrigerationSystem::sumUASuctionPiping() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->sumUASuctionPiping();
  }

  bool RefrigerationSystem::setSumUASuctionPiping(double sumUASuctionPiping) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setSumUASuctionPiping(sumUASuctionPiping);
  }

  bool RefrigerationSystem::isSumUASuctionPipingDefaulted() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->isSumUASuctionPipingDefaulted();
  }

  void RefrigerationSystem::resetSumUASuctionPiping() {
    getImpl<detail::RefrigerationSystem_Impl>()->resetSumUASuctionPiping();
  }

  std::string RefrigerationSystem::endUseSubcategory() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->endUseSubcategory();
  }

  bool RefrigerationSystem::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  bool RefrigerationSystem::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->isEndUseSubcategoryDefaulted();
  }

  void RefrigerationSystem::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationSystem_Impl>()->resetEndUseSubcategory();
  }

  std::string RefrigerationSystem::intercoolerType() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->intercoolerType();
  }

  bool RefrigerationSystem::setIntercoolerType(const std::string& intercoolerType) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setIntercoolerType(intercoolerType);
  }

  bool RefrigerationSystem::isIntercoolerTypeDefaulted() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->isIntercoolerTypeDefaulted();
  }

  void RefrigerationSystem::resetIntercoolerType() {
    getImpl<detail::RefrigerationSystem_Impl>()->resetIntercoolerType();
  }

  double RefrigerationSystem::shellandCoilIntercoolerEffectiveness() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->shellandCoilIntercoolerEffectiveness();
  }

  bool RefrigerationSystem::setShellandCoilIntercoolerEffectiveness(double shellandCoilIntercoolerEffectiveness) {
    return getImpl<detail::RefrigerationSystem_Impl>()->setShellandCoilIntercoolerEffectiveness(shellandCoilIntercoolerEffectiveness);
  }

  bool RefrigerationSystem::isShellandCoilIntercoolerEffectivenessDefaulted() const {
    return getImpl<detail::RefrigerationSystem_Impl>()->isShellandCoilIntercoolerEffectivenessDefaulted();
  }

  void RefrigerationSystem::resetShellandCoilIntercoolerEffectiveness() {
    getImpl<detail::RefrigerationSystem_Impl>()->resetShellandCoilIntercoolerEffectiveness();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double RefrigerationSystem_Impl::minimumCondensingTemperature() const {
      auto value = getDouble(openstudio::Refrigeration_SystemFields::MinimumCondensingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setMinimumCondensingTemperature(double minimumCondensingTemperature) {
      bool result = setDouble(openstudio::Refrigeration_SystemFields::MinimumCondensingTemperature, minimumCondensingTemperature);
      OS_ASSERT(result);
      return result;
    }

    std::string RefrigerationSystem_Impl::refrigerationSystemWorkingFluidType() const {
      auto value = getString(openstudio::Refrigeration_SystemFields::RefrigerationSystemWorkingFluidType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType) {
      bool result = setString(openstudio::Refrigeration_SystemFields::RefrigerationSystemWorkingFluidType, refrigerationSystemWorkingFluidType);
      return result;
    }

    std::string RefrigerationSystem_Impl::suctionTemperatureControlType() const {
      auto value = getString(openstudio::Refrigeration_SystemFields::SuctionTemperatureControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setSuctionTemperatureControlType(const std::string& suctionTemperatureControlType) {
      bool result = setString(openstudio::Refrigeration_SystemFields::SuctionTemperatureControlType, suctionTemperatureControlType);
      return result;
    }

    bool RefrigerationSystem_Impl::isSuctionTemperatureControlTypeDefaulted() const {
      return isEmpty(openstudio::Refrigeration_SystemFields::SuctionTemperatureControlType);
    }

    void RefrigerationSystem_Impl::resetSuctionTemperatureControlType() {
      bool result = setString(openstudio::Refrigeration_SystemFields::SuctionTemperatureControlType, "");
      OS_ASSERT(result);
    }

    double RefrigerationSystem_Impl::sumUASuctionPiping() const {
      auto value = getDouble(openstudio::Refrigeration_SystemFields::SumUASuctionPiping, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setSumUASuctionPiping(double sumUASuctionPiping) {
      bool result = setDouble(openstudio::Refrigeration_SystemFields::SumUASuctionPiping, sumUASuctionPiping);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationSystem_Impl::isSumUASuctionPipingDefaulted() const {
      return isEmpty(openstudio::Refrigeration_SystemFields::SumUASuctionPiping);
    }

    void RefrigerationSystem_Impl::resetSumUASuctionPiping() {
      bool result = setString(openstudio::Refrigeration_SystemFields::SumUASuctionPiping, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationSystem_Impl::endUseSubcategory() const {
      auto value = getString(openstudio::Refrigeration_SystemFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      bool result = setString(openstudio::Refrigeration_SystemFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationSystem_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Refrigeration_SystemFields::EndUseSubcategory);
    }

    void RefrigerationSystem_Impl::resetEndUseSubcategory() {
      bool result = setString(openstudio::Refrigeration_SystemFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationSystem_Impl::intercoolerType() const {
      auto value = getString(openstudio::Refrigeration_SystemFields::IntercoolerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setIntercoolerType(const std::string& intercoolerType) {
      bool result = setString(openstudio::Refrigeration_SystemFields::IntercoolerType, intercoolerType);
      return result;
    }

    bool RefrigerationSystem_Impl::isIntercoolerTypeDefaulted() const {
      return isEmpty(openstudio::Refrigeration_SystemFields::IntercoolerType);
    }

    void RefrigerationSystem_Impl::resetIntercoolerType() {
      bool result = setString(openstudio::Refrigeration_SystemFields::IntercoolerType, "");
      OS_ASSERT(result);
    }

    double RefrigerationSystem_Impl::shellandCoilIntercoolerEffectiveness() const {
      auto value = getDouble(openstudio::Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSystem_Impl::setShellandCoilIntercoolerEffectiveness(double shellandCoilIntercoolerEffectiveness) {
      bool result = setDouble(openstudio::Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness, shellandCoilIntercoolerEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationSystem_Impl::isShellandCoilIntercoolerEffectivenessDefaulted() const {
      return isEmpty(openstudio::Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness);
    }

    void RefrigerationSystem_Impl::resetShellandCoilIntercoolerEffectiveness() {
      bool result = setString(openstudio::Refrigeration_SystemFields::ShellandCoilIntercoolerEffectiveness, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
