/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/CoilPerformanceDXCooling.hpp"
#include "ParentObject/CoilPerformanceDXCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoilPerformance_DX_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CoilPerformanceDXCooling::CoilPerformanceDXCooling(const Model& model) : ParentObject(CoilPerformanceDXCooling::iddObjectType(), model) {}

  CoilPerformanceDXCooling::CoilPerformanceDXCooling(std::shared_ptr<detail::CoilPerformanceDXCooling_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType CoilPerformanceDXCooling::iddObjectType() {
    return IddObjectType::CoilPerformance_DX_Cooling;
  }

  std::vector<std::string> CoilPerformanceDXCooling::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoilPerformance_DX_CoolingFields::CondenserType);
  }

  boost::optional<double> CoilPerformanceDXCooling::grossRatedTotalCoolingCapacity() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->grossRatedTotalCoolingCapacity();
  }

  bool CoilPerformanceDXCooling::isGrossRatedTotalCoolingCapacityAutosized() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->isGrossRatedTotalCoolingCapacityAutosized();
  }

  bool CoilPerformanceDXCooling::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setGrossRatedTotalCoolingCapacity(grossRatedTotalCoolingCapacity);
  }

  void CoilPerformanceDXCooling::autosizeGrossRatedTotalCoolingCapacity() {
    getImpl<detail::CoilPerformanceDXCooling_Impl>()->autosizeGrossRatedTotalCoolingCapacity();
  }

  boost::optional<double> CoilPerformanceDXCooling::grossRatedSensibleHeatRatio() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->grossRatedSensibleHeatRatio();
  }

  bool CoilPerformanceDXCooling::isGrossRatedSensibleHeatRatioAutosized() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->isGrossRatedSensibleHeatRatioAutosized();
  }

  bool CoilPerformanceDXCooling::setGrossRatedSensibleHeatRatio(double grossRatedSensibleHeatRatio) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setGrossRatedSensibleHeatRatio(grossRatedSensibleHeatRatio);
  }

  void CoilPerformanceDXCooling::autosizeGrossRatedSensibleHeatRatio() {
    getImpl<detail::CoilPerformanceDXCooling_Impl>()->autosizeGrossRatedSensibleHeatRatio();
  }

  double CoilPerformanceDXCooling::grossRatedCoolingCOP() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->grossRatedCoolingCOP();
  }

  bool CoilPerformanceDXCooling::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setGrossRatedCoolingCOP(grossRatedCoolingCOP);
  }

  boost::optional<double> CoilPerformanceDXCooling::ratedAirFlowRate() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->ratedAirFlowRate();
  }

  bool CoilPerformanceDXCooling::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->isRatedAirFlowRateAutosized();
  }

  bool CoilPerformanceDXCooling::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void CoilPerformanceDXCooling::autosizeRatedAirFlowRate() {
    getImpl<detail::CoilPerformanceDXCooling_Impl>()->autosizeRatedAirFlowRate();
  }

  double CoilPerformanceDXCooling::fractionofAirFlowBypassedAroundCoil() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->fractionofAirFlowBypassedAroundCoil();
  }

  bool CoilPerformanceDXCooling::setFractionofAirFlowBypassedAroundCoil(double fractionofAirFlowBypassedAroundCoil) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setFractionofAirFlowBypassedAroundCoil(fractionofAirFlowBypassedAroundCoil);
  }

  double CoilPerformanceDXCooling::nominalTimeforCondensateRemovaltoBegin() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->nominalTimeforCondensateRemovaltoBegin();
  }

  bool CoilPerformanceDXCooling::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setNominalTimeforCondensateRemovaltoBegin(nominalTimeforCondensateRemovaltoBegin);
  }

  double CoilPerformanceDXCooling::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  }

  bool CoilPerformanceDXCooling::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
  }

  double CoilPerformanceDXCooling::maximumCyclingRate() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->maximumCyclingRate();
  }

  bool CoilPerformanceDXCooling::setMaximumCyclingRate(double maximumCyclingRate) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
  }

  double CoilPerformanceDXCooling::latentCapacityTimeConstant() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->latentCapacityTimeConstant();
  }

  bool CoilPerformanceDXCooling::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
  }

  std::string CoilPerformanceDXCooling::condenserType() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->condenserType();
  }

  bool CoilPerformanceDXCooling::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setCondenserType(condenserType);
  }

  double CoilPerformanceDXCooling::evaporativeCondenserEffectiveness() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->evaporativeCondenserEffectiveness();
  }

  bool CoilPerformanceDXCooling::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
  }

  boost::optional<double> CoilPerformanceDXCooling::evaporativeCondenserAirFlowRate() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->evaporativeCondenserAirFlowRate();
  }

  bool CoilPerformanceDXCooling::isEvaporativeCondenserAirFlowRateAutosized() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->isEvaporativeCondenserAirFlowRateAutosized();
  }

  bool CoilPerformanceDXCooling::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setEvaporativeCondenserAirFlowRate(evaporativeCondenserAirFlowRate);
  }

  void CoilPerformanceDXCooling::autosizeEvaporativeCondenserAirFlowRate() {
    getImpl<detail::CoilPerformanceDXCooling_Impl>()->autosizeEvaporativeCondenserAirFlowRate();
  }

  boost::optional<double> CoilPerformanceDXCooling::evaporativeCondenserPumpRatedPowerConsumption() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->evaporativeCondenserPumpRatedPowerConsumption();
  }

  bool CoilPerformanceDXCooling::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->isEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
  }

  bool CoilPerformanceDXCooling::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
    return getImpl<detail::CoilPerformanceDXCooling_Impl>()->setEvaporativeCondenserPumpRatedPowerConsumption(
      evaporativeCondenserPumpRatedPowerConsumption);
  }

  void CoilPerformanceDXCooling::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
    getImpl<detail::CoilPerformanceDXCooling_Impl>()->autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> CoilPerformanceDXCooling_Impl::grossRatedTotalCoolingCapacity() const {
      return getDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedTotalCoolingCapacity, true);
    }

    bool CoilPerformanceDXCooling_Impl::isGrossRatedTotalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedTotalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilPerformanceDXCooling_Impl::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedTotalCoolingCapacity, grossRatedTotalCoolingCapacity);
    }

    void CoilPerformanceDXCooling_Impl::autosizeGrossRatedTotalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedTotalCoolingCapacity, "autosize"));
    }

    boost::optional<double> CoilPerformanceDXCooling_Impl::grossRatedSensibleHeatRatio() const {
      return getDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedSensibleHeatRatio, true);
    }

    bool CoilPerformanceDXCooling_Impl::isGrossRatedSensibleHeatRatioAutosized() const {
      if (auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedSensibleHeatRatio, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilPerformanceDXCooling_Impl::setGrossRatedSensibleHeatRatio(double grossRatedSensibleHeatRatio) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedSensibleHeatRatio, grossRatedSensibleHeatRatio);
    }

    void CoilPerformanceDXCooling_Impl::autosizeGrossRatedSensibleHeatRatio() {
      OS_ASSERT(setString(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedSensibleHeatRatio, "autosize"));
    }

    double CoilPerformanceDXCooling_Impl::grossRatedCoolingCOP() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::GrossRatedCoolingCOP, grossRatedCoolingCOP);
    }

    boost::optional<double> CoilPerformanceDXCooling_Impl::ratedAirFlowRate() const {
      return getDouble(openstudio::CoilPerformance_DX_CoolingFields::RatedAirFlowRate, true);
    }

    bool CoilPerformanceDXCooling_Impl::isRatedAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::RatedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilPerformanceDXCooling_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    void CoilPerformanceDXCooling_Impl::autosizeRatedAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoilPerformance_DX_CoolingFields::RatedAirFlowRate, "autosize"));
    }

    double CoilPerformanceDXCooling_Impl::fractionofAirFlowBypassedAroundCoil() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::FractionofAirFlowBypassedAroundCoil, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setFractionofAirFlowBypassedAroundCoil(double fractionofAirFlowBypassedAroundCoil) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::FractionofAirFlowBypassedAroundCoil, fractionofAirFlowBypassedAroundCoil);
    }

    double CoilPerformanceDXCooling_Impl::nominalTimeforCondensateRemovaltoBegin() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::NominalTimeforCondensateRemovaltoBegin, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::NominalTimeforCondensateRemovaltoBegin, nominalTimeforCondensateRemovaltoBegin);
    }

    double CoilPerformanceDXCooling_Impl::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
      const auto value =
        getDouble(openstudio::CoilPerformance_DX_CoolingFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
                       ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
    }

    double CoilPerformanceDXCooling_Impl::maximumCyclingRate() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::MaximumCyclingRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::MaximumCyclingRate, maximumCyclingRate);
    }

    double CoilPerformanceDXCooling_Impl::latentCapacityTimeConstant() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::LatentCapacityTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
    }

    std::string CoilPerformanceDXCooling_Impl::condenserType() const {
      const auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::CondenserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::CoilPerformance_DX_CoolingFields::CondenserType, condenserType);
    }

    double CoilPerformanceDXCooling_Impl::evaporativeCondenserEffectiveness() const {
      const auto value = getDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilPerformanceDXCooling_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
    }

    boost::optional<double> CoilPerformanceDXCooling_Impl::evaporativeCondenserAirFlowRate() const {
      return getDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserAirFlowRate, true);
    }

    bool CoilPerformanceDXCooling_Impl::isEvaporativeCondenserAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilPerformanceDXCooling_Impl::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserAirFlowRate, evaporativeCondenserAirFlowRate);
    }

    void CoilPerformanceDXCooling_Impl::autosizeEvaporativeCondenserAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserAirFlowRate, "autosize"));
    }

    boost::optional<double> CoilPerformanceDXCooling_Impl::evaporativeCondenserPumpRatedPowerConsumption() const {
      return getDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserPumpRatedPowerConsumption, true);
    }

    bool CoilPerformanceDXCooling_Impl::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
      if (auto value = getString(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserPumpRatedPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilPerformanceDXCooling_Impl::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
      return setDouble(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserPumpRatedPowerConsumption,
                       evaporativeCondenserPumpRatedPowerConsumption);
    }

    void CoilPerformanceDXCooling_Impl::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
      OS_ASSERT(setString(openstudio::CoilPerformance_DX_CoolingFields::EvaporativeCondenserPumpRatedPowerConsumption, "autosize"));
    }

    std::vector<std::string> CoilPerformanceDXCooling_Impl::condenserTypeValues() const {
      return openstudio::epmodel::CoilPerformanceDXCooling::condenserTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
