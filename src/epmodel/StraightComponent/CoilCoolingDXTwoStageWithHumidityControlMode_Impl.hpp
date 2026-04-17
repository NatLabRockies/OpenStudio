/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_IMPL_HPP
#define EPMODEL_COILCOOLINGDXTWOSTAGEWITHHUMIDITYCONTROLMODE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
class Schedule;
class Curve;
class CoilPerformanceDXCooling;
namespace detail {

class EPMODEL_API CoilCoolingDXTwoStageWithHumidityControlMode_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingDXTwoStageWithHumidityControlMode_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  std::vector<ModelObject> children() const override;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
