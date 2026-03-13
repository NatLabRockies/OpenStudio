/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationSecondarySystem.hpp"
#include "ParentObject/RefrigerationSecondarySystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_SecondarySystem_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::string RefrigerationSecondarySystem_Impl::circulatingFluidName() const {
      const auto value = getString(Refrigeration_SecondarySystemFields::CirculatingFluidName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::setCirculatingFluidName(const std::string& circulatingFluidName) {
      const bool result = setString(Refrigeration_SecondarySystemFields::CirculatingFluidName, circulatingFluidName);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::evaporatorCapacity() const {
      return getDouble(Refrigeration_SecondarySystemFields::EvaporatorCapacity, true);
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorCapacity(double evaporatorCapacity) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::EvaporatorCapacity, evaporatorCapacity);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetEvaporatorCapacity() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::EvaporatorCapacity, ""));
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::evaporatorFlowRateforSecondaryFluid() const {
      return getDouble(Refrigeration_SecondarySystemFields::EvaporatorFlowRateforSecondaryFluid, true);
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorFlowRateforSecondaryFluid(double evaporatorFlowRateforSecondaryFluid) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::EvaporatorFlowRateforSecondaryFluid, evaporatorFlowRateforSecondaryFluid);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetEvaporatorFlowRateforSecondaryFluid() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::EvaporatorFlowRateforSecondaryFluid, ""));
    }

    double RefrigerationSecondarySystem_Impl::evaporatorEvaporatingTemperature() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::EvaporatorEvaporatingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorEvaporatingTemperature(double evaporatorEvaporatingTemperature) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::EvaporatorEvaporatingTemperature, evaporatorEvaporatingTemperature);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationSecondarySystem_Impl::evaporatorApproachTemperatureDifference() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::EvaporatorApproachTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorApproachTemperatureDifference(double evaporatorApproachTemperatureDifference) {
      const bool result =
        setDouble(Refrigeration_SecondarySystemFields::EvaporatorApproachTemperatureDifference, evaporatorApproachTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::evaporatorRangeTemperatureDifference() const {
      return getDouble(Refrigeration_SecondarySystemFields::EvaporatorRangeTemperatureDifference, true);
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorRangeTemperatureDifference(double evaporatorRangeTemperatureDifference) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::EvaporatorRangeTemperatureDifference, evaporatorRangeTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetEvaporatorRangeTemperatureDifference() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::EvaporatorRangeTemperatureDifference, ""));
    }

    int RefrigerationSecondarySystem_Impl::numberofPumpsinLoop() const {
      const auto value = getInt(Refrigeration_SecondarySystemFields::NumberofPumpsinLoop, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isNumberofPumpsinLoopDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::NumberofPumpsinLoop);
    }

    bool RefrigerationSecondarySystem_Impl::setNumberofPumpsinLoop(int numberofPumpsinLoop) {
      const bool result = setInt(Refrigeration_SecondarySystemFields::NumberofPumpsinLoop, numberofPumpsinLoop);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetNumberofPumpsinLoop() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::NumberofPumpsinLoop, ""));
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::totalPumpFlowRate() const {
      return getDouble(Refrigeration_SecondarySystemFields::TotalPumpFlowRate, true);
    }

    bool RefrigerationSecondarySystem_Impl::setTotalPumpFlowRate(double totalPumpFlowRate) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::TotalPumpFlowRate, totalPumpFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetTotalPumpFlowRate() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::TotalPumpFlowRate, ""));
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::totalPumpPower() const {
      return getDouble(Refrigeration_SecondarySystemFields::TotalPumpPower, true);
    }

    bool RefrigerationSecondarySystem_Impl::setTotalPumpPower(double totalPumpPower) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::TotalPumpPower, totalPumpPower);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetTotalPumpPower() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::TotalPumpPower, ""));
    }

    boost::optional<double> RefrigerationSecondarySystem_Impl::totalPumpHead() const {
      return getDouble(Refrigeration_SecondarySystemFields::TotalPumpHead, true);
    }

    bool RefrigerationSecondarySystem_Impl::setTotalPumpHead(double totalPumpHead) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::TotalPumpHead, totalPumpHead);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetTotalPumpHead() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::TotalPumpHead, ""));
    }

    double RefrigerationSecondarySystem_Impl::phaseChangeCirculatingRate() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::PhaseChangeCirculatingRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isPhaseChangeCirculatingRateDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::PhaseChangeCirculatingRate);
    }

    bool RefrigerationSecondarySystem_Impl::setPhaseChangeCirculatingRate(double phaseChangeCirculatingRate) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::PhaseChangeCirculatingRate, phaseChangeCirculatingRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetPhaseChangeCirculatingRate() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::PhaseChangeCirculatingRate, ""));
    }

    std::string RefrigerationSecondarySystem_Impl::pumpDriveType() const {
      const auto value = getString(Refrigeration_SecondarySystemFields::PumpDriveType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isPumpDriveTypeDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::PumpDriveType);
    }

    bool RefrigerationSecondarySystem_Impl::setPumpDriveType(const std::string& pumpDriveType) {
      const bool result = setString(Refrigeration_SecondarySystemFields::PumpDriveType, pumpDriveType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetPumpDriveType() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::PumpDriveType, ""));
    }

    double RefrigerationSecondarySystem_Impl::pumpMotorHeattoFluid() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::PumpMotorHeattoFluid, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isPumpMotorHeattoFluidDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::PumpMotorHeattoFluid);
    }

    bool RefrigerationSecondarySystem_Impl::setPumpMotorHeattoFluid(double pumpMotorHeattoFluid) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::PumpMotorHeattoFluid, pumpMotorHeattoFluid);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetPumpMotorHeattoFluid() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::PumpMotorHeattoFluid, ""));
    }

    double RefrigerationSecondarySystem_Impl::sumUADistributionPiping() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::SumUADistributionPiping, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isSumUADistributionPipingDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::SumUADistributionPiping);
    }

    bool RefrigerationSecondarySystem_Impl::setSumUADistributionPiping(double sumUADistributionPiping) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::SumUADistributionPiping, sumUADistributionPiping);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetSumUADistributionPiping() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::SumUADistributionPiping, ""));
    }

    double RefrigerationSecondarySystem_Impl::sumUAReceiverSeparatorShell() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::SumUAReceiver_SeparatorShell, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isSumUAReceiverSeparatorShellDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::SumUAReceiver_SeparatorShell);
    }

    bool RefrigerationSecondarySystem_Impl::setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::SumUAReceiver_SeparatorShell, sumUAReceiverSeparatorShell);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetSumUAReceiverSeparatorShell() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::SumUAReceiver_SeparatorShell, ""));
    }

    double RefrigerationSecondarySystem_Impl::evaporatorRefrigerantInventory() const {
      const auto value = getDouble(Refrigeration_SecondarySystemFields::EvaporatorRefrigerantInventory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isEvaporatorRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::EvaporatorRefrigerantInventory);
    }

    bool RefrigerationSecondarySystem_Impl::setEvaporatorRefrigerantInventory(double evaporatorRefrigerantInventory) {
      const bool result = setDouble(Refrigeration_SecondarySystemFields::EvaporatorRefrigerantInventory, evaporatorRefrigerantInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetEvaporatorRefrigerantInventory() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::EvaporatorRefrigerantInventory, ""));
    }

    std::string RefrigerationSecondarySystem_Impl::endUseSubcategory() const {
      const auto value = getString(Refrigeration_SecondarySystemFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSecondarySystem_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_SecondarySystemFields::EndUseSubcategory);
    }

    bool RefrigerationSecondarySystem_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(Refrigeration_SecondarySystemFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSecondarySystem_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(Refrigeration_SecondarySystemFields::EndUseSubcategory, ""));
    }

  }  // namespace detail

  RefrigerationSecondarySystem::RefrigerationSecondarySystem(const Model& model)
    : ParentObject(RefrigerationSecondarySystem::iddObjectType(), model) {}

  RefrigerationSecondarySystem::RefrigerationSecondarySystem(std::shared_ptr<detail::RefrigerationSecondarySystem_Impl> impl)
    : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationSecondarySystem::iddObjectType() {
    return IddObjectType::Refrigeration_SecondarySystem;
  }

  std::vector<std::string> RefrigerationSecondarySystem::circulatingFluidNameValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_SecondarySystemFields::CirculatingFluidName);
  }

  std::vector<std::string> RefrigerationSecondarySystem::pumpDriveTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_SecondarySystemFields::PumpDriveType);
  }

  std::string RefrigerationSecondarySystem::circulatingFluidName() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->circulatingFluidName();
  }

  bool RefrigerationSecondarySystem::setCirculatingFluidName(const std::string& circulatingFluidName) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setCirculatingFluidName(circulatingFluidName);
  }

  boost::optional<double> RefrigerationSecondarySystem::evaporatorCapacity() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorCapacity();
  }

  bool RefrigerationSecondarySystem::setEvaporatorCapacity(double evaporatorCapacity) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorCapacity(evaporatorCapacity);
  }

  void RefrigerationSecondarySystem::resetEvaporatorCapacity() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetEvaporatorCapacity();
  }

  boost::optional<double> RefrigerationSecondarySystem::evaporatorFlowRateforSecondaryFluid() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorFlowRateforSecondaryFluid();
  }

  bool RefrigerationSecondarySystem::setEvaporatorFlowRateforSecondaryFluid(double evaporatorFlowRateforSecondaryFluid) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorFlowRateforSecondaryFluid(evaporatorFlowRateforSecondaryFluid);
  }

  void RefrigerationSecondarySystem::resetEvaporatorFlowRateforSecondaryFluid() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetEvaporatorFlowRateforSecondaryFluid();
  }

  double RefrigerationSecondarySystem::evaporatorEvaporatingTemperature() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorEvaporatingTemperature();
  }

  bool RefrigerationSecondarySystem::setEvaporatorEvaporatingTemperature(double evaporatorEvaporatingTemperature) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorEvaporatingTemperature(evaporatorEvaporatingTemperature);
  }

  double RefrigerationSecondarySystem::evaporatorApproachTemperatureDifference() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorApproachTemperatureDifference();
  }

  bool RefrigerationSecondarySystem::setEvaporatorApproachTemperatureDifference(double evaporatorApproachTemperatureDifference) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorApproachTemperatureDifference(evaporatorApproachTemperatureDifference);
  }

  boost::optional<double> RefrigerationSecondarySystem::evaporatorRangeTemperatureDifference() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorRangeTemperatureDifference();
  }

  bool RefrigerationSecondarySystem::setEvaporatorRangeTemperatureDifference(double evaporatorRangeTemperatureDifference) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorRangeTemperatureDifference(evaporatorRangeTemperatureDifference);
  }

  void RefrigerationSecondarySystem::resetEvaporatorRangeTemperatureDifference() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetEvaporatorRangeTemperatureDifference();
  }

  int RefrigerationSecondarySystem::numberofPumpsinLoop() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->numberofPumpsinLoop();
  }

  bool RefrigerationSecondarySystem::isNumberofPumpsinLoopDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isNumberofPumpsinLoopDefaulted();
  }

  bool RefrigerationSecondarySystem::setNumberofPumpsinLoop(int numberofPumpsinLoop) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setNumberofPumpsinLoop(numberofPumpsinLoop);
  }

  void RefrigerationSecondarySystem::resetNumberofPumpsinLoop() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetNumberofPumpsinLoop();
  }

  boost::optional<double> RefrigerationSecondarySystem::totalPumpFlowRate() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->totalPumpFlowRate();
  }

  bool RefrigerationSecondarySystem::setTotalPumpFlowRate(double totalPumpFlowRate) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setTotalPumpFlowRate(totalPumpFlowRate);
  }

  void RefrigerationSecondarySystem::resetTotalPumpFlowRate() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetTotalPumpFlowRate();
  }

  boost::optional<double> RefrigerationSecondarySystem::totalPumpPower() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->totalPumpPower();
  }

  bool RefrigerationSecondarySystem::setTotalPumpPower(double totalPumpPower) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setTotalPumpPower(totalPumpPower);
  }

  void RefrigerationSecondarySystem::resetTotalPumpPower() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetTotalPumpPower();
  }

  boost::optional<double> RefrigerationSecondarySystem::totalPumpHead() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->totalPumpHead();
  }

  bool RefrigerationSecondarySystem::setTotalPumpHead(double totalPumpHead) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setTotalPumpHead(totalPumpHead);
  }

  void RefrigerationSecondarySystem::resetTotalPumpHead() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetTotalPumpHead();
  }

  double RefrigerationSecondarySystem::phaseChangeCirculatingRate() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->phaseChangeCirculatingRate();
  }

  bool RefrigerationSecondarySystem::isPhaseChangeCirculatingRateDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isPhaseChangeCirculatingRateDefaulted();
  }

  bool RefrigerationSecondarySystem::setPhaseChangeCirculatingRate(double phaseChangeCirculatingRate) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setPhaseChangeCirculatingRate(phaseChangeCirculatingRate);
  }

  void RefrigerationSecondarySystem::resetPhaseChangeCirculatingRate() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetPhaseChangeCirculatingRate();
  }

  std::string RefrigerationSecondarySystem::pumpDriveType() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->pumpDriveType();
  }

  bool RefrigerationSecondarySystem::isPumpDriveTypeDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isPumpDriveTypeDefaulted();
  }

  bool RefrigerationSecondarySystem::setPumpDriveType(const std::string& pumpDriveType) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setPumpDriveType(pumpDriveType);
  }

  void RefrigerationSecondarySystem::resetPumpDriveType() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetPumpDriveType();
  }

  double RefrigerationSecondarySystem::pumpMotorHeattoFluid() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->pumpMotorHeattoFluid();
  }

  bool RefrigerationSecondarySystem::isPumpMotorHeattoFluidDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isPumpMotorHeattoFluidDefaulted();
  }

  bool RefrigerationSecondarySystem::setPumpMotorHeattoFluid(double pumpMotorHeattoFluid) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setPumpMotorHeattoFluid(pumpMotorHeattoFluid);
  }

  void RefrigerationSecondarySystem::resetPumpMotorHeattoFluid() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetPumpMotorHeattoFluid();
  }

  double RefrigerationSecondarySystem::sumUADistributionPiping() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->sumUADistributionPiping();
  }

  bool RefrigerationSecondarySystem::isSumUADistributionPipingDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isSumUADistributionPipingDefaulted();
  }

  bool RefrigerationSecondarySystem::setSumUADistributionPiping(double sumUADistributionPiping) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setSumUADistributionPiping(sumUADistributionPiping);
  }

  void RefrigerationSecondarySystem::resetSumUADistributionPiping() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetSumUADistributionPiping();
  }

  double RefrigerationSecondarySystem::sumUAReceiverSeparatorShell() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->sumUAReceiverSeparatorShell();
  }

  bool RefrigerationSecondarySystem::isSumUAReceiverSeparatorShellDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isSumUAReceiverSeparatorShellDefaulted();
  }

  bool RefrigerationSecondarySystem::setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setSumUAReceiverSeparatorShell(sumUAReceiverSeparatorShell);
  }

  void RefrigerationSecondarySystem::resetSumUAReceiverSeparatorShell() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetSumUAReceiverSeparatorShell();
  }

  double RefrigerationSecondarySystem::evaporatorRefrigerantInventory() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->evaporatorRefrigerantInventory();
  }

  bool RefrigerationSecondarySystem::isEvaporatorRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isEvaporatorRefrigerantInventoryDefaulted();
  }

  bool RefrigerationSecondarySystem::setEvaporatorRefrigerantInventory(double evaporatorRefrigerantInventory) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEvaporatorRefrigerantInventory(evaporatorRefrigerantInventory);
  }

  void RefrigerationSecondarySystem::resetEvaporatorRefrigerantInventory() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetEvaporatorRefrigerantInventory();
  }

  std::string RefrigerationSecondarySystem::endUseSubcategory() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->endUseSubcategory();
  }

  bool RefrigerationSecondarySystem::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationSecondarySystem::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationSecondarySystem_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationSecondarySystem::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationSecondarySystem_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio
