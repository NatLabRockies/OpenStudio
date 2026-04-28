/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDX.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

  void applyConstructorDefaults(CoilCoolingDX& coil) {
    ScheduleConstant alwaysOn(coil.model());
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));
  }

  void applyDefaultPerformanceDefaults(CoilCoolingDXCurveFitPerformance& performance, const Model& model) {
    CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
    baseOperatingMode.autosizeRatedGrossTotalCoolingCapacity();
    baseOperatingMode.autosizeRatedEvaporatorAirFlowRate();
    baseOperatingMode.autosizeRatedCondenserAirFlowRate();
    OS_ASSERT(baseOperatingMode.setMaximumCyclingRate(0.0));
    OS_ASSERT(baseOperatingMode.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(0.0));
    OS_ASSERT(baseOperatingMode.setLatentCapacityTimeConstant(0.0));
    OS_ASSERT(baseOperatingMode.setNominalTimeforCondensateRemovaltoBegin(0.0));
    OS_ASSERT(!baseOperatingMode.applyLatentDegradationtoSpeedsGreaterthan1());
    OS_ASSERT(baseOperatingMode.setCondenserType("AirCooled"));
    baseOperatingMode.autosizeNominalEvaporativeCondenserPumpPower();

    OS_ASSERT(performance.setCrankcaseHeaterCapacity(0.0));
    OS_ASSERT(performance.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0));
    OS_ASSERT(performance.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
    OS_ASSERT(performance.setUnitInternalStaticAirPressure(773.3));
    OS_ASSERT(performance.setCapacityControlMethod("Discrete"));
    OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterCapacity(0.0));
    OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterSetpointTemperature(2.0));
    auto heaterSchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(performance.getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setPointer(
      openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName, heaterSchedule.handle(),
      false));
    OS_ASSERT(performance.setCompressorFuelType("Electricity"));
    OS_ASSERT(performance.getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setPointer(
      openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::BaseOperatingMode, baseOperatingMode.handle()));
  }

  }  // namespace

  CoilCoolingDX::CoilCoolingDX(const Model& model) : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);

    CoilCoolingDXCurveFitPerformance performance(model);
    applyDefaultPerformanceDefaults(performance, model);
    OS_ASSERT(setPerformanceObject(performance));
  }

  CoilCoolingDX::CoilCoolingDX(const Model& model, const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance)
    : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);
    OS_ASSERT(setPerformanceObject(coilCoolingDXCurveFitPerformance));
  }

  CoilCoolingDX::CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDX::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX;
  }

  bool CoilCoolingDX::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDX_Impl>()->addToNode(node);
  }

  Schedule CoilCoolingDX::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDX::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<ThermalZone> CoilCoolingDX::condenserZone() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserZone();
  }

  bool CoilCoolingDX::setCondenserZone(const ThermalZone& thermalZone) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserZone(thermalZone);
  }

  void CoilCoolingDX::resetCondenserZone() {
    getImpl<detail::CoilCoolingDX_Impl>()->resetCondenserZone();
  }

  CoilCoolingDXCurveFitPerformance CoilCoolingDX::performanceObject() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->performanceObject();
  }

  bool CoilCoolingDX::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setPerformanceObject(coilCoolingDXCurveFitPerformance);
  }

  std::string CoilCoolingDX::condenserInletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserInletNodeName();
  }

  bool CoilCoolingDX::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserInletNodeName(condenserInletNodeName);
  }

  std::string CoilCoolingDX::condenserOutletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserOutletNodeName();
  }

  bool CoilCoolingDX::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserOutletNodeName(condenserOutletNodeName);
  }
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilCoolingDX_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName;
    }

    unsigned CoilCoolingDX_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName;
    }

    bool CoilCoolingDX_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    std::vector<ModelObject> CoilCoolingDX_Impl::children() const {
      return {performanceObject()};
    }

    Schedule CoilCoolingDX_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilCoolingDX_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    boost::optional<ThermalZone> CoilCoolingDX_Impl::condenserZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Coil_Cooling_DXFields::CondenserZoneName);
    }

    bool CoilCoolingDX_Impl::setCondenserZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::Coil_Cooling_DXFields::CondenserZoneName, thermalZone.handle());
    }

    void CoilCoolingDX_Impl::resetCondenserZone() {
      bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserZoneName, "");
      OS_ASSERT(result);
    }

    CoilCoolingDXCurveFitPerformance CoilCoolingDX_Impl::performanceObject() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitPerformance>(openstudio::Coil_Cooling_DXFields::PerformanceObjectName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
      return setPointer(openstudio::Coil_Cooling_DXFields::PerformanceObjectName, coilCoolingDXCurveFitPerformance.handle());
    }

    // Condenser inlet node name
    std::string CoilCoolingDX_Impl::condenserInletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
      const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, condenserInletNodeName);
      OS_ASSERT(result);
      return result;
    }

    // Condenser outlet node name
    std::string CoilCoolingDX_Impl::condenserOutletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
      const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, condenserOutletNodeName);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
