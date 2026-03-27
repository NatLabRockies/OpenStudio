/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_HPP
#define EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilCoolingDXTwoStageWithHumidityControlMode_Impl;
}

class EPMODEL_API CoilCoolingDXTwoStageWithHumidityControlMode : public StraightComponent
{
 public:
  explicit CoilCoolingDXTwoStageWithHumidityControlMode(const Model& model);

  virtual ~CoilCoolingDXTwoStageWithHumidityControlMode() override = default;
  CoilCoolingDXTwoStageWithHumidityControlMode(const CoilCoolingDXTwoStageWithHumidityControlMode& other) = default;
  CoilCoolingDXTwoStageWithHumidityControlMode(CoilCoolingDXTwoStageWithHumidityControlMode&& other) = default;
  CoilCoolingDXTwoStageWithHumidityControlMode& operator=(const CoilCoolingDXTwoStageWithHumidityControlMode&) = default;
  CoilCoolingDXTwoStageWithHumidityControlMode& operator=(CoilCoolingDXTwoStageWithHumidityControlMode&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The canonical scalar two-stage DX surface is largely present, while schedule, curve, stage-object, and node-link helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXTwoStageWithHumidityControlMode.
  // - Implemented Parity: The scalar compressor, humidity-control, basin-heater, and stage-count helpers preserve the canonical naming and defaults.
  // - Documented Delta: Availability schedule, curves, stage-performance objects, and node-link helpers from canonical `openstudio::model::CoilCoolingDXTwoStageWithHumidityControlMode` are not exposed yet.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Cooling:DX:TwoStageWithHumidityControlMode` fields.
  // - Evidence: `src/model/CoilCoolingDXTwoStageWithHumidityControlMode.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXTwoStageWithHumidityControlMode.cpp`, and `src/epmodel/test/CoilCoolingDXTwoStageWithHumidityControlMode_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, stage-object, and relationship helpers without changing the preserved scalar signatures.
  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  int numberofCapacityStages() const;
  bool setNumberofCapacityStages(int numberofCapacityStages);

  int numberofEnhancedDehumidificationModes() const;
  bool setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes);

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl;

  friend class Model;

  explicit CoilCoolingDXTwoStageWithHumidityControlMode(std::shared_ptr<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
