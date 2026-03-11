/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_IMPL_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingDXCurveFitPerformance_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingDXCurveFitPerformance_Impl() override = default;

  double crankcaseHeaterCapacity() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

  double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
  bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

  double unitInternalStaticAirPressure() const;
  bool setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure);

  std::string capacityControlMethod() const;
  bool setCapacityControlMethod(const std::string& capacityControlMethod);

  double evaporativeCondenserBasinHeaterCapacity() const;
  bool setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity);

  double evaporativeCondenserBasinHeaterSetpointTemperature() const;
  bool setEvaporativeCondenserBasinHeaterSetpointTemperature(double evaporativeCondenserBasinHeaterSetpointTemperature);

  std::string compressorFuelType() const;
  bool setCompressorFuelType(const std::string& compressorFuelType);

  std::vector<std::string> capacityControlMethodValues() const;
  std::vector<std::string> compressorFuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
