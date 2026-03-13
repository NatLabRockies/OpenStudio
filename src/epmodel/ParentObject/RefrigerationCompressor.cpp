/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationCompressor.hpp"
#include "ParentObject/RefrigerationCompressor_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_Compressor_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationCompressor::RefrigerationCompressor(const Model& model) : ParentObject(RefrigerationCompressor::iddObjectType(), model) {}

  RefrigerationCompressor::RefrigerationCompressor(std::shared_ptr<detail::RefrigerationCompressor_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationCompressor::iddObjectType() {
    return IddObjectType::Refrigeration_Compressor;
  }

  std::vector<std::string> RefrigerationCompressor::modeofOperationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_CompressorFields::ModeofOperation);
  }

  boost::optional<double> RefrigerationCompressor::ratedSuperheat() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->ratedSuperheat();
  }

  bool RefrigerationCompressor::setRatedSuperheat(double ratedSuperheat) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setRatedSuperheat(ratedSuperheat);
  }

  void RefrigerationCompressor::resetRatedSuperheat() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetRatedSuperheat();
  }

  boost::optional<double> RefrigerationCompressor::ratedReturnGasTemperature() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->ratedReturnGasTemperature();
  }

  bool RefrigerationCompressor::setRatedReturnGasTemperature(double ratedReturnGasTemperature) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setRatedReturnGasTemperature(ratedReturnGasTemperature);
  }

  void RefrigerationCompressor::resetRatedReturnGasTemperature() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetRatedReturnGasTemperature();
  }

  boost::optional<double> RefrigerationCompressor::ratedLiquidTemperature() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->ratedLiquidTemperature();
  }

  bool RefrigerationCompressor::setRatedLiquidTemperature(double ratedLiquidTemperature) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setRatedLiquidTemperature(ratedLiquidTemperature);
  }

  void RefrigerationCompressor::resetRatedLiquidTemperature() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetRatedLiquidTemperature();
  }

  boost::optional<double> RefrigerationCompressor::ratedSubcooling() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->ratedSubcooling();
  }

  bool RefrigerationCompressor::setRatedSubcooling(double ratedSubcooling) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setRatedSubcooling(ratedSubcooling);
  }

  void RefrigerationCompressor::resetRatedSubcooling() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetRatedSubcooling();
  }

  std::string RefrigerationCompressor::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCompressor::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCompressor::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationCompressor::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetEndUseSubcategory();
  }

  std::string RefrigerationCompressor::modeofOperation() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->modeofOperation();
  }

  bool RefrigerationCompressor::isModeofOperationDefaulted() const {
    return getImpl<detail::RefrigerationCompressor_Impl>()->isModeofOperationDefaulted();
  }

  bool RefrigerationCompressor::setModeofOperation(const std::string& modeofOperation) {
    return getImpl<detail::RefrigerationCompressor_Impl>()->setModeofOperation(modeofOperation);
  }

  void RefrigerationCompressor::resetModeofOperation() {
    getImpl<detail::RefrigerationCompressor_Impl>()->resetModeofOperation();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> RefrigerationCompressor_Impl::ratedSuperheat() const {
      return getDouble(Refrigeration_CompressorFields::RatedSuperheat, true);
    }

    bool RefrigerationCompressor_Impl::setRatedSuperheat(double ratedSuperheat) {
      return setDouble(Refrigeration_CompressorFields::RatedSuperheat, ratedSuperheat);
    }

    void RefrigerationCompressor_Impl::resetRatedSuperheat() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::RatedSuperheat, ""));
    }

    boost::optional<double> RefrigerationCompressor_Impl::ratedReturnGasTemperature() const {
      return getDouble(Refrigeration_CompressorFields::RatedReturnGasTemperature, true);
    }

    bool RefrigerationCompressor_Impl::setRatedReturnGasTemperature(double ratedReturnGasTemperature) {
      return setDouble(Refrigeration_CompressorFields::RatedReturnGasTemperature, ratedReturnGasTemperature);
    }

    void RefrigerationCompressor_Impl::resetRatedReturnGasTemperature() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::RatedReturnGasTemperature, ""));
    }

    boost::optional<double> RefrigerationCompressor_Impl::ratedLiquidTemperature() const {
      return getDouble(Refrigeration_CompressorFields::RatedLiquidTemperature, true);
    }

    bool RefrigerationCompressor_Impl::setRatedLiquidTemperature(double ratedLiquidTemperature) {
      return setDouble(Refrigeration_CompressorFields::RatedLiquidTemperature, ratedLiquidTemperature);
    }

    void RefrigerationCompressor_Impl::resetRatedLiquidTemperature() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::RatedLiquidTemperature, ""));
    }

    boost::optional<double> RefrigerationCompressor_Impl::ratedSubcooling() const {
      return getDouble(Refrigeration_CompressorFields::RatedSubcooling, true);
    }

    bool RefrigerationCompressor_Impl::setRatedSubcooling(double ratedSubcooling) {
      return setDouble(Refrigeration_CompressorFields::RatedSubcooling, ratedSubcooling);
    }

    void RefrigerationCompressor_Impl::resetRatedSubcooling() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::RatedSubcooling, ""));
    }

    std::string RefrigerationCompressor_Impl::endUseSubcategory() const {
      const auto value = getString(Refrigeration_CompressorFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCompressor_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_CompressorFields::EndUseSubcategory);
    }

    bool RefrigerationCompressor_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(Refrigeration_CompressorFields::EndUseSubcategory, endUseSubcategory);
    }

    void RefrigerationCompressor_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::EndUseSubcategory, ""));
    }

    std::string RefrigerationCompressor_Impl::modeofOperation() const {
      const auto value = getString(Refrigeration_CompressorFields::ModeofOperation, true);
      if (value && !value->empty()) {
        return *value;
      }
      return "Subcritical";
    }

    bool RefrigerationCompressor_Impl::isModeofOperationDefaulted() const {
      return isEmpty(Refrigeration_CompressorFields::ModeofOperation);
    }

    bool RefrigerationCompressor_Impl::setModeofOperation(const std::string& modeofOperation) {
      return setString(Refrigeration_CompressorFields::ModeofOperation, modeofOperation);
    }

    void RefrigerationCompressor_Impl::resetModeofOperation() {
      OS_ASSERT(setString(Refrigeration_CompressorFields::ModeofOperation, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
