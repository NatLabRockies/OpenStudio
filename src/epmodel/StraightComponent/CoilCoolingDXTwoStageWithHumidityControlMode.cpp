/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode.hpp"
#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

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

#define EPMODEL_IMPL_FORWARD_0(ret, name) \
  ret CoilCoolingDXTwoStageWithHumidityControlMode::name() const { return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->name(); }
#define EPMODEL_IMPL_FORWARD_1(ret, name, t1, a1) \
  ret CoilCoolingDXTwoStageWithHumidityControlMode::name(t1 a1) { return getImpl<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl>()->name(a1); }

EPMODEL_IMPL_FORWARD_0(double, crankcaseHeaterCapacity)
EPMODEL_IMPL_FORWARD_1(bool, setCrankcaseHeaterCapacity, double, crankcaseHeaterCapacity)

EPMODEL_IMPL_FORWARD_0(double, maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation)
EPMODEL_IMPL_FORWARD_1(bool, setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, double,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation)

EPMODEL_IMPL_FORWARD_0(int, numberofCapacityStages)
EPMODEL_IMPL_FORWARD_1(bool, setNumberofCapacityStages, int, numberofCapacityStages)

EPMODEL_IMPL_FORWARD_0(int, numberofEnhancedDehumidificationModes)
EPMODEL_IMPL_FORWARD_1(bool, setNumberofEnhancedDehumidificationModes, int, numberofEnhancedDehumidificationModes)

EPMODEL_IMPL_FORWARD_0(double, basinHeaterCapacity)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterCapacity, double, basinHeaterCapacity)

EPMODEL_IMPL_FORWARD_0(double, basinHeaterSetpointTemperature)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterSetpointTemperature, double, basinHeaterSetpointTemperature)

EPMODEL_IMPL_FORWARD_0(double, minimumOutdoorDryBulbTemperatureforCompressorOperation)
EPMODEL_IMPL_FORWARD_1(bool, setMinimumOutdoorDryBulbTemperatureforCompressorOperation, double,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation)

EPMODEL_IMPL_FORWARD_1(bool, addToNode, Node&, node)

#undef EPMODEL_IMPL_FORWARD_0
#undef EPMODEL_IMPL_FORWARD_1

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDXTwoStageWithHumidityControlMode_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirInletNodeName;
}

unsigned CoilCoolingDXTwoStageWithHumidityControlMode_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirOutletNodeName;
}

double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilCoolingDXTwoStageWithHumidityControlMode_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::
                                 MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return setDouble(
    openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
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
  const auto value =
    getInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoStageWithHumidityControlMode_Impl::setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes) {
  return setInt(openstudio::Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes,
                numberofEnhancedDehumidificationModes);
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
