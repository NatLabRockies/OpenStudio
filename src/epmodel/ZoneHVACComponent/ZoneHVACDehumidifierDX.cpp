/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACDehumidifierDX.hpp"
#include "ZoneHVACDehumidifierDX_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Dehumidifier_DX_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACDehumidifierDX::ZoneHVACDehumidifierDX(const Model& model) : ZoneHVACComponent(ZoneHVACDehumidifierDX::iddObjectType(), model) {
    auto waterRemovalCurve = CurveBiquadratic(model);
    OS_ASSERT(waterRemovalCurve.setCoefficient1Constant(-2.724878664080));
    OS_ASSERT(waterRemovalCurve.setCoefficient2x(0.100711983591));
    OS_ASSERT(waterRemovalCurve.setCoefficient3xPOW2(-0.000990538285));
    OS_ASSERT(waterRemovalCurve.setCoefficient4y(0.050053043874));
    OS_ASSERT(waterRemovalCurve.setCoefficient5yPOW2(-0.000203629282));
    OS_ASSERT(waterRemovalCurve.setCoefficient6xTIMESY(-0.000341750531));
    OS_ASSERT(waterRemovalCurve.setMinimumValueofx(21.0));
    OS_ASSERT(waterRemovalCurve.setMaximumValueofx(32.22));
    OS_ASSERT(waterRemovalCurve.setMinimumValueofy(40.0));
    OS_ASSERT(waterRemovalCurve.setMaximumValueofy(80.0));

    auto energyFactorCurve = CurveBiquadratic(model);
    OS_ASSERT(energyFactorCurve.setCoefficient1Constant(-2.388319068955));
    OS_ASSERT(energyFactorCurve.setCoefficient2x(0.093047739452));
    OS_ASSERT(energyFactorCurve.setCoefficient3xPOW2(-0.001369700327));
    OS_ASSERT(energyFactorCurve.setCoefficient4y(0.066533716758));
    OS_ASSERT(energyFactorCurve.setCoefficient5yPOW2(-0.000343198063));
    OS_ASSERT(energyFactorCurve.setCoefficient6xTIMESY(-0.000562490295));
    OS_ASSERT(energyFactorCurve.setMinimumValueofx(21.0));
    OS_ASSERT(energyFactorCurve.setMaximumValueofx(32.22));
    OS_ASSERT(energyFactorCurve.setMinimumValueofy(40.0));
    OS_ASSERT(energyFactorCurve.setMaximumValueofy(80.0));

    auto partLoadFractionCurve = CurveQuadratic(model);
    OS_ASSERT(partLoadFractionCurve.setCoefficient1Constant(0.95));
    OS_ASSERT(partLoadFractionCurve.setCoefficient2x(0.05));
    OS_ASSERT(partLoadFractionCurve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(partLoadFractionCurve.setMinimumValueofx(0.0));
    OS_ASSERT(partLoadFractionCurve.setMaximumValueofx(1.0));

    auto alwaysOn = model.alwaysOnDiscreteSchedule();

    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setRatedWaterRemoval(50.16));
    OS_ASSERT(setRatedEnergyFactor(3.412));
    OS_ASSERT(setRatedAirFlowRate(0.12036));
    OS_ASSERT(setWaterRemovalCurve(waterRemovalCurve));
    OS_ASSERT(setEnergyFactorCurve(energyFactorCurve));
    OS_ASSERT(setPartLoadFractionCorrelationCurve(partLoadFractionCurve));
    OS_ASSERT(setMinimumDryBulbTemperatureforDehumidifierOperation(10.0));
    OS_ASSERT(setMaximumDryBulbTemperatureforDehumidifierOperation(32.0));
    OS_ASSERT(setOffCycleParasiticElectricLoad(0.0));
  }

  ZoneHVACDehumidifierDX::ZoneHVACDehumidifierDX(const Model& model, const Curve& waterRemovalCurve, const Curve& energyFactorCurve,
                                                 const Curve& partLoadFractionCurve)
    : ZoneHVACComponent(ZoneHVACDehumidifierDX::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();

    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setRatedWaterRemoval(50.16));
    OS_ASSERT(setRatedEnergyFactor(3.412));
    OS_ASSERT(setRatedAirFlowRate(0.12036));
    OS_ASSERT(setWaterRemovalCurve(waterRemovalCurve));
    OS_ASSERT(setEnergyFactorCurve(energyFactorCurve));
    OS_ASSERT(setPartLoadFractionCorrelationCurve(partLoadFractionCurve));
    OS_ASSERT(setMinimumDryBulbTemperatureforDehumidifierOperation(10.0));
    OS_ASSERT(setMaximumDryBulbTemperatureforDehumidifierOperation(32.0));
    OS_ASSERT(setOffCycleParasiticElectricLoad(0.0));
  }

  ZoneHVACDehumidifierDX::ZoneHVACDehumidifierDX(std::shared_ptr<detail::ZoneHVACDehumidifierDX_Impl> impl) : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACDehumidifierDX::iddObjectType() {
    return {IddObjectType::ZoneHVAC_Dehumidifier_DX};
  }

  Schedule ZoneHVACDehumidifierDX::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACDehumidifierDX::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setAvailabilitySchedule(schedule);
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

  Curve ZoneHVACDehumidifierDX::waterRemovalCurve() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->waterRemovalCurve();
  }

  bool ZoneHVACDehumidifierDX::setWaterRemovalCurve(const Curve& curve) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setWaterRemovalCurve(curve);
  }

  Curve ZoneHVACDehumidifierDX::energyFactorCurve() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->energyFactorCurve();
  }

  bool ZoneHVACDehumidifierDX::setEnergyFactorCurve(const Curve& curve) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setEnergyFactorCurve(curve);
  }

  Curve ZoneHVACDehumidifierDX::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool ZoneHVACDehumidifierDX::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::ZoneHVACDehumidifierDX_Impl>()->setPartLoadFractionCorrelationCurve(curve);
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
      if (auto const waterRemovalCurve =
            getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName)) {
        result.push_back(*waterRemovalCurve);
      }
      if (auto const energyFactorCurve =
            getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName)) {
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

    Schedule ZoneHVACDehumidifierDX_Impl::availabilitySchedule() const {
      if (auto target =
            getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_Dehumidifier_DXFields::AvailabilityScheduleName)) {
        return *target;
      }
      throw std::runtime_error("Zone HVAC DX dehumidifier is missing its availability schedule.");
    }

    bool ZoneHVACDehumidifierDX_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::ZoneHVAC_Dehumidifier_DXFields::AvailabilityScheduleName, "ZoneHVACDehumidifierDX", "Availability", schedule);
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

    Curve ZoneHVACDehumidifierDX_Impl::waterRemovalCurve() const {
      if (auto target = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName)) {
        return *target;
      }
      throw std::runtime_error("Zone HVAC DX dehumidifier is missing its water removal curve.");
    }

    bool ZoneHVACDehumidifierDX_Impl::setWaterRemovalCurve(const Curve& curve) {
      return setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName, curve.handle());
    }

    Curve ZoneHVACDehumidifierDX_Impl::energyFactorCurve() const {
      if (auto target = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName)) {
        return *target;
      }
      throw std::runtime_error("Zone HVAC DX dehumidifier is missing its energy factor curve.");
    }

    bool ZoneHVACDehumidifierDX_Impl::setEnergyFactorCurve(const Curve& curve) {
      return setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName, curve.handle());
    }

    Curve ZoneHVACDehumidifierDX_Impl::partLoadFractionCorrelationCurve() const {
      if (auto target =
            getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ZoneHVAC_Dehumidifier_DXFields::PartLoadFractionCorrelationCurveName)) {
        return *target;
      }
      throw std::runtime_error("Zone HVAC DX dehumidifier is missing its part load fraction correlation curve.");
    }

    bool ZoneHVACDehumidifierDX_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::PartLoadFractionCorrelationCurveName, curve.handle());
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
