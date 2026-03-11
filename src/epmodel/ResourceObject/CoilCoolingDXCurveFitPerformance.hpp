/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITPERFORMANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingDXCurveFitPerformance_Impl;
}

class EPMODEL_API CoilCoolingDXCurveFitPerformance : public ModelObject
{
 public:
  explicit CoilCoolingDXCurveFitPerformance(const Model& model);

  virtual ~CoilCoolingDXCurveFitPerformance() override = default;
  CoilCoolingDXCurveFitPerformance(const CoilCoolingDXCurveFitPerformance& other) = default;
  CoilCoolingDXCurveFitPerformance(CoilCoolingDXCurveFitPerformance&& other) = default;
  CoilCoolingDXCurveFitPerformance& operator=(const CoilCoolingDXCurveFitPerformance&) = default;
  CoilCoolingDXCurveFitPerformance& operator=(CoilCoolingDXCurveFitPerformance&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> capacityControlMethodValues();
  static std::vector<std::string> compressorFuelTypeValues();
  static std::vector<std::string> validCapacityControlMethodValues();
  static std::vector<std::string> validCompressorFuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Preserved scalar APIs map directly to matching E+ Coil:Cooling:DX:CurveFit:Performance fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXCurveFitPerformance writes these scalar fields one-to-one.
  // - TODO(parity): Add relationship/object-link APIs (operating modes, schedule, curve) in a dedicated non-scalar pass.
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

 protected:
  using ImplType = detail::CoilCoolingDXCurveFitPerformance_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDXCurveFitPerformance(std::shared_ptr<detail::CoilCoolingDXCurveFitPerformance_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
