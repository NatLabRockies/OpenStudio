/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingCoil.hpp"
#include "FaultModelFoulingCoil_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_Coil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelFoulingCoil::FaultModelFoulingCoil(const Model& model) : ModelObject(FaultModelFoulingCoil::iddObjectType(), model) {}

  FaultModelFoulingCoil::FaultModelFoulingCoil(std::shared_ptr<detail::FaultModelFoulingCoil_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelFoulingCoil::iddObjectType() {
    return IddObjectType::FaultModel_Fouling_Coil;
  }

  std::vector<std::string> FaultModelFoulingCoil::foulingInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FaultModel_Fouling_CoilFields::FoulingInputMethod);
  }

  std::string FaultModelFoulingCoil::foulingInputMethod() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->foulingInputMethod();
  }

  bool FaultModelFoulingCoil::isFoulingInputMethodDefaulted() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->isFoulingInputMethodDefaulted();
  }

  bool FaultModelFoulingCoil::setFoulingInputMethod(const std::string& foulingInputMethod) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setFoulingInputMethod(foulingInputMethod);
  }

  void FaultModelFoulingCoil::resetFoulingInputMethod() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetFoulingInputMethod();
  }

  boost::optional<double> FaultModelFoulingCoil::uAFouled() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->uAFouled();
  }

  bool FaultModelFoulingCoil::setUAFouled(double uAFouled) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setUAFouled(uAFouled);
  }

  void FaultModelFoulingCoil::resetUAFouled() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetUAFouled();
  }

  double FaultModelFoulingCoil::waterSideFoulingFactor() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->waterSideFoulingFactor();
  }

  bool FaultModelFoulingCoil::isWaterSideFoulingFactorDefaulted() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->isWaterSideFoulingFactorDefaulted();
  }

  bool FaultModelFoulingCoil::setWaterSideFoulingFactor(double waterSideFoulingFactor) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setWaterSideFoulingFactor(waterSideFoulingFactor);
  }

  void FaultModelFoulingCoil::resetWaterSideFoulingFactor() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetWaterSideFoulingFactor();
  }

  double FaultModelFoulingCoil::airSideFoulingFactor() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->airSideFoulingFactor();
  }

  bool FaultModelFoulingCoil::isAirSideFoulingFactorDefaulted() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->isAirSideFoulingFactorDefaulted();
  }

  bool FaultModelFoulingCoil::setAirSideFoulingFactor(double airSideFoulingFactor) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setAirSideFoulingFactor(airSideFoulingFactor);
  }

  void FaultModelFoulingCoil::resetAirSideFoulingFactor() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetAirSideFoulingFactor();
  }

  boost::optional<double> FaultModelFoulingCoil::outsideCoilSurfaceArea() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->outsideCoilSurfaceArea();
  }

  bool FaultModelFoulingCoil::setOutsideCoilSurfaceArea(double outsideCoilSurfaceArea) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setOutsideCoilSurfaceArea(outsideCoilSurfaceArea);
  }

  void FaultModelFoulingCoil::resetOutsideCoilSurfaceArea() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetOutsideCoilSurfaceArea();
  }

  double FaultModelFoulingCoil::insidetoOutsideCoilSurfaceAreaRatio() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->insidetoOutsideCoilSurfaceAreaRatio();
  }

  bool FaultModelFoulingCoil::isInsidetoOutsideCoilSurfaceAreaRatioDefaulted() const {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->isInsidetoOutsideCoilSurfaceAreaRatioDefaulted();
  }

  bool FaultModelFoulingCoil::setInsidetoOutsideCoilSurfaceAreaRatio(double insidetoOutsideCoilSurfaceAreaRatio) {
    return getImpl<detail::FaultModelFoulingCoil_Impl>()->setInsidetoOutsideCoilSurfaceAreaRatio(insidetoOutsideCoilSurfaceAreaRatio);
  }

  void FaultModelFoulingCoil::resetInsidetoOutsideCoilSurfaceAreaRatio() {
    getImpl<detail::FaultModelFoulingCoil_Impl>()->resetInsidetoOutsideCoilSurfaceAreaRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string FaultModelFoulingCoil_Impl::foulingInputMethod() const {
      const auto value = getString(openstudio::FaultModel_Fouling_CoilFields::FoulingInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingCoil_Impl::isFoulingInputMethodDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_CoilFields::FoulingInputMethod);
    }

    bool FaultModelFoulingCoil_Impl::setFoulingInputMethod(const std::string& foulingInputMethod) {
      return setString(openstudio::FaultModel_Fouling_CoilFields::FoulingInputMethod, foulingInputMethod);
    }

    void FaultModelFoulingCoil_Impl::resetFoulingInputMethod() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::FoulingInputMethod, ""));
    }

    boost::optional<double> FaultModelFoulingCoil_Impl::uAFouled() const {
      return getDouble(openstudio::FaultModel_Fouling_CoilFields::UAFouled, true);
    }

    bool FaultModelFoulingCoil_Impl::setUAFouled(double uAFouled) {
      return setDouble(openstudio::FaultModel_Fouling_CoilFields::UAFouled, uAFouled);
    }

    void FaultModelFoulingCoil_Impl::resetUAFouled() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::UAFouled, ""));
    }

    double FaultModelFoulingCoil_Impl::waterSideFoulingFactor() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_CoilFields::WaterSideFoulingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingCoil_Impl::isWaterSideFoulingFactorDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_CoilFields::WaterSideFoulingFactor);
    }

    bool FaultModelFoulingCoil_Impl::setWaterSideFoulingFactor(double waterSideFoulingFactor) {
      return setDouble(openstudio::FaultModel_Fouling_CoilFields::WaterSideFoulingFactor, waterSideFoulingFactor);
    }

    void FaultModelFoulingCoil_Impl::resetWaterSideFoulingFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::WaterSideFoulingFactor, ""));
    }

    double FaultModelFoulingCoil_Impl::airSideFoulingFactor() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_CoilFields::AirSideFoulingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingCoil_Impl::isAirSideFoulingFactorDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_CoilFields::AirSideFoulingFactor);
    }

    bool FaultModelFoulingCoil_Impl::setAirSideFoulingFactor(double airSideFoulingFactor) {
      return setDouble(openstudio::FaultModel_Fouling_CoilFields::AirSideFoulingFactor, airSideFoulingFactor);
    }

    void FaultModelFoulingCoil_Impl::resetAirSideFoulingFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::AirSideFoulingFactor, ""));
    }

    boost::optional<double> FaultModelFoulingCoil_Impl::outsideCoilSurfaceArea() const {
      return getDouble(openstudio::FaultModel_Fouling_CoilFields::OutsideCoilSurfaceArea, true);
    }

    bool FaultModelFoulingCoil_Impl::setOutsideCoilSurfaceArea(double outsideCoilSurfaceArea) {
      return setDouble(openstudio::FaultModel_Fouling_CoilFields::OutsideCoilSurfaceArea, outsideCoilSurfaceArea);
    }

    void FaultModelFoulingCoil_Impl::resetOutsideCoilSurfaceArea() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::OutsideCoilSurfaceArea, ""));
    }

    double FaultModelFoulingCoil_Impl::insidetoOutsideCoilSurfaceAreaRatio() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_CoilFields::InsidetoOutsideCoilSurfaceAreaRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingCoil_Impl::isInsidetoOutsideCoilSurfaceAreaRatioDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_CoilFields::InsidetoOutsideCoilSurfaceAreaRatio);
    }

    bool FaultModelFoulingCoil_Impl::setInsidetoOutsideCoilSurfaceAreaRatio(double insidetoOutsideCoilSurfaceAreaRatio) {
      return setDouble(openstudio::FaultModel_Fouling_CoilFields::InsidetoOutsideCoilSurfaceAreaRatio, insidetoOutsideCoilSurfaceAreaRatio);
    }

    void FaultModelFoulingCoil_Impl::resetInsidetoOutsideCoilSurfaceAreaRatio() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoilFields::InsidetoOutsideCoilSurfaceAreaRatio, ""));
    }

    std::vector<std::string> FaultModelFoulingCoil_Impl::foulingInputMethodValues() const {
      return openstudio::epmodel::FaultModelFoulingCoil::foulingInputMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
