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
class Schedule;
class Curve;
class CoilPerformanceDXCooling;

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
  // - Status: Partial Parity. The scalar two-stage DX surface, relationship-bearing schedule / curve / stage-object helpers, and the current epmodel
  //   supply-side air-loop insertion path are present, while canonical default stage-performance object seeding and broader OA / DOAS topology remain out
  //   of scope.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDXTwoStageWithHumidityControlMode.
  // - Implemented Parity: The scalar compressor, humidity-control, basin-heater, and stage-count helpers preserve the canonical naming and defaults;
  //   optional availability / basin-heater schedules, the crankcase-heater curve, the four stage-performance links, and the current supply-side
  //   `addToNode` path are also preserved.
  // - Documented Delta: Canonical constructor seeding of fully populated default `CoilPerformanceDXCooling` child graphs and broader OA / DOAS topology
  //   acceptance are deferred. The current `epmodel::CoilPerformanceDXCooling` wrapper remains scalar-only.
  // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Cooling:DX:TwoStageWithHumidityControlMode` fields.
  // - Evidence: `src/model/CoilCoolingDXTwoStageWithHumidityControlMode.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXTwoStageWithHumidityControlMode.cpp`, and `src/epmodel/test/CoilCoolingDXTwoStageWithHumidityControlMode_GTest.cpp`.
  // - Remaining Parity Work: Add canonical default stage-performance child seeding once `epmodel::CoilPerformanceDXCooling` gains its curve
  //   relationships, and widen topology acceptance only where the current epmodel air-loop graph can prove it.
  boost::optional<Schedule> availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
  bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
  void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  int numberofCapacityStages() const;
  bool setNumberofCapacityStages(int numberofCapacityStages);

  int numberofEnhancedDehumidificationModes() const;
  bool setNumberofEnhancedDehumidificationModes(int numberofEnhancedDehumidificationModes);

  boost::optional<CoilPerformanceDXCooling> normalModeStage1CoilPerformance() const;
  bool setNormalModeStage1CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
  void resetNormalModeStage1CoilPerformance();

  boost::optional<CoilPerformanceDXCooling> normalModeStage1Plus2CoilPerformance() const;
  bool setNormalModeStage1Plus2CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
  void resetNormalModeStage1Plus2CoilPerformance();

  boost::optional<CoilPerformanceDXCooling> dehumidificationMode1Stage1CoilPerformance() const;
  bool setDehumidificationMode1Stage1CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
  void resetDehumidificationMode1Stage1CoilPerformance();

  boost::optional<CoilPerformanceDXCooling> dehumidificationMode1Stage1Plus2CoilPerformance() const;
  bool setDehumidificationMode1Stage1Plus2CoilPerformance(const CoilPerformanceDXCooling& coilPerformanceDXCooling);
  void resetDehumidificationMode1Stage1Plus2CoilPerformance();

  double basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);

  double basinHeaterSetpointTemperature() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

  boost::optional<Schedule> basinHeaterOperatingSchedule() const;
  bool setBasinHeaterOperatingSchedule(Schedule& schedule);
  void resetBasinHeaterOperatingSchedule();

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXTwoStageWithHumidityControlMode(std::shared_ptr<detail::CoilCoolingDXTwoStageWithHumidityControlMode_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
