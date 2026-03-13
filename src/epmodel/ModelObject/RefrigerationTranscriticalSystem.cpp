/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RefrigerationTranscriticalSystem.hpp"
#include "RefrigerationTranscriticalSystem_Impl.hpp"
#include "ModelObject/FluidPropertiesName.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Refrigeration_TranscriticalSystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationTranscriticalSystem::RefrigerationTranscriticalSystem(const Model& model)
    : ModelObject(RefrigerationTranscriticalSystem::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RefrigerationTranscriticalSystem_Impl>());

    FluidPropertiesName fluid(model);
    OS_ASSERT(!fluid.fluidTypeValues().empty());
    OS_ASSERT(fluid.setFluidName("R744"));
    OS_ASSERT(fluid.setFluidType(fluid.fluidTypeValues().front()));

    OS_ASSERT(setReceiverPressure(3500000.0));
    OS_ASSERT(setSubcoolerEffectiveness(0.4));
    OS_ASSERT(setRefrigerationSystemWorkingFluidType(fluid.fluidName()));
    OS_ASSERT(setSumUASuctionPipingforMediumTemperatureLoads(0.0));
    OS_ASSERT(setSumUASuctionPipingforLowTemperatureLoads(0.0));
  }

  RefrigerationTranscriticalSystem::RefrigerationTranscriticalSystem(std::shared_ptr<detail::RefrigerationTranscriticalSystem_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationTranscriticalSystem::iddObjectType() {
    return IddObjectType::Refrigeration_TranscriticalSystem;
  }

  std::vector<std::string> RefrigerationTranscriticalSystem::refrigerationSystemWorkingFluidTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Refrigeration_TranscriticalSystemFields::RefrigerationSystemWorkingFluidType);
  }

  double RefrigerationTranscriticalSystem::receiverPressure() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->receiverPressure();
  }

  bool RefrigerationTranscriticalSystem::isReceiverPressureDefaulted() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->isReceiverPressureDefaulted();
  }

  bool RefrigerationTranscriticalSystem::setReceiverPressure(double receiverPressure) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setReceiverPressure(receiverPressure);
  }

  void RefrigerationTranscriticalSystem::resetReceiverPressure() {
    getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->resetReceiverPressure();
  }

  double RefrigerationTranscriticalSystem::subcoolerEffectiveness() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->subcoolerEffectiveness();
  }

  bool RefrigerationTranscriticalSystem::isSubcoolerEffectivenessDefaulted() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->isSubcoolerEffectivenessDefaulted();
  }

  bool RefrigerationTranscriticalSystem::setSubcoolerEffectiveness(double subcoolerEffectiveness) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setSubcoolerEffectiveness(subcoolerEffectiveness);
  }

  void RefrigerationTranscriticalSystem::resetSubcoolerEffectiveness() {
    getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->resetSubcoolerEffectiveness();
  }

  std::string RefrigerationTranscriticalSystem::refrigerationSystemWorkingFluidType() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->refrigerationSystemWorkingFluidType();
  }

  bool RefrigerationTranscriticalSystem::setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setRefrigerationSystemWorkingFluidType(refrigerationSystemWorkingFluidType);
  }

  double RefrigerationTranscriticalSystem::sumUASuctionPipingforMediumTemperatureLoads() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->sumUASuctionPipingforMediumTemperatureLoads();
  }

  bool RefrigerationTranscriticalSystem::isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->isSumUASuctionPipingforMediumTemperatureLoadsDefaulted();
  }

  bool RefrigerationTranscriticalSystem::setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setSumUASuctionPipingforMediumTemperatureLoads(
      sumUASuctionPipingforMediumTemperatureLoads);
  }

  void RefrigerationTranscriticalSystem::resetSumUASuctionPipingforMediumTemperatureLoads() {
    getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->resetSumUASuctionPipingforMediumTemperatureLoads();
  }

  double RefrigerationTranscriticalSystem::sumUASuctionPipingforLowTemperatureLoads() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->sumUASuctionPipingforLowTemperatureLoads();
  }

  bool RefrigerationTranscriticalSystem::isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->isSumUASuctionPipingforLowTemperatureLoadsDefaulted();
  }

  bool RefrigerationTranscriticalSystem::setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setSumUASuctionPipingforLowTemperatureLoads(
      sumUASuctionPipingforLowTemperatureLoads);
  }

  void RefrigerationTranscriticalSystem::resetSumUASuctionPipingforLowTemperatureLoads() {
    getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->resetSumUASuctionPipingforLowTemperatureLoads();
  }

  std::string RefrigerationTranscriticalSystem::endUseSubcategory() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->endUseSubcategory();
  }

  bool RefrigerationTranscriticalSystem::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationTranscriticalSystem::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationTranscriticalSystem::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationTranscriticalSystem_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double RefrigerationTranscriticalSystem_Impl::receiverPressure() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_TranscriticalSystemFields::ReceiverPressure, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::isReceiverPressureDefaulted() const {
      return isEmpty(openstudio::Refrigeration_TranscriticalSystemFields::ReceiverPressure);
    }

    bool RefrigerationTranscriticalSystem_Impl::setReceiverPressure(double receiverPressure) {
      bool result = setDouble(openstudio::Refrigeration_TranscriticalSystemFields::ReceiverPressure, receiverPressure);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationTranscriticalSystem_Impl::resetReceiverPressure() {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::ReceiverPressure, "");
      OS_ASSERT(result);
    }

    double RefrigerationTranscriticalSystem_Impl::subcoolerEffectiveness() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_TranscriticalSystemFields::SubcoolerEffectiveness, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::isSubcoolerEffectivenessDefaulted() const {
      return isEmpty(openstudio::Refrigeration_TranscriticalSystemFields::SubcoolerEffectiveness);
    }

    bool RefrigerationTranscriticalSystem_Impl::setSubcoolerEffectiveness(double subcoolerEffectiveness) {
      bool result = setDouble(openstudio::Refrigeration_TranscriticalSystemFields::SubcoolerEffectiveness, subcoolerEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationTranscriticalSystem_Impl::resetSubcoolerEffectiveness() {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::SubcoolerEffectiveness, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationTranscriticalSystem_Impl::refrigerationSystemWorkingFluidType() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_TranscriticalSystemFields::RefrigerationSystemWorkingFluidType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType) {
      return setString(openstudio::Refrigeration_TranscriticalSystemFields::RefrigerationSystemWorkingFluidType, refrigerationSystemWorkingFluidType);
    }

    double RefrigerationTranscriticalSystem_Impl::sumUASuctionPipingforMediumTemperatureLoads() const {
      boost::optional<double> value =
        getDouble(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforMediumTemperatureLoads, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const {
      return isEmpty(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforMediumTemperatureLoads);
    }

    bool RefrigerationTranscriticalSystem_Impl::setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads) {
      bool result = setDouble(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforMediumTemperatureLoads,
                              sumUASuctionPipingforMediumTemperatureLoads);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationTranscriticalSystem_Impl::resetSumUASuctionPipingforMediumTemperatureLoads() {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforMediumTemperatureLoads, "");
      OS_ASSERT(result);
    }

    double RefrigerationTranscriticalSystem_Impl::sumUASuctionPipingforLowTemperatureLoads() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforLowTemperatureLoads, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const {
      return isEmpty(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforLowTemperatureLoads);
    }

    bool RefrigerationTranscriticalSystem_Impl::setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads) {
      bool result = setDouble(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforLowTemperatureLoads,
                              sumUASuctionPipingforLowTemperatureLoads);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationTranscriticalSystem_Impl::resetSumUASuctionPipingforLowTemperatureLoads() {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::SumUASuctionPipingforLowTemperatureLoads, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationTranscriticalSystem_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_TranscriticalSystemFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationTranscriticalSystem_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Refrigeration_TranscriticalSystemFields::EndUseSubcategory);
    }

    bool RefrigerationTranscriticalSystem_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationTranscriticalSystem_Impl::resetEndUseSubcategory() {
      bool result = setString(openstudio::Refrigeration_TranscriticalSystemFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
