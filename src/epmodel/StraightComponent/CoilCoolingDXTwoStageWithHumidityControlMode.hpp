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
  // - API: Preserve openstudio::model::CoilCoolingDXTwoStageWithHumidityControlMode scalar accessor names/signatures.
  // - Field Mapping: These APIs map directly to EnergyPlus Coil:Cooling:DX:TwoStageWithHumidityControlMode scalar fields.
  // - Field Mapping: relationship-like fields (schedules, curves, stage performance object references, node links) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXTwoStageWithHumidityControlMode.cpp writes these scalar values directly.
  // - TODO(parity): Add excluded relationship APIs in a dedicated parity pass without changing scalar signatures.
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
