/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {
    constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
    constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
    constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
    constexpr double kDefaultHydronicTubingConductivity = 0.35;
    constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
    constexpr const char* kDefaultSetpointControlType = "HalfFlowPower";
    constexpr const char* kDefaultHeatingDesignCapacityMethod = "HeatingDesignCapacity";
    constexpr double kDefaultFractionofAutosizedHeatingDesignCapacity = 1.0;
    constexpr double kDefaultHeatingControlThrottlingRange = 0.5;
    constexpr const char* kDefaultCoolingDesignCapacityMethod = "CoolingDesignCapacity";
    constexpr double kDefaultCoolingControlThrottlingRange = 0.5;
    constexpr const char* kDefaultCondensationControlType = "SimpleOff";
    constexpr double kDefaultCondensationControlDewpointOffset = 1.0;
  }  // namespace detail

  ZoneHVACLowTempRadiantVarFlowDesign::ZoneHVACLowTempRadiantVarFlowDesign(const Model& model)
    : ModelObject(ZoneHVACLowTempRadiantVarFlowDesign::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>());
  }

  ZoneHVACLowTempRadiantVarFlowDesign::ZoneHVACLowTempRadiantVarFlowDesign(std::shared_ptr<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACLowTempRadiantVarFlowDesign::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::fluidtoRadiantSurfaceHeatTransferModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::setpointControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::coolingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlowDesign::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType);
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign::heatingControlTemperatureSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingControlTemperatureSchedule();
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign::coolingControlTemperatureSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingControlTemperatureSchedule();
  }

  boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign::changeoverDelayTimePeriodSchedule() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->changeoverDelayTimePeriodSchedule();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::fluidtoRadiantSurfaceHeatTransferModel() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::hydronicTubingInsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingInsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isHydronicTubingInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingInsideDiameterDefaulted();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::hydronicTubingOutsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingOutsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isHydronicTubingOutsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::hydronicTubingConductivity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->hydronicTubingConductivity();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isHydronicTubingConductivityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHydronicTubingConductivityDefaulted();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isTemperatureControlTypeDefaulted();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::setpointControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setpointControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isSetpointControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isSetpointControlTypeDefaulted();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isHeatingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHeatingDesignCapacityMethodDefaulted();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::heatingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isHeatingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHeatingControlThrottlingRangeDefaulted();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::coolingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isCoolingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCoolingDesignCapacityMethodDefaulted();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign::fractionofAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fractionofAutosizedCoolingDesignCapacity();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::coolingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  std::string ZoneHVACLowTempRadiantVarFlowDesign::condensationControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlTypeDefaulted();
  }

  double ZoneHVACLowTempRadiantVarFlowDesign::condensationControlDewpointOffset() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlDewpointOffset();
  }

  bool ZoneHVACLowTempRadiantVarFlowDesign::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  namespace detail {

    boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign_Impl::heatingControlTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlTemperatureScheduleName);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHeatingControlTemperatureSchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlTemperatureScheduleName,
                        schedule.handle(), false);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHeatingControlTemperatureSchedule() {
      OS_ASSERT(
        setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlTemperatureScheduleName, Handle(), false));
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign_Impl::coolingControlTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCoolingControlTemperatureSchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName,
                        schedule.handle(), false);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCoolingControlTemperatureSchedule() {
      OS_ASSERT(
        setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName, Handle(), false));
    }

    boost::optional<Schedule> ZoneHVACLowTempRadiantVarFlowDesign_Impl::changeoverDelayTimePeriodSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::ChangeoverDelayTimePeriodSchedule);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
      return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, schedule.handle(),
                        false);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetChangeoverDelayTimePeriodSchedule() {
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, Handle(), false));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
      if (const auto value =
            getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, true)) {
        return *value;
      }
      return kDefaultFluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::hydronicTubingInsideDiameter() const {
      if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingInsideDiameter, true)) {
        return *value;
      }
      return kDefaultHydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isHydronicTubingInsideDiameterDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingInsideDiameter);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHydronicTubingInsideDiameter(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingInsideDiameter, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHydronicTubingInsideDiameter() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingInsideDiameter, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::hydronicTubingOutsideDiameter() const {
      if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingOutsideDiameter, true)) {
        return *value;
      }
      return kDefaultHydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingOutsideDiameter);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHydronicTubingOutsideDiameter(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingOutsideDiameter, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHydronicTubingOutsideDiameter() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingOutsideDiameter, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::hydronicTubingConductivity() const {
      if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingConductivity, true)) {
        return *value;
      }
      return kDefaultHydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isHydronicTubingConductivityDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingConductivity);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHydronicTubingConductivity(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingConductivity, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHydronicTubingConductivity() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingConductivity, ""));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::temperatureControlType() const {
      if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType, true)) {
        return *value;
      }
      return kDefaultTemperatureControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isTemperatureControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setTemperatureControlType(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetTemperatureControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType, ""));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::setpointControlType() const {
      if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType, true)) {
        return *value;
      }
      return kDefaultSetpointControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isSetpointControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setSetpointControlType(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetSetpointControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType, ""));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::heatingDesignCapacityMethod() const {
      if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod, true)) {
        return *value;
      }
      return kDefaultHeatingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isHeatingDesignCapacityMethodDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHeatingDesignCapacityMethod(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHeatingDesignCapacityMethod() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod, ""));
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign_Impl::heatingDesignCapacityPerFloorArea() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityPerFloorArea, true);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHeatingDesignCapacityPerFloorArea(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityPerFloorArea, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHeatingDesignCapacityPerFloorArea() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityPerFloorArea, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      if (const auto value =
            getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedHeatingDesignCapacity, true)) {
        return *value;
      }
      return kDefaultFractionofAutosizedHeatingDesignCapacity;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedHeatingDesignCapacity);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setFractionofAutosizedHeatingDesignCapacity(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedHeatingDesignCapacity, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedHeatingDesignCapacity, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::heatingControlThrottlingRange() const {
      if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlThrottlingRange, true)) {
        return *value;
      }
      return kDefaultHeatingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isHeatingControlThrottlingRangeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlThrottlingRange);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setHeatingControlThrottlingRange(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlThrottlingRange, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetHeatingControlThrottlingRange() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlThrottlingRange, ""));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::coolingDesignCapacityMethod() const {
      if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, true)) {
        return *value;
      }
      return kDefaultCoolingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isCoolingDesignCapacityMethodDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCoolingDesignCapacityMethod(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCoolingDesignCapacityMethod() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, ""));
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign_Impl::coolingDesignCapacityPerFloorArea() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, true);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCoolingDesignCapacityPerFloorArea(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCoolingDesignCapacityPerFloorArea() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, ""));
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlowDesign_Impl::fractionofAutosizedCoolingDesignCapacity() const {
      return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, true);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setFractionofAutosizedCoolingDesignCapacity(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetFractionofAutosizedCoolingDesignCapacity() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::coolingControlThrottlingRange() const {
      if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, true)) {
        return *value;
      }
      return kDefaultCoolingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCoolingControlThrottlingRange(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCoolingControlThrottlingRange() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, ""));
    }

    std::string ZoneHVACLowTempRadiantVarFlowDesign_Impl::condensationControlType() const {
      if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, true)) {
        return *value;
      }
      return kDefaultCondensationControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isCondensationControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCondensationControlType(const std::string& value) {
      return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCondensationControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, ""));
    }

    double ZoneHVACLowTempRadiantVarFlowDesign_Impl::condensationControlDewpointOffset() const {
      if (const auto value =
            getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, true)) {
        return *value;
      }
      return kDefaultCondensationControlDewpointOffset;
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset);
    }

    bool ZoneHVACLowTempRadiantVarFlowDesign_Impl::setCondensationControlDewpointOffset(double value) {
      return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, value);
    }

    void ZoneHVACLowTempRadiantVarFlowDesign_Impl::resetCondensationControlDewpointOffset() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
