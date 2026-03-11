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
namespace detail {

class EPMODEL_API CoilCoolingDXTwoStageWithHumidityControlMode_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilCoolingDXTwoStageWithHumidityControlMode_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
