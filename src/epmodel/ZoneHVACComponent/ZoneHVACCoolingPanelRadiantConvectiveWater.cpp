/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>

#include <vector>

namespace openstudio {
namespace epmodel {

  ZoneHVACCoolingPanelRadiantConvectiveWater::ZoneHVACCoolingPanelRadiantConvectiveWater(const Model& model)
    : ZoneHVACComponent(ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType(), model) {}

  ZoneHVACCoolingPanelRadiantConvectiveWater::ZoneHVACCoolingPanelRadiantConvectiveWater(
    std::shared_ptr<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType() {
    return IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water;
  }

  std::vector<std::string> ZoneHVACCoolingPanelRadiantConvectiveWater::coolingDesignCapacityMethodValues() {
    return {"None", "CoolingDesignCapacity", "CapacityPerFloorArea", "FractionOfAutosizedCoolingCapacity"};
  }

  std::vector<std::string> ZoneHVACCoolingPanelRadiantConvectiveWater::controlTypeValues() {
    return {"MeanAirTemperature",        "MeanRadiantTemperature", "OperativeTemperature", "OutdoorDryBulbTemperature",
            "OutdoorWetBulbTemperature", "ZoneTotalLoad",          "ZoneConvectiveLoad"};
  }

  std::vector<std::string> ZoneHVACCoolingPanelRadiantConvectiveWater::condensationControlTypeValues() {
    return {"Off", "SimpleOff", "VariableOff"};
  }

  unsigned detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::inletPort() const {
    return 0u;
  }

  unsigned detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::outletPort() const {
    return 0u;
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::ratedInletWaterTemperature() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedInletWaterTemperature();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isRatedInletWaterTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedInletWaterTemperatureDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedInletWaterTemperature(ratedInletWaterTemperature);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetRatedInletWaterTemperature() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedInletWaterTemperature();
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::ratedInletSpaceTemperature() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedInletSpaceTemperature();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isRatedInletSpaceTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedInletSpaceTemperatureDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setRatedInletSpaceTemperature(double ratedInletSpaceTemperature) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedInletSpaceTemperature(ratedInletSpaceTemperature);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetRatedInletSpaceTemperature() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedInletSpaceTemperature();
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::ratedWaterMassFlowRate() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedWaterMassFlowRate();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isRatedWaterMassFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedWaterMassFlowRateDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetRatedWaterMassFlowRate() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedWaterMassFlowRate();
  }

  std::string ZoneHVACCoolingPanelRadiantConvectiveWater::coolingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacityMethod();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isCoolingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingDesignCapacityMethodDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetCoolingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCoolingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater::coolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacity();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isCoolingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingDesignCapacityAutosized();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCoolingDesignCapacity(double coolingDesignCapacity) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::autosizeCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->autosizeCoolingDesignCapacity();
  }

  boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacityPerFloorArea(
      coolingDesignCapacityPerFloorArea);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetCoolingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCoolingDesignCapacityPerFloorArea();
  }

  boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater::fractionOfAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionOfAutosizedCoolingDesignCapacity();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setFractionOfAutosizedCoolingDesignCapacity(double fractionOfAutosizedCoolingDesignCapacity) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionOfAutosizedCoolingDesignCapacity(
      fractionOfAutosizedCoolingDesignCapacity);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetFractionOfAutosizedCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetFractionOfAutosizedCoolingDesignCapacity();
  }

  boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater::maximumChilledWaterFlowRate() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->maximumChilledWaterFlowRate();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isMaximumChilledWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isMaximumChilledWaterFlowRateAutosized();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setMaximumChilledWaterFlowRate(maximumChilledWaterFlowRate);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::autosizeMaximumChilledWaterFlowRate() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->autosizeMaximumChilledWaterFlowRate();
  }

  std::string ZoneHVACCoolingPanelRadiantConvectiveWater::controlType() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->controlType();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isControlTypeDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setControlType(const std::string& controlType) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setControlType(controlType);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetControlType() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetControlType();
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::coolingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingControlThrottlingRange();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetCoolingControlThrottlingRange() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCoolingControlThrottlingRange();
  }

  std::string ZoneHVACCoolingPanelRadiantConvectiveWater::condensationControlType() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->condensationControlType();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCondensationControlTypeDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCondensationControlType(condensationControlType);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetCondensationControlType() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCondensationControlType();
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::condensationControlDewpointOffset() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->condensationControlDewpointOffset();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCondensationControlDewpointOffset(
      condensationControlDewpointOffset);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetCondensationControlDewpointOffset() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCondensationControlDewpointOffset();
  }

  double ZoneHVACCoolingPanelRadiantConvectiveWater::fractionRadiant() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionRadiant();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionRadiant(fractionRadiant);
  }

  boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater::fractionOfRadiantEnergyIncidentOnPeople() const {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionOfRadiantEnergyIncidentOnPeople();
  }

  bool ZoneHVACCoolingPanelRadiantConvectiveWater::setFractionOfRadiantEnergyIncidentOnPeople(double fractionOfRadiantEnergyIncidentOnPeople) {
    return getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionOfRadiantEnergyIncidentOnPeople(
      fractionOfRadiantEnergyIncidentOnPeople);
  }

  void ZoneHVACCoolingPanelRadiantConvectiveWater::resetFractionOfRadiantEnergyIncidentOnPeople() {
    getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetFractionOfRadiantEnergyIncidentOnPeople();
  }

  namespace detail {

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedInletWaterTemperature() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedInletWaterTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
      const bool result = setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, ratedInletWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedInletWaterTemperature() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature, ""));
    }

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedInletSpaceTemperature() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedInletSpaceTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedInletSpaceTemperature(double ratedInletSpaceTemperature) {
      const bool result = setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, ratedInletSpaceTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedInletSpaceTemperature() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature, ""));
    }

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::ratedWaterMassFlowRate() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isRatedWaterMassFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
      const bool result = setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ratedWaterMassFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetRatedWaterMassFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ""));
    }

    std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacityMethod() const {
      const auto value = getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingDesignCapacityMethodDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
      return setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, coolingDesignCapacityMethod);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingDesignCapacityMethod() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod, ""));
    }

    boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacity() const {
      return getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, true);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingDesignCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
      return setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, coolingDesignCapacity);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::autosizeCoolingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingDesignCapacityPerFloorArea() const {
      return getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, true);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
      return setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, coolingDesignCapacityPerFloorArea);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingDesignCapacityPerFloorArea() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea, ""));
    }

    boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionOfAutosizedCoolingDesignCapacity() const {
      return getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity, true);
    }

    bool
      ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionOfAutosizedCoolingDesignCapacity(double fractionOfAutosizedCoolingDesignCapacity) {
      return setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity,
                       fractionOfAutosizedCoolingDesignCapacity);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetFractionOfAutosizedCoolingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity, ""));
    }

    boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::maximumChilledWaterFlowRate() const {
      return getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, true);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isMaximumChilledWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, maximumChilledWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::autosizeMaximumChilledWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate, "autosize"));
    }

    std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::controlType() const {
      const auto value = getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setControlType(const std::string& controlType) {
      return setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, controlType);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetControlType() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType, ""));
    }

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::coolingControlThrottlingRange() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
      const bool result =
        setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, coolingControlThrottlingRange);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCoolingControlThrottlingRange() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange, ""));
    }

    std::string ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::condensationControlType() const {
      const auto value = getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCondensationControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCondensationControlType(const std::string& condensationControlType) {
      return setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, condensationControlType);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCondensationControlType() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType, ""));
    }

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::condensationControlDewpointOffset() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      return isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
      const bool result =
        setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, condensationControlDewpointOffset);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetCondensationControlDewpointOffset() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset, ""));
    }

    double ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionRadiant() const {
      auto value = getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionRadiant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionRadiant(double fractionRadiant) {
      return setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionRadiant, fractionRadiant);
    }

    boost::optional<double> ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::fractionOfRadiantEnergyIncidentOnPeople() const {
      return getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofRadiantEnergyIncidentonPeople, true);
    }

    bool ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::setFractionOfRadiantEnergyIncidentOnPeople(double fractionOfRadiantEnergyIncidentOnPeople) {
      return setDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofRadiantEnergyIncidentonPeople,
                       fractionOfRadiantEnergyIncidentOnPeople);
    }

    void ZoneHVACCoolingPanelRadiantConvectiveWater_Impl::resetFractionOfRadiantEnergyIncidentOnPeople() {
      OS_ASSERT(setString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofRadiantEnergyIncidentonPeople, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
