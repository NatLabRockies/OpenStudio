/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/WaterUseRainCollector.hpp"
#include "scaffolds/WaterUseRainCollector_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WaterUse_RainCollector_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  WaterUseRainCollector::WaterUseRainCollector(const Model& model) : ModelObject(WaterUseRainCollector::iddObjectType(), model) {}

  WaterUseRainCollector::WaterUseRainCollector(std::shared_ptr<detail::WaterUseRainCollector_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WaterUseRainCollector::iddObjectType() {
    return IddObjectType::WaterUse_RainCollector;
  }

  std::vector<std::string> WaterUseRainCollector::lossFactorModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterUse_RainCollectorFields::LossFactorMode);
  }

  boost::optional<std::string> WaterUseRainCollector::lossFactorMode() const {
    return getImpl<detail::WaterUseRainCollector_Impl>()->lossFactorMode();
  }

  bool WaterUseRainCollector::setLossFactorMode(const std::string& lossFactorMode) {
    return getImpl<detail::WaterUseRainCollector_Impl>()->setLossFactorMode(lossFactorMode);
  }

  boost::optional<double> WaterUseRainCollector::collectionLossFactor() const {
    return getImpl<detail::WaterUseRainCollector_Impl>()->collectionLossFactor();
  }

  bool WaterUseRainCollector::setCollectionLossFactor(double collectionLossFactor) {
    return getImpl<detail::WaterUseRainCollector_Impl>()->setCollectionLossFactor(collectionLossFactor);
  }

  boost::optional<double> WaterUseRainCollector::maximumCollectionRate() const {
    return getImpl<detail::WaterUseRainCollector_Impl>()->maximumCollectionRate();
  }

  bool WaterUseRainCollector::setMaximumCollectionRate(double maximumCollectionRate) {
    return getImpl<detail::WaterUseRainCollector_Impl>()->setMaximumCollectionRate(maximumCollectionRate);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> WaterUseRainCollector_Impl::lossFactorModeValues() const {
      return openstudio::epmodel::WaterUseRainCollector::lossFactorModeValues();
    }

    boost::optional<std::string> WaterUseRainCollector_Impl::lossFactorMode() const {
      return getString(openstudio::WaterUse_RainCollectorFields::LossFactorMode, true);
    }

    bool WaterUseRainCollector_Impl::setLossFactorMode(const std::string& lossFactorMode) {
      return setString(openstudio::WaterUse_RainCollectorFields::LossFactorMode, lossFactorMode);
    }

    boost::optional<double> WaterUseRainCollector_Impl::collectionLossFactor() const {
      return getDouble(openstudio::WaterUse_RainCollectorFields::CollectionLossFactor, true);
    }

    bool WaterUseRainCollector_Impl::setCollectionLossFactor(double collectionLossFactor) {
      return setDouble(openstudio::WaterUse_RainCollectorFields::CollectionLossFactor, collectionLossFactor);
    }

    boost::optional<double> WaterUseRainCollector_Impl::maximumCollectionRate() const {
      return getDouble(openstudio::WaterUse_RainCollectorFields::MaximumCollectionRate, true);
    }

    bool WaterUseRainCollector_Impl::setMaximumCollectionRate(double maximumCollectionRate) {
      return setDouble(openstudio::WaterUse_RainCollectorFields::MaximumCollectionRate, maximumCollectionRate);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
