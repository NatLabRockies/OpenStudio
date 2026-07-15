/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode.hpp"
#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "ParentObject/CoilPerformanceDXCooling.hpp"
#include "ParentObject/CoilPerformanceDXCooling_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_TwoStageWithHumidityControlMode_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingDXTwoStageWithHumidityControlMode::CoilCoolingDXTwoStageWithHumidityControlMode(const Model& model)
    : StraightComponent(CoilCoolingDXTwoStageWithHumidityControlMode::iddObjectType(), model) {
    bool ok = true;

    ok = setNumberofCapacityStages(2);
    OS_ASSERT(ok);
    ok = setNumberofEnhancedDehumidificationModes(1);
    OS_ASSERT(ok);
    ok = setCrankcaseHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterSetpointTemperature(2.0);
    OS_ASSERT(ok);
    ok = setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0);
    OS_ASSERT(ok);
  }

  CoilCoolingDXTwoStageWithHumidityControlMode::CoilCoolingDXTwoStageWithHumidityControlMode(
    std::shared_ptr<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDXTwoStageWithHumidityControlMode::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_TwoStageWithHumidityControlMode;
  }

  boost::optional<Schedule> CoilCoolingDXTwoStageWithHumidityControlMode::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDXTwoStageWithHumidityControlMode::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setAvailabilitySchedule(schedule);
  }

  void CoilCoolingDXTwoStageWithHumidityControlMode::resetAvailabilitySchedule() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetAvailabilitySchedule();
  }

  double CoilCoolingDXTwoStageWithHumidityControlMode::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->crankcaseHeaterCapacity();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  boost::optional<Curve> CoilCoolingDXTwoStageWithHumidityControlMode::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilCoolingDXTwoStageWithHumidityControlMode::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  }

  int CoilCoolingDXTwoStageWithHumidityControlMode::numberofCapacityStages() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->numberofCapacityStages();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setNumberofCapacityStages(int numberofCapacityStages) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setNumberofCapacityStages(numberofCapacityStages);
  }

  int CoilCoolingDXTwoStageWithHumidityControlMode::numberofEnhancedDehumidificationModes() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->numberofEnhancedDehumidificationModes();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setNumberofEnhancedDehumidificationModes(
      numberofEnhancedDehumidificationModes);
  }

  boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode::normalModeStage1CoilPerformance() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->normalModeStage1CoilPerformance();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setNormalModeStage1CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setNormalModeStage1CoilPerformance(coilPerformanceDXCooling);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetNormalModeStage1CoilPerformance() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetNormalModeStage1CoilPerformance();
  }

  boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode::normalModeStage1Plus2CoilPerformance() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->normalModeStage1Plus2CoilPerformance();
  }
  bool
    CoilCoolingDXTwoStageWithHumidityControlMode::setNormalModeStage1Plus2CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setNormalModeStage1Plus2CoilPerformance(coilPerformanceDXCooling);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetNormalModeStage1Plus2CoilPerformance() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetNormalModeStage1Plus2CoilPerformance();
  }

  boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode::dehumidificationMode1Stage1CoilPerformance() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->dehumidificationMode1Stage1CoilPerformance();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setDehumidificationMode1Stage1CoilPerformance(
    const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setDehumidificationMode1Stage1CoilPerformance(
      coilPerformanceDXCooling);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetDehumidificationMode1Stage1CoilPerformance() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetDehumidificationMode1Stage1CoilPerformance();
  }

  boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode::dehumidificationMode1Stage1Plus2CoilPerformance() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->dehumidificationMode1Stage1Plus2CoilPerformance();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setDehumidificationMode1Stage1Plus2CoilPerformance(
    const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setDehumidificationMode1Stage1Plus2CoilPerformance(
      coilPerformanceDXCooling);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetDehumidificationMode1Stage1Plus2CoilPerformance() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetDehumidificationMode1Stage1Plus2CoilPerformance();
  }

  double CoilCoolingDXTwoStageWithHumidityControlMode::basinHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->basinHeaterCapacity();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  double CoilCoolingDXTwoStageWithHumidityControlMode::basinHeaterSetpointTemperature() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->basinHeaterSetpointTemperature();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  boost::optional<Schedule> CoilCoolingDXTwoStageWithHumidityControlMode::basinHeaterOperatingSchedule() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->basinHeaterOperatingSchedule();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setBasinHeaterOperatingSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setBasinHeaterOperatingSchedule(schedule);
  }
  void CoilCoolingDXTwoStageWithHumidityControlMode::resetBasinHeaterOperatingSchedule() {
    getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->resetBasinHeaterOperatingSchedule();
  }

  double CoilCoolingDXTwoStageWithHumidityControlMode::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }
  bool CoilCoolingDXTwoStageWithHumidityControlMode::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  bool CoilCoolingDXTwoStageWithHumidityControlMode::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<Schedule> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AvailabilityScheduleName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AvailabilityScheduleName, Handle(), false));
    }

    unsigned CoilCoolingDXTwoStageWithHumidityControlMode_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirInletNodeName;
    }

    unsigned CoilCoolingDXTwoStageWithHumidityControlMode_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirOutletNodeName;
    }

    std::vector<ModelObject> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::children() const {
      std::vector<ModelObject> result;
      if (const auto stage = normalModeStage1CoilPerformance()) {
        result.push_back(*stage);
      }
      if (const auto stage = normalModeStage1Plus2CoilPerformance()) {
        result.push_back(*stage);
      }
      if (const auto stage = dehumidificationMode1Stage1CoilPerformance()) {
        result.push_back(*stage);
      }
      if (const auto stage = dehumidificationMode1Stage1Plus2CoilPerformance()) {
        result.push_back(*stage);
      }
      return result;
    }

    double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    boost::optional<Curve> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName,
                        curve.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName,
                           Handle(), false));
    }

    double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
      const auto value = getDouble(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    int CoilCoolingDXTwoStageWithHumidityControlMode_Impl::numberofCapacityStages() const {
      const auto value = getInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofCapacityStages, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setNumberofCapacityStages(int numberofCapacityStages) {
      return setInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofCapacityStages, numberofCapacityStages);
    }

    int CoilCoolingDXTwoStageWithHumidityControlMode_Impl::numberofEnhancedDehumidificationModes() const {
      const auto value = getInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes) {
      return setInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes,
                    numberofEnhancedDehumidificationModes);
    }

    boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::normalModeStage1CoilPerformance() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilPerformanceDXCooling>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setNormalModeStage1CoilPerformance(
      const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceName,
                        coilPerformanceDXCooling.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetNormalModeStage1CoilPerformance() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceName, Handle(), false));
    }

    boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::normalModeStage1Plus2CoilPerformance() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilPerformanceDXCooling>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setNormalModeStage1Plus2CoilPerformance(
      const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceName,
                        coilPerformanceDXCooling.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetNormalModeStage1Plus2CoilPerformance() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceName, Handle(), false));
    }

    boost::optional<CoilPerformanceDXCooling> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::dehumidificationMode1Stage1CoilPerformance() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilPerformanceDXCooling>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setDehumidificationMode1Stage1CoilPerformance(
      const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceName,
                        coilPerformanceDXCooling.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetDehumidificationMode1Stage1CoilPerformance() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceName,
                           Handle(), false));
    }

    boost::optional<CoilPerformanceDXCooling>
      CoilCoolingDXTwoStageWithHumidityControlMode_Impl::dehumidificationMode1Stage1Plus2CoilPerformance() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilPerformanceDXCooling>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setDehumidificationMode1Stage1Plus2CoilPerformance(
      const CoilPerformanceDXCooling& coilPerformanceDXCooling) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceName,
                        coilPerformanceDXCooling.handle(), false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetDehumidificationMode1Stage1Plus2CoilPerformance() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceName,
                           Handle(), false));
    }

    double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::basinHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::basinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterSetpointTemperature,
                       basinHeaterSetpointTemperature);
    }

    boost::optional<Schedule> CoilCoolingDXTwoStageWithHumidityControlMode_Impl::basinHeaterOperatingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterOperatingScheduleName);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setBasinHeaterOperatingSchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterOperatingScheduleName, schedule.handle(),
                        false);
    }

    void CoilCoolingDXTwoStageWithHumidityControlMode_Impl::resetBasinHeaterOperatingSchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterOperatingScheduleName, Handle(), false));
    }

    double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
