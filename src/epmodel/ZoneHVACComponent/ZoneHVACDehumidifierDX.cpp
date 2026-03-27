/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACDehumidifierDX.hpp"
#include "ZoneHVACDehumidifierDX_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Dehumidifier_DX_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACDehumidifierDX::ZoneHVACDehumidifierDX(const Model& model) : ZoneHVACComponent(ZoneHVACDehumidifierDX::iddObjectType(), model) {
    OS_ASSERT(setRatedWaterRemoval(50.16));
    OS_ASSERT(setRatedEnergyFactor(3.412));
    OS_ASSERT(setRatedAirFlowRate(0.12036));
    OS_ASSERT(setMinimumDryBulbTemperatureforDehumidifierOperation(10.0));
    OS_ASSERT(setMaximumDryBulbTemperatureforDehumidifierOperation(32.0));
    OS_ASSERT(setOffCycleParasiticElectricLoad(0.0));
  }

  ZoneHVACDehumidifierDX::ZoneHVACDehumidifierDX(std::shared_ptr<detail::ZoneHVACDehumidifierDX_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACDehumidifierDX::iddObjectType() {
    return {IddObjectType::ZoneHVAC_Dehumidifier_DX};
  }

  double ZoneHVACDehumidifierDX::ratedWaterRemoval() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->ratedWaterRemoval();
  }

  bool ZoneHVACDehumidifierDX::setRatedWaterRemoval(double ratedWaterRemoval) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setRatedWaterRemoval(ratedWaterRemoval);
  }

  double ZoneHVACDehumidifierDX::ratedEnergyFactor() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->ratedEnergyFactor();
  }

  bool ZoneHVACDehumidifierDX::setRatedEnergyFactor(double ratedEnergyFactor) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setRatedEnergyFactor(ratedEnergyFactor);
  }

  double ZoneHVACDehumidifierDX::ratedAirFlowRate() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->ratedAirFlowRate();
  }

  bool ZoneHVACDehumidifierDX::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  double ZoneHVACDehumidifierDX::minimumDryBulbTemperatureforDehumidifierOperation() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->minimumDryBulbTemperatureforDehumidifierOperation();
  }

  bool ZoneHVACDehumidifierDX::setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setMinimumDryBulbTemperatureforDehumidifierOperation(
      minimumDryBulbTemperatureforDehumidifierOperation);
  }

  double ZoneHVACDehumidifierDX::maximumDryBulbTemperatureforDehumidifierOperation() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->maximumDryBulbTemperatureforDehumidifierOperation();
  }

  bool ZoneHVACDehumidifierDX::setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setMaximumDryBulbTemperatureforDehumidifierOperation(
      maximumDryBulbTemperatureforDehumidifierOperation);
  }

  double ZoneHVACDehumidifierDX::offCycleParasiticElectricLoad() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->offCycleParasiticElectricLoad();
  }

  bool ZoneHVACDehumidifierDX::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setOffCycleParasiticElectricLoad(offCycleParasiticElectricLoad);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<ModelObject> ZoneHVACDehumidifierDX_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto const waterRemovalCurve = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName)) {
        result.push_back(*waterRemovalCurve);
      }
      if (auto const energyFactorCurve = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName)) {
        result.push_back(*energyFactorCurve);
      }
      if (auto const partLoadFractionCorrelationCurve =
            getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::PartLoadFractionCorrelationCurveName)) {
        result.push_back(*partLoadFractionCorrelationCurve);
      }
      return result;
    }

    unsigned ZoneHVACDehumidifierDX_Impl::inletPort() const {
      return openstudio::ZoneHVAC_Dehumidifier_DXFields::AirInletNodeName;
    }

    unsigned ZoneHVACDehumidifierDX_Impl::outletPort() const {
      return openstudio::ZoneHVAC_Dehumidifier_DXFields::AirOutletNodeName;
    }

    double ZoneHVACDehumidifierDX_Impl::ratedWaterRemoval() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedWaterRemoval, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setRatedWaterRemoval(double ratedWaterRemoval) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedWaterRemoval, ratedWaterRemoval);
    }

    double ZoneHVACDehumidifierDX_Impl::ratedEnergyFactor() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedEnergyFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setRatedEnergyFactor(double ratedEnergyFactor) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedEnergyFactor, ratedEnergyFactor);
    }

    double ZoneHVACDehumidifierDX_Impl::ratedAirFlowRate() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedAirFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    double ZoneHVACDehumidifierDX_Impl::minimumDryBulbTemperatureforDehumidifierOperation() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::MinimumDryBulbTemperatureforDehumidifierOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::MinimumDryBulbTemperatureforDehumidifierOperation,
                       minimumDryBulbTemperatureforDehumidifierOperation);
    }

    double ZoneHVACDehumidifierDX_Impl::maximumDryBulbTemperatureforDehumidifierOperation() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::MaximumDryBulbTemperatureforDehumidifierOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::MaximumDryBulbTemperatureforDehumidifierOperation,
                       maximumDryBulbTemperatureforDehumidifierOperation);
    }

    double ZoneHVACDehumidifierDX_Impl::offCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::OffCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACDehumidifierDX_Impl::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
      return setDouble(openstudio::ZoneHVAC_Dehumidifier_DXFields::OffCycleParasiticElectricLoad, offCycleParasiticElectricLoad);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
