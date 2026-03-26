/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HeatPumpWaterToWaterEquationFitCooling::HeatPumpWaterToWaterEquationFitCooling(const Model& model)
    : WaterToWaterComponent(HeatPumpWaterToWaterEquationFitCooling::iddObjectType(), model) {
    autosizeReferenceLoadSideFlowRate();
    autosizeReferenceSourceSideFlowRate();
    autosizeRatedCoolingCapacity();
    autosizeRatedCoolingPowerConsumption();
    OS_ASSERT(setReferenceCoefficientofPerformance(8.0));
    OS_ASSERT(setSizingFactor(1.0));
  }

  HeatPumpWaterToWaterEquationFitCooling::HeatPumpWaterToWaterEquationFitCooling(
    std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitCooling_Impl> impl)
    : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType HeatPumpWaterToWaterEquationFitCooling::iddObjectType() {
    return IddObjectType::HeatPump_WaterToWater_EquationFit_Cooling;
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::referenceLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->referenceLoadSideFlowRate();
  }

  double HeatPumpWaterToWaterEquationFitCooling::ratedLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->ratedLoadSideFlowRate();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::isReferenceLoadSideFlowRateAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->isReferenceLoadSideFlowRateAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setReferenceLoadSideFlowRate(referenceLoadSideFlowRate);
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setRatedLoadSideFlowRate(ratedLoadSideFlowRate);
  }

  void HeatPumpWaterToWaterEquationFitCooling::autosizeReferenceLoadSideFlowRate() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizeReferenceLoadSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::autosizedReferenceLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizedReferenceLoadSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::referenceSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->referenceSourceSideFlowRate();
  }

  double HeatPumpWaterToWaterEquationFitCooling::ratedSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->ratedSourceSideFlowRate();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::isReferenceSourceSideFlowRateAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->isReferenceSourceSideFlowRateAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setReferenceSourceSideFlowRate(referenceSourceSideFlowRate);
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setRatedSourceSideFlowRate(ratedSourceSideFlowRate);
  }

  void HeatPumpWaterToWaterEquationFitCooling::autosizeReferenceSourceSideFlowRate() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizeReferenceSourceSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::autosizedReferenceSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizedReferenceSourceSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::ratedCoolingCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->ratedCoolingCapacity();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::isRatedCoolingCapacityAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->isRatedCoolingCapacityAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setRatedCoolingCapacity(double ratedCoolingCapacity) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setRatedCoolingCapacity(ratedCoolingCapacity);
  }

  void HeatPumpWaterToWaterEquationFitCooling::autosizeRatedCoolingCapacity() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizeRatedCoolingCapacity();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::autosizedRatedCoolingCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizedRatedCoolingCapacity();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::ratedCoolingPowerConsumption() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->ratedCoolingPowerConsumption();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::isRatedCoolingPowerConsumptionAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->isRatedCoolingPowerConsumptionAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setRatedCoolingPowerConsumption(ratedCoolingPowerConsumption);
  }

  void HeatPumpWaterToWaterEquationFitCooling::autosizeRatedCoolingPowerConsumption() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizeRatedCoolingPowerConsumption();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitCooling::autosizedRatedCoolingPowerConsumption() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->autosizedRatedCoolingPowerConsumption();
  }

  double HeatPumpWaterToWaterEquationFitCooling::referenceCoefficientofPerformance() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->referenceCoefficientofPerformance();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
  }

  double HeatPumpWaterToWaterEquationFitCooling::sizingFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->sizingFactor();
  }

  bool HeatPumpWaterToWaterEquationFitCooling::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitCooling_Impl>()->setSizingFactor(sizingFactor);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::referenceLoadSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, true);
    }

    double HeatPumpWaterToWaterEquationFitCooling_Impl::ratedLoadSideFlowRate() const {
      if (auto value = referenceLoadSideFlowRate()) {
        return *value;
      }
      return -999.0;
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::isReferenceLoadSideFlowRateAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::referenceSourceSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, true);
    }

    double HeatPumpWaterToWaterEquationFitCooling_Impl::ratedSourceSideFlowRate() const {
      if (auto value = referenceSourceSideFlowRate()) {
        return *value;
      }
      return -999.0;
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::isReferenceSourceSideFlowRateAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::ratedCoolingCapacity() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, true);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::isRatedCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::ratedCoolingPowerConsumption() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, true);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::isRatedCoolingPowerConsumptionAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    double HeatPumpWaterToWaterEquationFitCooling_Impl::referenceCoefficientofPerformance() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoefficientofPerformance, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeatPumpWaterToWaterEquationFitCooling_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, referenceLoadSideFlowRate);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
      return setReferenceLoadSideFlowRate(ratedLoadSideFlowRate);
    }

    void HeatPumpWaterToWaterEquationFitCooling_Impl::autosizeReferenceLoadSideFlowRate() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceLoadSideFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, referenceSourceSideFlowRate);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
      return setReferenceSourceSideFlowRate(ratedSourceSideFlowRate);
    }

    void HeatPumpWaterToWaterEquationFitCooling_Impl::autosizeReferenceSourceSideFlowRate() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceSourceSideFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setRatedCoolingCapacity(double ratedCoolingCapacity) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, ratedCoolingCapacity);
    }

    void HeatPumpWaterToWaterEquationFitCooling_Impl::autosizeRatedCoolingCapacity() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingCapacity, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, ratedCoolingPowerConsumption);
    }

    void HeatPumpWaterToWaterEquationFitCooling_Impl::autosizeRatedCoolingPowerConsumption() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoolingPowerConsumption, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
      const bool result =
        setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpWaterToWaterEquationFitCooling_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SizingFactor, sizingFactor);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::autosizedReferenceLoadSideFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::autosizedReferenceSourceSideFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::autosizedRatedCoolingCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitCooling_Impl::autosizedRatedCoolingPowerConsumption() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    unsigned HeatPumpWaterToWaterEquationFitCooling_Impl::supplyInletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitCooling_Impl::supplyOutletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitCooling_Impl::demandInletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitCooling_Impl::demandOutletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
