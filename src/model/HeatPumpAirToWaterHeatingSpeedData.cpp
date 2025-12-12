/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpAirToWaterHeatingSpeedData.hpp"
#include "HeatPumpAirToWaterHeatingSpeedData_Impl.hpp"

#include "HeatPumpAirToWaterHeating.hpp"
#include "HeatPumpAirToWaterHeating_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Curve.hpp"
#include "Curve_Impl.hpp"
#include "CurveBiquadratic.hpp"
#include "CurveQuadratic.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_HeatPump_AirToWater_Heating_SpeedData_FieldEnums.hxx>

#include <fmt/format.h>

namespace openstudio {
namespace model {

  namespace detail {

    HeatPumpAirToWaterHeatingSpeedData_Impl::HeatPumpAirToWaterHeatingSpeedData_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == HeatPumpAirToWaterHeatingSpeedData::iddObjectType());
    }

    HeatPumpAirToWaterHeatingSpeedData_Impl::HeatPumpAirToWaterHeatingSpeedData_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == HeatPumpAirToWaterHeatingSpeedData::iddObjectType());
    }

    HeatPumpAirToWaterHeatingSpeedData_Impl::HeatPumpAirToWaterHeatingSpeedData_Impl(const HeatPumpAirToWaterHeatingSpeedData_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& HeatPumpAirToWaterHeatingSpeedData_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    IddObjectType HeatPumpAirToWaterHeatingSpeedData_Impl::iddObjectType() const {
      return HeatPumpAirToWaterHeatingSpeedData::iddObjectType();
    }

    std::vector<ModelObject> HeatPumpAirToWaterHeatingSpeedData_Impl::children() const {
      std::vector<ModelObject> children;
      if (auto c_ = optionalNormalizedHeatingCapacityFunctionofTemperatureCurve()) {
        children.push_back(*c_);
      }
      if (auto c_ = optionalHeatingEnergyInputRatioFunctionofTemperatureCurve()) {
        children.push_back(*c_);
      }
      if (auto c_ = optionalHeatingEnergyInputRatioFunctionofPLRCurve()) {
        children.push_back(*c_);
      }

      return children;
    }

    ModelObject HeatPumpAirToWaterHeatingSpeedData_Impl::clone(Model model) const {
      // Don't clone the curves (listed as children)
      return ModelObject_Impl::clone(model);  // NOLINT(bugprone-parent-virtual-call)
    }

    boost::optional<double> HeatPumpAirToWaterHeatingSpeedData_Impl::ratedHeatingCapacity() const {
      return getDouble(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedHeatingCapacity, true);
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::isRatedHeatingCapacityAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedHeatingCapacity, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterHeatingSpeedData_Impl::autosizedRatedHeatingCapacity() {
      boost::optional<double> result;
      auto awhp_hcs = heatPumpAirToWaterHeatings();
      if (awhp_hcs.empty()) {
        return result;
      }
      size_t n_found = 0;
      for (const auto& awhp_hc : awhp_hcs) {
        // Check needed because could be the booster speed
        if (awhp_hc.speeds().empty()) {
          continue;
        }
        // It has to be the last speed
        if (awhp_hc.speeds().back().handle() != this->handle()) {
          continue;
        }
        if (n_found == 0) {
          // Setting the first one only
          result = awhp_hc.autosizedRatedHeatingCapacity();
        }
        ++n_found;
      }
      if (n_found > 1) {
        LOG(Warn, briefDescription() << " is used as the highest speed in multiple HeatPumpAirToWaterHeating objects, "
                                        "returning the autosized value from the first one only.");
      }

      return result;
    }

    double HeatPumpAirToWaterHeatingSpeedData_Impl::ratedCOPforHeating() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedCOPforHeating, true);
      OS_ASSERT(value);
      return value.get();
    }

    Curve HeatPumpAirToWaterHeatingSpeedData_Impl::normalizedHeatingCapacityFunctionofTemperatureCurve() const {
      boost::optional<Curve> value = optionalNormalizedHeatingCapacityFunctionofTemperatureCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Normalized Heating Capacity Functionof Temperature Curve attached.");
      }
      return value.get();
    }

    Curve HeatPumpAirToWaterHeatingSpeedData_Impl::heatingEnergyInputRatioFunctionofTemperatureCurve() const {
      boost::optional<Curve> value = optionalHeatingEnergyInputRatioFunctionofTemperatureCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Heating Energy Input Ratio Functionof Temperature Curve attached.");
      }
      return value.get();
    }

    Curve HeatPumpAirToWaterHeatingSpeedData_Impl::heatingEnergyInputRatioFunctionofPLRCurve() const {
      boost::optional<Curve> value = optionalHeatingEnergyInputRatioFunctionofPLRCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Heating Energy Input Ratio Functionof PLRCurve attached.");
      }
      return value.get();
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
      const bool result = setDouble(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedHeatingCapacity, ratedHeatingCapacity);
      return result;
    }

    void HeatPumpAirToWaterHeatingSpeedData_Impl::autosizeRatedHeatingCapacity() {
      const bool result = setString(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedHeatingCapacity, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::setRatedCOPforHeating(double ratedCOPforHeating) {
      const bool result = setDouble(OS_HeatPump_AirToWater_Heating_SpeedDataFields::RatedCOPforHeating, ratedCOPforHeating);
      return result;
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::setNormalizedHeatingCapacityFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
      const bool result = setPointer(OS_HeatPump_AirToWater_Heating_SpeedDataFields::NormalizedHeatingCapacityFunctionofTemperatureCurveName,
                                     bivariateFunctions.handle());
      return result;
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::setHeatingEnergyInputRatioFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
      const bool result = setPointer(OS_HeatPump_AirToWater_Heating_SpeedDataFields::HeatingEnergyInputRatioFunctionofTemperatureCurveName,
                                     bivariateFunctions.handle());
      return result;
    }

    bool HeatPumpAirToWaterHeatingSpeedData_Impl::setHeatingEnergyInputRatioFunctionofPLRCurve(const Curve& univariateFunctions) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_Heating_SpeedDataFields::HeatingEnergyInputRatioFunctionofPLRCurveName, univariateFunctions.handle());
      return result;
    }

    void HeatPumpAirToWaterHeatingSpeedData_Impl::autosize() {
      autosizeRatedHeatingCapacity();
    }

    void HeatPumpAirToWaterHeatingSpeedData_Impl::applySizingValues() {
      if (boost::optional<double> val_ = autosizedRatedHeatingCapacity()) {
        setRatedHeatingCapacity(*val_);
      }
    }

    boost::optional<Curve> HeatPumpAirToWaterHeatingSpeedData_Impl::optionalNormalizedHeatingCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Heating_SpeedDataFields::NormalizedHeatingCapacityFunctionofTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterHeatingSpeedData_Impl::optionalHeatingEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Heating_SpeedDataFields::HeatingEnergyInputRatioFunctionofTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterHeatingSpeedData_Impl::optionalHeatingEnergyInputRatioFunctionofPLRCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Heating_SpeedDataFields::HeatingEnergyInputRatioFunctionofPLRCurveName);
    }

    std::vector<HeatPumpAirToWaterHeating> HeatPumpAirToWaterHeatingSpeedData_Impl::heatPumpAirToWaterHeatings() const {
      std::vector<HeatPumpAirToWaterHeating> result;

      const auto handle = this->handle();

      for (const auto& awhp : model().getConcreteModelObjects<HeatPumpAirToWaterHeating>()) {
        if (awhp.boosterModeOnSpeed() && awhp.boosterModeOnSpeed()->handle() == handle) {
          result.push_back(awhp);
        } else {
          const auto speeds = awhp.speeds();
          if (std::find_if(speeds.cbegin(), speeds.cend(),
                           [handle](const HeatPumpAirToWaterHeatingSpeedData& speed) { return speed.handle() == handle; })
              != speeds.end()) {
            result.push_back(awhp);
          }
        }
      }
      return result;
    }

  }  // namespace detail

  HeatPumpAirToWaterHeatingSpeedData::HeatPumpAirToWaterHeatingSpeedData(const Model& model)
    : ResourceObject(HeatPumpAirToWaterHeatingSpeedData::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>());

    autosizeRatedHeatingCapacity();
    setRatedCOPforHeating(3.0);

    bool ok = true;
    {
      CurveBiquadratic capFT(model);
      capFT.setName(fmt::format("{} CapCurveFuncTempHT", this->nameString()));
      capFT.setCoefficient1Constant(0.885);
      capFT.setCoefficient2x(-0.00040);
      capFT.setCoefficient3xPOW2(0.00019);
      capFT.setCoefficient4y(0.0202);
      capFT.setCoefficient5yPOW2(-0.0096);
      capFT.setCoefficient6xTIMESY(0.000580);
      capFT.setMinimumValueofx(30.0);
      capFT.setMaximumValueofx(50.0);
      capFT.setMinimumValueofy(-7.0);
      capFT.setMaximumValueofy(20.0);
      capFT.setMinimumCurveOutput(0.5);
      capFT.setMaximumCurveOutput(1.3);
      capFT.setInputUnitTypeforX("Temperature");
      capFT.setInputUnitTypeforY("Temperature");
      capFT.setOutputUnitType("Dimensionless");

      ok = setNormalizedHeatingCapacityFunctionofTemperatureCurve(capFT);
      OS_ASSERT(ok);
    }

    {
      CurveBiquadratic eirFT(model);
      eirFT.setName(fmt::format("{} EIRCurveFuncTempHT", this->nameString()));
      eirFT.setCoefficient1Constant(1.055);
      eirFT.setCoefficient2x(0.00035);
      eirFT.setCoefficient3xPOW2(-0.00027);
      eirFT.setCoefficient4y(-0.0108);
      eirFT.setCoefficient5yPOW2(0.0145);
      eirFT.setCoefficient6xTIMESY(-0.000230);
      eirFT.setMinimumValueofx(30.0);
      eirFT.setMaximumValueofx(50.0);
      eirFT.setMinimumValueofy(-7.0);
      eirFT.setMaximumValueofy(20.0);
      eirFT.setMinimumCurveOutput(0.7);
      eirFT.setMaximumCurveOutput(1.5);
      eirFT.setInputUnitTypeforX("Temperature");
      eirFT.setInputUnitTypeforY("Temperature");
      eirFT.setOutputUnitType("Dimensionless");

      ok = setHeatingEnergyInputRatioFunctionofTemperatureCurve(eirFT);
      OS_ASSERT(ok);
    }

    {
      CurveQuadratic eirfPLR(model);
      eirfPLR.setName(fmt::format("{} EIRCurveFuncPLR", this->nameString()));
      eirfPLR.setCoefficient1Constant(1.0);
      eirfPLR.setCoefficient2x(0.0);
      eirfPLR.setCoefficient3xPOW2(0.0);
      eirfPLR.setMinimumValueofx(0.0);
      eirfPLR.setMaximumValueofx(1.0);
      eirfPLR.setMinimumCurveOutput(0.0);
      eirfPLR.setMaximumCurveOutput(1.0);
      eirfPLR.setInputUnitTypeforX("Dimensionless");
      eirfPLR.setOutputUnitType("Dimensionless");
      ok = setHeatingEnergyInputRatioFunctionofPLRCurve(eirfPLR);
      OS_ASSERT(ok);
    }
  }

  HeatPumpAirToWaterHeatingSpeedData::HeatPumpAirToWaterHeatingSpeedData(const Model& model,
                                                                         const Curve& normalizedHeatingCapacityFunctionofTemperatureCurve,
                                                                         const Curve& heatingEnergyInputRatioFunctionofTemperatureCurve,
                                                                         const Curve& heatingEnergyInputRatioFunctionofPLRCurve)
    : ResourceObject(HeatPumpAirToWaterHeatingSpeedData::iddObjectType(), model) {

    auto impl = getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>();
    OS_ASSERT(impl);

    autosizeRatedHeatingCapacity();
    setRatedCOPforHeating(3.0);

    bool ok = setNormalizedHeatingCapacityFunctionofTemperatureCurve(normalizedHeatingCapacityFunctionofTemperatureCurve);
    if (!ok) {
      // We don't call remove() (which would do ResourceObject::remove()) because that would try to remove the curves too if they aren't being used,
      // so we call ModelObject::remove() directly
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s Capacity Curve to "
                                     << normalizedHeatingCapacityFunctionofTemperatureCurve.briefDescription() << ".");
    }
    ok = setHeatingEnergyInputRatioFunctionofTemperatureCurve(heatingEnergyInputRatioFunctionofTemperatureCurve);
    if (!ok) {
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s EIRfT Curve to "
                                     << heatingEnergyInputRatioFunctionofTemperatureCurve.briefDescription() << ".");
    }
    ok = setHeatingEnergyInputRatioFunctionofPLRCurve(heatingEnergyInputRatioFunctionofPLRCurve);
    if (!ok) {
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s EIRfPLR Curve to " << heatingEnergyInputRatioFunctionofPLRCurve.briefDescription()
                                     << ".");
    }
  }

  IddObjectType HeatPumpAirToWaterHeatingSpeedData::iddObjectType() {
    return {IddObjectType::OS_HeatPump_AirToWater_Heating_SpeedData};
  }

  boost::optional<double> HeatPumpAirToWaterHeatingSpeedData::ratedHeatingCapacity() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->ratedHeatingCapacity();
  }

  bool HeatPumpAirToWaterHeatingSpeedData::isRatedHeatingCapacityAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->isRatedHeatingCapacityAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterHeatingSpeedData::autosizedRatedHeatingCapacity() {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->autosizedRatedHeatingCapacity();
  }

  double HeatPumpAirToWaterHeatingSpeedData::ratedCOPforHeating() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->ratedCOPforHeating();
  }

  Curve HeatPumpAirToWaterHeatingSpeedData::normalizedHeatingCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->normalizedHeatingCapacityFunctionofTemperatureCurve();
  }

  Curve HeatPumpAirToWaterHeatingSpeedData::heatingEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->heatingEnergyInputRatioFunctionofTemperatureCurve();
  }

  Curve HeatPumpAirToWaterHeatingSpeedData::heatingEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->heatingEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterHeatingSpeedData::setRatedHeatingCapacity(double ratedHeatingCapacity) {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
  }

  void HeatPumpAirToWaterHeatingSpeedData::autosizeRatedHeatingCapacity() {
    getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->autosizeRatedHeatingCapacity();
  }

  bool HeatPumpAirToWaterHeatingSpeedData::setRatedCOPforHeating(double ratedCOPforHeating) {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->setRatedCOPforHeating(ratedCOPforHeating);
  }

  bool HeatPumpAirToWaterHeatingSpeedData::setNormalizedHeatingCapacityFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->setNormalizedHeatingCapacityFunctionofTemperatureCurve(bivariateFunctions);
  }

  bool HeatPumpAirToWaterHeatingSpeedData::setHeatingEnergyInputRatioFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->setHeatingEnergyInputRatioFunctionofTemperatureCurve(bivariateFunctions);
  }

  bool HeatPumpAirToWaterHeatingSpeedData::setHeatingEnergyInputRatioFunctionofPLRCurve(const Curve& univariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->setHeatingEnergyInputRatioFunctionofPLRCurve(univariateFunctions);
  }

  /// @cond
  HeatPumpAirToWaterHeatingSpeedData::HeatPumpAirToWaterHeatingSpeedData(std::shared_ptr<detail::HeatPumpAirToWaterHeatingSpeedData_Impl> impl)
    : ResourceObject(std::move(impl)) {}
  /// @endcond

  void HeatPumpAirToWaterHeatingSpeedData::autosize() {
    getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->autosizeRatedHeatingCapacity();
  }

  // TODO: needed?
  // void HeatPumpAirToWaterHeatingSpeedData::applySizingValues() {
  //   getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->applySizingValues();
  // }

  std::vector<HeatPumpAirToWaterHeating> HeatPumpAirToWaterHeatingSpeedData::heatPumpAirToWaterHeatings() const {
    return getImpl<detail::HeatPumpAirToWaterHeatingSpeedData_Impl>()->heatPumpAirToWaterHeatings();
  }

}  // namespace model
}  // namespace openstudio
