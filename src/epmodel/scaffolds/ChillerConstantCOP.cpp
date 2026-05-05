/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerConstantCOP.hpp"
#include "ChillerConstantCOP_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_ConstantCOP_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ChillerConstantCOP::ChillerConstantCOP(const Model& model) : ModelObject(ChillerConstantCOP::iddObjectType(), model) {}

  ChillerConstantCOP::ChillerConstantCOP(std::shared_ptr<detail::ChillerConstantCOP_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ChillerConstantCOP::iddObjectType() {
    return IddObjectType::Chiller_ConstantCOP;
  }

  std::vector<std::string> ChillerConstantCOP::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_ConstantCOPFields::CondenserType);
  }

  std::vector<std::string> ChillerConstantCOP::chillerFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_ConstantCOPFields::ChillerFlowMode);
  }

  boost::optional<double> ChillerConstantCOP::nominalCapacity() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->nominalCapacity();
  }

  bool ChillerConstantCOP::isNominalCapacityAutosized() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isNominalCapacityAutosized();
  }

  bool ChillerConstantCOP::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void ChillerConstantCOP::autosizeNominalCapacity() {
    getImpl<detail::ChillerConstantCOP_Impl>()->autosizeNominalCapacity();
  }

  double ChillerConstantCOP::nominalCOP() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->nominalCOP();
  }

  bool ChillerConstantCOP::setNominalCOP(double nominalCOP) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setNominalCOP(nominalCOP);
  }

  boost::optional<double> ChillerConstantCOP::designChilledWaterFlowRate() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->designChilledWaterFlowRate();
  }

  bool ChillerConstantCOP::isDesignChilledWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isDesignChilledWaterFlowRateAutosized();
  }

  bool ChillerConstantCOP::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
  }

  void ChillerConstantCOP::resetDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetDesignChilledWaterFlowRate();
  }

  void ChillerConstantCOP::autosizeDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerConstantCOP_Impl>()->autosizeDesignChilledWaterFlowRate();
  }

  boost::optional<double> ChillerConstantCOP::designCondenserWaterFlowRate() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->designCondenserWaterFlowRate();
  }

  bool ChillerConstantCOP::isDesignCondenserWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isDesignCondenserWaterFlowRateAutosized();
  }

  bool ChillerConstantCOP::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
  }

  void ChillerConstantCOP::resetDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetDesignCondenserWaterFlowRate();
  }

  void ChillerConstantCOP::autosizeDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerConstantCOP_Impl>()->autosizeDesignCondenserWaterFlowRate();
  }

  std::string ChillerConstantCOP::condenserType() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->condenserType();
  }

  bool ChillerConstantCOP::isCondenserTypeDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isCondenserTypeDefaulted();
  }

  bool ChillerConstantCOP::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setCondenserType(condenserType);
  }

  void ChillerConstantCOP::resetCondenserType() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetCondenserType();
  }

  std::string ChillerConstantCOP::chillerFlowMode() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->chillerFlowMode();
  }

  bool ChillerConstantCOP::isChillerFlowModeDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isChillerFlowModeDefaulted();
  }

  bool ChillerConstantCOP::setChillerFlowMode(const std::string& chillerFlowMode) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setChillerFlowMode(chillerFlowMode);
  }

  void ChillerConstantCOP::resetChillerFlowMode() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetChillerFlowMode();
  }

  double ChillerConstantCOP::sizingFactor() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->sizingFactor();
  }

  bool ChillerConstantCOP::isSizingFactorDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isSizingFactorDefaulted();
  }

  bool ChillerConstantCOP::setSizingFactor(double sizingFactor) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setSizingFactor(sizingFactor);
  }

  void ChillerConstantCOP::resetSizingFactor() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetSizingFactor();
  }

  double ChillerConstantCOP::basinHeaterCapacity() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->basinHeaterCapacity();
  }

  bool ChillerConstantCOP::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool ChillerConstantCOP::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void ChillerConstantCOP::resetBasinHeaterCapacity() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetBasinHeaterCapacity();
  }

  double ChillerConstantCOP::basinHeaterSetpointTemperature() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->basinHeaterSetpointTemperature();
  }

  bool ChillerConstantCOP::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool ChillerConstantCOP::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void ChillerConstantCOP::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  double ChillerConstantCOP::thermosiphonMinimumTemperatureDifference() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->thermosiphonMinimumTemperatureDifference();
  }

  bool ChillerConstantCOP::isThermosiphonMinimumTemperatureDifferenceDefaulted() const {
    return getImpl<detail::ChillerConstantCOP_Impl>()->isThermosiphonMinimumTemperatureDifferenceDefaulted();
  }

  bool ChillerConstantCOP::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
    return getImpl<detail::ChillerConstantCOP_Impl>()->setThermosiphonMinimumTemperatureDifference(thermosiphonMinimumTemperatureDifference);
  }

  void ChillerConstantCOP::resetThermosiphonMinimumTemperatureDifference() {
    getImpl<detail::ChillerConstantCOP_Impl>()->resetThermosiphonMinimumTemperatureDifference();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ChillerConstantCOP_Impl::nominalCapacity() const {
      return getDouble(openstudio::Chiller_ConstantCOPFields::NominalCapacity, true);
    }

    bool ChillerConstantCOP_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::Chiller_ConstantCOPFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerConstantCOP_Impl::setNominalCapacity(double nominalCapacity) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::NominalCapacity, nominalCapacity);
      return result;
    }

    void ChillerConstantCOP_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::NominalCapacity, "autosize"));
    }

    double ChillerConstantCOP_Impl::nominalCOP() const {
      const auto value = getDouble(openstudio::Chiller_ConstantCOPFields::NominalCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerConstantCOP_Impl::setNominalCOP(double nominalCOP) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::NominalCOP, nominalCOP);
      return result;
    }

    boost::optional<double> ChillerConstantCOP_Impl::designChilledWaterFlowRate() const {
      return getDouble(openstudio::Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, true);
    }

    bool ChillerConstantCOP_Impl::isDesignChilledWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerConstantCOP_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
      return result;
    }

    void ChillerConstantCOP_Impl::resetDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, ""));
    }

    void ChillerConstantCOP_Impl::autosizeDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::DesignChilledWaterFlowRate, "autosize"));
    }

    boost::optional<double> ChillerConstantCOP_Impl::designCondenserWaterFlowRate() const {
      return getDouble(openstudio::Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, true);
    }

    bool ChillerConstantCOP_Impl::isDesignCondenserWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerConstantCOP_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
      return result;
    }

    void ChillerConstantCOP_Impl::resetDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, ""));
    }

    void ChillerConstantCOP_Impl::autosizeDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::DesignCondenserWaterFlowRate, "autosize"));
    }

    std::string ChillerConstantCOP_Impl::condenserType() const {
      if (auto value = getString(openstudio::Chiller_ConstantCOPFields::CondenserType, false)) {
        return *value;
      }
      return "AirCooled";
    }

    bool ChillerConstantCOP_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::CondenserType);
    }

    bool ChillerConstantCOP_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Chiller_ConstantCOPFields::CondenserType, condenserType);
    }

    void ChillerConstantCOP_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::CondenserType, ""));
    }

    std::string ChillerConstantCOP_Impl::chillerFlowMode() const {
      if (auto value = getString(openstudio::Chiller_ConstantCOPFields::ChillerFlowMode, false)) {
        return *value;
      }
      return "NotModulated";
    }

    bool ChillerConstantCOP_Impl::isChillerFlowModeDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::ChillerFlowMode);
    }

    bool ChillerConstantCOP_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
      return setString(openstudio::Chiller_ConstantCOPFields::ChillerFlowMode, chillerFlowMode);
    }

    void ChillerConstantCOP_Impl::resetChillerFlowMode() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::ChillerFlowMode, ""));
    }

    double ChillerConstantCOP_Impl::sizingFactor() const {
      if (auto value = getDouble(openstudio::Chiller_ConstantCOPFields::SizingFactor, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ChillerConstantCOP_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::SizingFactor);
    }

    bool ChillerConstantCOP_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::SizingFactor, sizingFactor);
      return result;
    }

    void ChillerConstantCOP_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::SizingFactor, ""));
    }

    double ChillerConstantCOP_Impl::basinHeaterCapacity() const {
      if (auto value = getDouble(openstudio::Chiller_ConstantCOPFields::BasinHeaterCapacity, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ChillerConstantCOP_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::BasinHeaterCapacity);
    }

    bool ChillerConstantCOP_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::BasinHeaterCapacity, basinHeaterCapacity);
      return result;
    }

    void ChillerConstantCOP_Impl::resetBasinHeaterCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::BasinHeaterCapacity, ""));
    }

    double ChillerConstantCOP_Impl::basinHeaterSetpointTemperature() const {
      if (auto value = getDouble(openstudio::Chiller_ConstantCOPFields::BasinHeaterSetpointTemperature, false)) {
        return *value;
      }
      return 2.0;
    }

    bool ChillerConstantCOP_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::BasinHeaterSetpointTemperature);
    }

    bool ChillerConstantCOP_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      const bool result = setDouble(openstudio::Chiller_ConstantCOPFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
      return result;
    }

    void ChillerConstantCOP_Impl::resetBasinHeaterSetpointTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::BasinHeaterSetpointTemperature, ""));
    }

    double ChillerConstantCOP_Impl::thermosiphonMinimumTemperatureDifference() const {
      if (auto value = getDouble(openstudio::Chiller_ConstantCOPFields::ThermosiphonMinimumTemperatureDifference, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ChillerConstantCOP_Impl::isThermosiphonMinimumTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::Chiller_ConstantCOPFields::ThermosiphonMinimumTemperatureDifference);
    }

    bool ChillerConstantCOP_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
      const bool result =
        setDouble(openstudio::Chiller_ConstantCOPFields::ThermosiphonMinimumTemperatureDifference, thermosiphonMinimumTemperatureDifference);
      return result;
    }

    void ChillerConstantCOP_Impl::resetThermosiphonMinimumTemperatureDifference() {
      OS_ASSERT(setString(openstudio::Chiller_ConstantCOPFields::ThermosiphonMinimumTemperatureDifference, ""));
    }

    std::vector<std::string> ChillerConstantCOP_Impl::condenserTypeValues() const {
      return ChillerConstantCOP::condenserTypeValues();
    }

    std::vector<std::string> ChillerConstantCOP_Impl::chillerFlowModeValues() const {
      return ChillerConstantCOP::chillerFlowModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
