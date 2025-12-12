/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "HeatPumpAirToWaterCoolingSpeedData_Impl.hpp"

#include "HeatPumpAirToWaterCooling.hpp"
#include "HeatPumpAirToWaterCooling_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Curve.hpp"
#include "Curve_Impl.hpp"
#include "CurveBiquadratic.hpp"
#include "CurveQuadratic.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_HeatPump_AirToWater_Cooling_SpeedData_FieldEnums.hxx>

#include <fmt/format.h>

namespace openstudio {
namespace model {

  namespace detail {

    HeatPumpAirToWaterCoolingSpeedData_Impl::HeatPumpAirToWaterCoolingSpeedData_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == HeatPumpAirToWaterCoolingSpeedData::iddObjectType());
    }

    HeatPumpAirToWaterCoolingSpeedData_Impl::HeatPumpAirToWaterCoolingSpeedData_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == HeatPumpAirToWaterCoolingSpeedData::iddObjectType());
    }

    HeatPumpAirToWaterCoolingSpeedData_Impl::HeatPumpAirToWaterCoolingSpeedData_Impl(const HeatPumpAirToWaterCoolingSpeedData_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ResourceObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& HeatPumpAirToWaterCoolingSpeedData_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    IddObjectType HeatPumpAirToWaterCoolingSpeedData_Impl::iddObjectType() const {
      return HeatPumpAirToWaterCoolingSpeedData::iddObjectType();
    }

    std::vector<ModelObject> HeatPumpAirToWaterCoolingSpeedData_Impl::children() const {
      std::vector<ModelObject> children;
      if (auto c_ = optionalNormalizedCoolingCapacityFunctionofTemperatureCurve()) {
        children.push_back(*c_);
      }
      if (auto c_ = optionalCoolingEnergyInputRatioFunctionofTemperatureCurve()) {
        children.push_back(*c_);
      }
      if (auto c_ = optionalCoolingEnergyInputRatioFunctionofPLRCurve()) {
        children.push_back(*c_);
      }

      return children;
    }

    ModelObject HeatPumpAirToWaterCoolingSpeedData_Impl::clone(Model model) const {
      // Don't clone the curves (listed as children)
      return ModelObject_Impl::clone(model);  // NOLINT(bugprone-parent-virtual-call)
    }

    boost::optional<double> HeatPumpAirToWaterCoolingSpeedData_Impl::ratedCoolingCapacity() const {
      return getDouble(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCoolingCapacity, true);
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::isRatedCoolingCapacityAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCoolingCapacity, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterCoolingSpeedData_Impl::autosizedRatedCoolingCapacity() {
      boost::optional<double> result;
      auto awhp_ccs = heatPumpAirToWaterCoolings();
      if (awhp_ccs.empty()) {
        return result;
      }
      size_t n_found = 0;
      for (const auto& awhp_cc : awhp_ccs) {
        // Check needed because could be the booster speed
        if (awhp_cc.speeds().empty()) {
          continue;
        }
        // It has to be the last speed
        if (awhp_cc.speeds().back().handle() != this->handle()) {
          continue;
        }
        if (n_found == 0) {
          // Setting the first one only
          result = awhp_cc.autosizedRatedCoolingCapacity();
        }
        ++n_found;
      }
      if (n_found > 1) {
        LOG(Warn, briefDescription() << " is used as the highest speed in multiple HeatPumpAirToWaterCooling objects, "
                                        "returning the autosized value from the first one only.");
      }

      return result;
    }

    double HeatPumpAirToWaterCoolingSpeedData_Impl::ratedCOPforCooling() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCOPforCooling, true);
      OS_ASSERT(value);
      return value.get();
    }

    Curve HeatPumpAirToWaterCoolingSpeedData_Impl::normalizedCoolingCapacityFunctionofTemperatureCurve() const {
      boost::optional<Curve> value = optionalNormalizedCoolingCapacityFunctionofTemperatureCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Normalized Cooling Capacity Functionof Temperature Curve attached.");
      }
      return value.get();
    }

    Curve HeatPumpAirToWaterCoolingSpeedData_Impl::coolingEnergyInputRatioFunctionofTemperatureCurve() const {
      boost::optional<Curve> value = optionalCoolingEnergyInputRatioFunctionofTemperatureCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Cooling Energy Input Ratio Functionof Temperature Curve attached.");
      }
      return value.get();
    }

    Curve HeatPumpAirToWaterCoolingSpeedData_Impl::coolingEnergyInputRatioFunctionofPLRCurve() const {
      boost::optional<Curve> value = optionalCoolingEnergyInputRatioFunctionofPLRCurve();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Cooling Energy Input Ratio Functionof PLRCurve attached.");
      }
      return value.get();
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::setRatedCoolingCapacity(double ratedCoolingCapacity) {
      const bool result = setDouble(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCoolingCapacity, ratedCoolingCapacity);
      return result;
    }

    void HeatPumpAirToWaterCoolingSpeedData_Impl::autosizeRatedCoolingCapacity() {
      const bool result = setString(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::setRatedCOPforCooling(double ratedCOPforCooling) {
      const bool result = setDouble(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::RatedCOPforCooling, ratedCOPforCooling);
      return result;
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::setNormalizedCoolingCapacityFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
      const bool result = setPointer(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::NormalizedCoolingCapacityFunctionofTemperatureCurveName,
                                     bivariateFunctions.handle());
      return result;
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::setCoolingEnergyInputRatioFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
      const bool result = setPointer(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::CoolingEnergyInputRatioFunctionofTemperatureCurveName,
                                     bivariateFunctions.handle());
      return result;
    }

    bool HeatPumpAirToWaterCoolingSpeedData_Impl::setCoolingEnergyInputRatioFunctionofPLRCurve(const Curve& univariateFunctions) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_Cooling_SpeedDataFields::CoolingEnergyInputRatioFunctionofPLRCurveName, univariateFunctions.handle());
      return result;
    }

    void HeatPumpAirToWaterCoolingSpeedData_Impl::autosize() {
      autosizeRatedCoolingCapacity();
    }

    void HeatPumpAirToWaterCoolingSpeedData_Impl::applySizingValues() {
      if (boost::optional<double> val_ = autosizedRatedCoolingCapacity()) {
        setRatedCoolingCapacity(*val_);
      }
    }

    boost::optional<Curve> HeatPumpAirToWaterCoolingSpeedData_Impl::optionalNormalizedCoolingCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Cooling_SpeedDataFields::NormalizedCoolingCapacityFunctionofTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterCoolingSpeedData_Impl::optionalCoolingEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Cooling_SpeedDataFields::CoolingEnergyInputRatioFunctionofTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterCoolingSpeedData_Impl::optionalCoolingEnergyInputRatioFunctionofPLRCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        OS_HeatPump_AirToWater_Cooling_SpeedDataFields::CoolingEnergyInputRatioFunctionofPLRCurveName);
    }

    std::vector<HeatPumpAirToWaterCooling> HeatPumpAirToWaterCoolingSpeedData_Impl::heatPumpAirToWaterCoolings() const {
      std::vector<HeatPumpAirToWaterCooling> result;

      const auto handle = this->handle();

      for (const auto& awhp : model().getConcreteModelObjects<HeatPumpAirToWaterCooling>()) {
        if (awhp.boosterModeOnSpeed() && awhp.boosterModeOnSpeed()->handle() == handle) {
          result.push_back(awhp);
        } else {
          const auto speeds = awhp.speeds();
          if (std::find_if(speeds.cbegin(), speeds.cend(),
                           [handle](const HeatPumpAirToWaterCoolingSpeedData& speed) { return speed.handle() == handle; })
              != speeds.end()) {
            result.push_back(awhp);
          }
        }
      }
      return result;
    }

  }  // namespace detail

  HeatPumpAirToWaterCoolingSpeedData::HeatPumpAirToWaterCoolingSpeedData(const Model& model)
    : ResourceObject(HeatPumpAirToWaterCoolingSpeedData::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>());

    autosizeRatedCoolingCapacity();
    setRatedCOPforCooling(3.0);

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

      ok = setNormalizedCoolingCapacityFunctionofTemperatureCurve(capFT);
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

      ok = setCoolingEnergyInputRatioFunctionofTemperatureCurve(eirFT);
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
      ok = setCoolingEnergyInputRatioFunctionofPLRCurve(eirfPLR);
      OS_ASSERT(ok);
    }
  }

  HeatPumpAirToWaterCoolingSpeedData::HeatPumpAirToWaterCoolingSpeedData(const Model& model,
                                                                         const Curve& normalizedCoolingCapacityFunctionofTemperatureCurve,
                                                                         const Curve& coolingEnergyInputRatioFunctionofTemperatureCurve,
                                                                         const Curve& coolingEnergyInputRatioFunctionofPLRCurve)
    : ResourceObject(HeatPumpAirToWaterCoolingSpeedData::iddObjectType(), model) {

    auto impl = getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>();
    OS_ASSERT(impl);

    autosizeRatedCoolingCapacity();
    setRatedCOPforCooling(3.0);

    bool ok = setNormalizedCoolingCapacityFunctionofTemperatureCurve(normalizedCoolingCapacityFunctionofTemperatureCurve);
    if (!ok) {
      // We don't call remove() (which would do ResourceObject::remove()) because that would try to remove the curves too if they aren't being used,
      // so we call ModelObject::remove() directly
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s Capacity Curve to "
                                     << normalizedCoolingCapacityFunctionofTemperatureCurve.briefDescription() << ".");
    }
    ok = setCoolingEnergyInputRatioFunctionofTemperatureCurve(coolingEnergyInputRatioFunctionofTemperatureCurve);
    if (!ok) {
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s EIRfT Curve to "
                                     << coolingEnergyInputRatioFunctionofTemperatureCurve.briefDescription() << ".");
    }
    ok = setCoolingEnergyInputRatioFunctionofPLRCurve(coolingEnergyInputRatioFunctionofPLRCurve);
    if (!ok) {
      impl->detail::ModelObject_Impl::remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s EIRfPLR Curve to " << coolingEnergyInputRatioFunctionofPLRCurve.briefDescription()
                                     << ".");
    }
  }

  IddObjectType HeatPumpAirToWaterCoolingSpeedData::iddObjectType() {
    return {IddObjectType::OS_HeatPump_AirToWater_Cooling_SpeedData};
  }

  boost::optional<double> HeatPumpAirToWaterCoolingSpeedData::ratedCoolingCapacity() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->ratedCoolingCapacity();
  }

  bool HeatPumpAirToWaterCoolingSpeedData::isRatedCoolingCapacityAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->isRatedCoolingCapacityAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterCoolingSpeedData::autosizedRatedCoolingCapacity() {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->autosizedRatedCoolingCapacity();
  }

  double HeatPumpAirToWaterCoolingSpeedData::ratedCOPforCooling() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->ratedCOPforCooling();
  }

  Curve HeatPumpAirToWaterCoolingSpeedData::normalizedCoolingCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->normalizedCoolingCapacityFunctionofTemperatureCurve();
  }

  Curve HeatPumpAirToWaterCoolingSpeedData::coolingEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->coolingEnergyInputRatioFunctionofTemperatureCurve();
  }

  Curve HeatPumpAirToWaterCoolingSpeedData::coolingEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->coolingEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterCoolingSpeedData::setRatedCoolingCapacity(double ratedCoolingCapacity) {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->setRatedCoolingCapacity(ratedCoolingCapacity);
  }

  void HeatPumpAirToWaterCoolingSpeedData::autosizeRatedCoolingCapacity() {
    getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->autosizeRatedCoolingCapacity();
  }

  bool HeatPumpAirToWaterCoolingSpeedData::setRatedCOPforCooling(double ratedCOPforCooling) {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->setRatedCOPforCooling(ratedCOPforCooling);
  }

  bool HeatPumpAirToWaterCoolingSpeedData::setNormalizedCoolingCapacityFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->setNormalizedCoolingCapacityFunctionofTemperatureCurve(bivariateFunctions);
  }

  bool HeatPumpAirToWaterCoolingSpeedData::setCoolingEnergyInputRatioFunctionofTemperatureCurve(const Curve& bivariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->setCoolingEnergyInputRatioFunctionofTemperatureCurve(bivariateFunctions);
  }

  bool HeatPumpAirToWaterCoolingSpeedData::setCoolingEnergyInputRatioFunctionofPLRCurve(const Curve& univariateFunctions) {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->setCoolingEnergyInputRatioFunctionofPLRCurve(univariateFunctions);
  }

  /// @cond
  HeatPumpAirToWaterCoolingSpeedData::HeatPumpAirToWaterCoolingSpeedData(std::shared_ptr<detail::HeatPumpAirToWaterCoolingSpeedData_Impl> impl)
    : ResourceObject(std::move(impl)) {}
  /// @endcond

  void HeatPumpAirToWaterCoolingSpeedData::autosize() {
    getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->autosize();
  }

  // TODO: needed?
  // void HeatPumpAirToWaterCoolingSpeedData::applySizingValues() {
  //   getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->applySizingValues();
  // }

  std::vector<HeatPumpAirToWaterCooling> HeatPumpAirToWaterCoolingSpeedData::heatPumpAirToWaterCoolings() const {
    return getImpl<detail::HeatPumpAirToWaterCoolingSpeedData_Impl>()->heatPumpAirToWaterCoolings();
  }

}  // namespace model
}  // namespace openstudio
